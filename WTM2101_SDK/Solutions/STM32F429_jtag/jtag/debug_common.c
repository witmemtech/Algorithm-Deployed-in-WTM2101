
#include "debug_common.h"
#include "jtag_port.h"

static int riscv_xlen = 32;  // indicate riscv xlen, default 32

int enable_dmi() {
    int error;
    uint32_t value;

    read_dm_register(DBG_DMCONTROL, &value, &error);
    if (error)
        return error;
    value |= (1 << CTRL_DMACTIVE);
    write_dm_register(DBG_DMCONTROL, value, &error);
		
		//read_dm_register(DBG_DMCONTROL, &ret, &error);
    return error;
}

int get_cpu_state(CPU_STATE *state) {
	int error;
	uint32_t r_value;
	// read the dmstatus register
	read_dm_register(DBG_DMSTATUS, &r_value, &error);
	if ((r_value >> DMS_ALLNONEXISTENT) & 1)
		*state = CPU_NONEXISTENT;
	else if ((r_value >> DMS_ALLUNAVAIL) & 1)
		*state = CPU_UNAVAIL;
	else if ((r_value >> DMS_ALLRUNNING) & 1)
		*state = CPU_RUNNING;
	else if ((r_value >> DMS_ALLHALTED) & 1)
		*state = CPU_HALTED;
	else
		return 1;
	return error;
}

int clear_cmderr(void) {
	int error;
	write_dm_register(DBG_ABSTRACTCS, (7 << ABSCS_CMDERR), &error);
	return error;
}

int get_cmderr(CMD_ERROR_STATE *state) {
	int error;
	uint32_t r_value;
	read_dm_register(DBG_ABSTRACTCS, &r_value, &error);
	*state = (CMD_ERROR_STATE)((r_value >> ABSCS_CMDERR) & 0x7);
	return error;
}

int halt_cpu() {
    int error;
    uint32_t value = 0;
	
	
    read_dm_register(DBG_DMCONTROL, &value, &error);
    if (error)
    	return error;
    // set the haltreq bit
    value |= ((uint32_t)1<<CTRL_HALTREQ);
    // clear the resumereq bit
    value &= ~(1<<CTRL_RESUMEREQ);
    write_dm_register(DBG_DMCONTROL, value, &error);
    return error;
}

int resume_cpu() {
    int error;
    uint32_t value;
    read_dm_register(DBG_DMCONTROL, &value, &error);
    if (error)
    	return error;
    // clear the haltreq bit
    value &= ~((uint32_t)1<<CTRL_HALTREQ);
    // set the resumereq bit
    value |= (1<<CTRL_RESUMEREQ);
    write_dm_register(DBG_DMCONTROL, value, &error);
    return error;
}


static int read_register_using_abs_cmd(int reg_value, uint64_t *value, REG_ACCESS_SIZE size) {
	int error;
	uint32_t r_value;

	// write commad
	uint32_t command = (size << CMD_AARSIZE) | (1 << CMD_TRANSFER) | reg_value;
	write_dm_register(DBG_COMMAND, command, &error);
	if (error)
		return error;

	// read register[31:0]
	read_dm_register(DBG_DATA0, &r_value, &error);
	if (error)
		return error;

	*value = (uint64_t)r_value;
	if (size == REG_SIZE_64) {
		// read register[63:32]
		read_dm_register(DBG_DATA1, &r_value, &error);
		*value = ((uint64_t)r_value << 32) | *value;
		if (error)
			return error;
	}
	return OK;
}

static int write_register_using_abs_cmd(int reg_value, uint64_t value, REG_ACCESS_SIZE size) {
	int error;
	uint32_t w_value;

	// write data[31:0]
	w_value = (uint32_t)(value & 0xffffffff);
	write_dm_register(DBG_DATA0, w_value, &error);
	if (error)
		return error;

	if (size == REG_SIZE_64) {
		// write data[63:32]
		w_value = (uint32_t)((value>>32) & 0xffffffff);
		write_dm_register(DBG_DATA1, w_value, &error);
		if (error)
			return error;
	}

	// write commad
	uint32_t command = (size << CMD_AARSIZE) | (1 << CMD_TRANSFER) | (1<<CMD_WRITE) | reg_value;
	write_dm_register(DBG_COMMAND, command, &error);

	return error;
}

static int read_xpr_using_prg_buf(int reg_value, uint64_t *value, REG_ACCESS_SIZE size){
	uint32_t opcode;
	int error;

	// addi s0, rd, #0
	opcode = (reg_value << 15) | (8 << 7) | 0x13;
	write_dm_register(DBG_PROGBUF0, opcode, &error);
	if (error)
		return error;
	// ebreak
	opcode = 0x00100073;
	write_dm_register(DBG_PROGBUF1, opcode, &error);
	if (error)
		return error;

	// execute program buffer
	uint32_t command;
	command = (1 << CMD_POSTEXEC);
	write_dm_register(DBG_COMMAND, command, &error);
	if (error)
		return error;

	// read the xpr value
	command = (size << CMD_AARSIZE) | (1 << CMD_TRANSFER) | (0x1000 + reg_value);
	write_dm_register(DBG_COMMAND, command, &error);
	if (error)
		return error;

	// read the data
	uint32_t r_value;
	read_dm_register(DBG_DATA0, &r_value, &error);
	if (error)
		return error;
	*value = (uint64_t)r_value;
	if (size == REG_SIZE_64) {
		// read register[63:32]
		read_dm_register(DBG_DATA1, &r_value, &error);
		*value = ((uint64_t)r_value << 32) | *value;
		if (error)
			return error;
	}
	return OK;
}

static int write_xpr_using_prg_buf(int reg_value, uint64_t value, REG_ACCESS_SIZE size){
	uint32_t opcode;
	uint32_t w_value;
	int error;

	// write data
	// write data[31:0]
	w_value = (uint32_t)(value & 0xffffffff);
	write_dm_register(DBG_DATA0, w_value, &error);
	if (error)
		return error;

	if (size == REG_SIZE_64) {
		// write data[63:32]
		w_value = (uint32_t)((value>>32) & 0xffffffff);
		write_dm_register(DBG_DATA1, w_value, &error);
		if (error)
			return error;
	}

	// addi rd, s0, #0
	opcode = (8 << 15) | (reg_value << 7) | 0x13;
	write_dm_register(DBG_PROGBUF0, opcode, &error);
	if (error)
		return error;
	// ebreak
	opcode = 0x00100073;
	write_dm_register(DBG_PROGBUF1, opcode, &error);
	if (error)
		return error;

	// execute program buffer
	uint32_t command;
	command = (1u << CMD_POSTEXEC);
	write_dm_register(DBG_COMMAND, command, &error);
	if (error)
		return error;

	// write the xpr value
	command = (size << CMD_AARSIZE) | (1u << CMD_POSTEXEC ) | (1u << CMD_TRANSFER) |
											 (1u << CMD_WRITE)| (0x1008);
	write_dm_register(DBG_COMMAND, command, &error);
	return error;
}



static int read_memory_using_prg_buf(uint64_t addr , uint64_t *data, MEM_ACCESS_SIZE size) {
	int error;
	uint32_t addr32;
	uint32_t opcode;

	switch(size) {
		case MEM_SIZE_8:
			opcode = 0x00040403;  // lb	s0,0(s0)
			break;
		case MEM_SIZE_16:
			opcode = 0x00041403;  // lh	s0,0(s0)
			break;
		case MEM_SIZE_32:
			opcode = 0x00042403;  // lw	s0,0(s0)
			break;
		case MEM_SIZE_64:
			opcode = 0x00043403;  // ld	s0,0(s0)
			break;
		default:
			opcode = 0x00100073;  // ebreak
	}

	// write progbuf0
	write_dm_register(DBG_PROGBUF0, opcode, &error);
	if (error)
		return error;
	// write prog buf1 ebreak
	write_dm_register(DBG_PROGBUF1, 0x00100073, &error);   // ebreak
	if (error)
		return error;
	//
	// write data0 address
	addr32 = (uint32_t)(addr & 0xffffffff);
	write_dm_register(DBG_DATA0, addr32, &error);
	if (error)
		return error;

	uint32_t command;
	// for rv64, the address is 64bit
	if (riscv_xlen > 32) {
		addr32 = (uint32_t)((addr >> 32) & 0xffffffff);
		write_dm_register(DBG_DATA1, addr32, &error);
		if (error)
			return error;
		command = (3u << CMD_AAMSIZE) | (1u << CMD_POSTEXEC) | (1u << CMD_TRANSFER) | (1u << CMD_WRITE) | 0x1008;
	}
	else
		command = (2u << CMD_AAMSIZE) | (1u << CMD_POSTEXEC) | (1u << CMD_TRANSFER) | (1u << CMD_WRITE) | 0x1008;

	// write command,  write, postexec, regno = 0x1008
	write_dm_register(DBG_COMMAND, command, &error);
	if (error)
		return error;

	// write command to read x8, regno = 0x1008
	if (size > MEM_SIZE_32)
		command = (REG_SIZE_64 << CMD_AARSIZE) | (1u << CMD_TRANSFER) | 0x1008;
	else
		command = (REG_SIZE_32 << CMD_AARSIZE) | (1u << CMD_TRANSFER) | 0x1008;
	write_dm_register(DBG_COMMAND, command, &error);
	if (error)
		return error;

	// read dbg_data
	uint32_t r_value;
	read_dm_register(DBG_DATA0, &r_value, &error);
	if (error)
		return error;
	*data = (uint64_t) r_value;
	// read more than 32 bit memory, using DBG_DATA1
	if (size > MEM_SIZE_32) {
		read_dm_register(DBG_DATA1, &r_value, &error);
		*data = ((uint64_t)r_value << 32u) | *data;
	}
	return error;
}

static int read_memory_using_abs_cmd(uint64_t addr , uint64_t *data, MEM_ACCESS_SIZE size) {
	int error;
	uint32_t addr32;
	if (riscv_xlen > 32) {
		// for rv64
		addr32 = (uint32_t)addr & 0xffffffff;
		write_dm_register(DBG_DATA2, addr32, &error);
		if (error)
			return error;

		addr32 = (uint32_t)(addr >> 32u) & 0xffffffff;
		write_dm_register(DBG_DATA3, addr32, &error);
		if (error)
			return error;
	}
	else {
		addr32 = (uint32_t)addr & 0xffffffff;
		write_dm_register(DBG_DATA1, addr32, &error);
		if (error)
			return error;
	}

	// write command, to access memory
	write_dm_register(DBG_COMMAND, (2u << CMD_CMDTYPE) | (size << CMD_AARSIZE) | (1u<<CMD_TRANSFER), &error);
	if (error)
		return error;

	// read dbg_data
	uint32_t r_value;
	read_dm_register(DBG_DATA0, &r_value, &error);
	if (error)
		return error;
	*data = (uint64_t) r_value;
	// read more than 32 bit memory, using DBG_DATA1
	if (size > MEM_SIZE_32) {
		read_dm_register(DBG_DATA1, &r_value, &error);
		*data = ((uint64_t)r_value << 32u) | *data;
	}
	return error;
}

static int read_memory_using_sys_bus(uint64_t addr , uint64_t *data, MEM_ACCESS_SIZE size) {
	int error;
	uint32_t r_data;
	*data = 0;

	read_dm_register(DBG_SBCS, &r_data, &error);
	if (error){
            DEBUG_PRINT("error read DBG_SBCS\n\r");
	    return error;
        }

	r_data |= (size << SBCS_SBACCESS) | (1u << SBCS_SBREADONADDR);

	// write SBCS , select the access size
	write_dm_register(DBG_SBCS, r_data, &error);
	if (error){
            DEBUG_PRINT("error write DBG_SBCS\n\r");
	    return error;
        }


	// write address
	if (riscv_xlen > 32) {
		write_dm_register(DBG_SBADDRESS1, ((addr >> 32u) & 0xffffffff), &error);
		if (error)
			return error;
	}
	write_dm_register(DBG_SBADDRESS0, (addr & 0xffffffff), &error);
	if (error){
            DEBUG_PRINT("error write DBG_SBADDRESS0\n\r");
	    return error;
        }

	// wait the read finish
	int i;
	for(i=0; i<5; i++) {
		read_dm_register(DBG_SBCS, &r_data, &error);
		if (error){
                    DEBUG_PRINT("error wait the read finish DBG_SBCS\n\r");
		    return error;
                }

		// judge the sbbusy bit, if zero, mean access is finish
		if ( !((r_data >> SBCS_SBBUSY) & 0x1))
			break;
	}
	if (i==5) {
		return TIMEOUT;
	}

	// read data
	if (size > MEM_SIZE_32) {
		read_dm_register(DBG_SBDATA1, &r_data, &error);
		if (error){
                    DEBUG_PRINT("error read DBG_SBDATA1\n\r");
		    return error;
                }
		*data = (uint64_t)r_data << 32;
	}

	read_dm_register(DBG_SBDATA0, &r_data, &error);
	if (error){
            DEBUG_PRINT("error read DBG_SBDATA1\n\r");
	    return error;
        }
	*data |= (uint64_t)r_data;

	// write sbcs 0, clear sbreadonaddr , sbaccess, sbautoincrement, abreadondata
	write_dm_register(DBG_SBCS, 0, &error);
	return error;
}

int read_memory_bulk(uint64_t base_addr, uint64_t *data_array, int len, MEM_ACCESS_SIZE size) {
	int error;
	uint32_t r_data;

	read_dm_register(DBG_SBCS, &r_data, &error);
	if (error)
		return error;

	r_data |= (size << SBCS_SBACCESS) | (1u << SBCS_SBREADONADDR) |
			  (1u << SBCS_SBREADONDATA) | (1u << SBCS_SBAUTOINCREMENT);

	// write SBCS , select the access size
	write_dm_register(DBG_SBCS, r_data, &error);
	if (error)
		return error;


	// write address
	if (riscv_xlen > 32) {
		write_dm_register(DBG_SBADDRESS1, ((base_addr >> 32u) & 0xffffffff), &error);
		if (error)
			return error;
	}
	// write SBADDRESS0 trigger read
	write_dm_register(DBG_SBADDRESS0, (base_addr & 0xffffffff), &error);
	if (error)
		return error;

	int i;
	for(i=0; i<len-1; i++) {
		data_array[i] = 0;
		if (size > MEM_SIZE_32) {
			read_dm_register(DBG_SBDATA1, &r_data, &error);
			if (error)
				return error;
			data_array[i] = (uint64_t)r_data << 32u;
		}
		// read sbdata0 trigger next read
		read_dm_register(DBG_SBDATA0, &r_data, &error);
		if (error)
			return error;
		data_array[i] |= (uint64_t)r_data;
	}

	// disable autoread
	write_dm_register(DBG_SBCS, 0, &error);
	if (error)
		return error;

	data_array[i] = 0;
	if (size > MEM_SIZE_32) {
		read_dm_register(DBG_SBDATA1, &r_data, &error);
		if (error)
			return error;
		data_array[i] = (uint64_t)r_data << 32u;
	}
	// read sbdata0 trigger next read
	read_dm_register(DBG_SBDATA0, &r_data, &error);
	if (error)
		return error;
	data_array[i] |= (uint64_t)r_data;

	return OK;
}


int write_memory_using_prg_buf(uint64_t addr , uint64_t data, MEM_ACCESS_SIZE size) {
	int error;
	int aarsize;
	uint32_t opcode;

	switch(size) {
		case MEM_SIZE_8:
			opcode = 0x00940023;    // sb	s1,0(s0)
			break;
		case MEM_SIZE_16:
			opcode = 0x00941023;    // sh	s1,0(s0)
			break;
		case MEM_SIZE_32:
			opcode = 0x00942023;    // sw	s1,0(s0)
			break;
		case MEM_SIZE_64:
			opcode = 0x00943023;    // sd	s1,0(s0)
			break;
		default:
			opcode = 0x00100073;    // ebreak
	}


	// write prog buffer 0  sw s1, 0(s0)
	write_dm_register(DBG_PROGBUF0, opcode, &error);   // sb/sh/sw/sd s1, 0(s0)
	if (error)
		return error;
	// write progbug1  ebreak
	write_dm_register(DBG_PROGBUF1, 0x00100073, &error);   // ebreak
	if (error)
		return error;
	//
	// write data0 address
	uint32_t addr32 = (uint32_t)(addr & 0xffffffff);
	write_dm_register(DBG_DATA0, addr32, &error);
	if (error)
		return error;

	uint32_t command;
	if (riscv_xlen > 32) {
		// for rv64 , the address is 64 bit
		addr32 = (uint32_t)((addr >> 32) & 0xffffffff);
		write_dm_register(DBG_DATA1, addr32, &error);
		if (error)
			return error;
		command = (3u << CMD_AARSIZE) | (1u << CMD_WRITE) | (1u << CMD_TRANSFER) | 0x1008;
		aarsize = 3;
	}
	else {
		command = (2u << CMD_AARSIZE) | (1u << CMD_WRITE) | (1u << CMD_TRANSFER) | 0x1008;
		aarsize = 2;
	}

	// write command,  write, regno = 0x1008
	write_dm_register(DBG_COMMAND, command, &error);
	if (error)
		return error;

	// write data, value
	uint32_t data32;
	data32 = (uint32_t)(data & 0xffffffff);
	write_dm_register(DBG_DATA0, data32, &error);
	if (error)
		return error;

	if (size > MEM_SIZE_32) {
		// when write data exceed 32 bit, using dbg_data1 to parse high 32-bit value
		data32 = (uint32_t)((data >> 32u) & 0xffffffff);
		write_dm_register(DBG_DATA1, data32, &error);
		if (error)
			return error;
	}

	// write command, write, postexec, regno = 0x1009
	command = (aarsize << CMD_AARSIZE) | (1u << CMD_POSTEXEC) | (1u << CMD_TRANSFER) | (1u << CMD_WRITE) | 0x1009;
	write_dm_register(DBG_COMMAND, command, &error);

  return error;

}

int write_memory_using_abs_cmd(uint64_t addr , uint64_t data, MEM_ACCESS_SIZE size) {
	int error ;
	uint32_t addr32;
	uint32_t data32;
	addr32 = (uint32_t)(addr & 0xffffffff);
	data32 = (uint32_t)(data & 0xffffffff);

	if (riscv_xlen > 32) {
		// for rv64
		// write address
		write_dm_register(DBG_DATA2, addr32, &error);
		if (error)
			return error;
		addr32 = (uint32_t)((addr >> 32u) & 0xffffffff);
		write_dm_register(DBG_DATA3, addr32, &error);
		if (error)
			return error;

		// write data
		write_dm_register(DBG_DATA0, data32, &error);
		if (error)
			return error;
		data32 = (uint32_t)((data >> 32u) & 0xffffffff);
		write_dm_register(DBG_DATA1, data32, &error);
		if (error)
			return error;
	}
	else {
		// for rv32
		// write data1 address
		write_dm_register(DBG_DATA1, addr32, &error);
		if (error)
			return error;
		// write data0 value
		write_dm_register(DBG_DATA0, data32, &error);
		if (error)
			return error;
	}
	// write command, to access memory
	uint32_t command = (2u << CMD_CMDTYPE) | (size << CMD_AARSIZE) | (1u << CMD_TRANSFER) | (1u << CMD_WRITE);
	write_dm_register(DBG_COMMAND, command, &error);

  return error;
}



static int write_memory_using_sys_bus(uint64_t addr , uint64_t data, MEM_ACCESS_SIZE size) {
	int error;
	uint32_t r_data;

	read_dm_register(DBG_SBCS, &r_data, &error);
	if (error){
            DEBUG_PRINT("error read DBG_SBCS\r\n");
            return error;
        }

	r_data &= ~((7u << SBCS_SBACCESS) | (1u << SBCS_SBREADONADDR));
	r_data |= (size << SBCS_SBACCESS);

	// write SBCS , select the access size
	write_dm_register(DBG_SBCS, r_data, &error);
	if (error){
            DEBUG_PRINT("error write DBG_SBCS error\n\r");
	    return error;
        }

	// write address
	write_dm_register(DBG_SBADDRESS0, (addr & 0xffffffff), &error);
	if (error){
            DEBUG_PRINT("error write DBG_SBADDRESS0\n\r");
	    return error;
        }

	if (riscv_xlen > 32) {
		write_dm_register(DBG_SBADDRESS1, ((addr >> 32u) & 0xffffffff), &error);
		if (error){
                    DEBUG_PRINT("error write DBG_SBADDRESS1\n\r");
		    return error;
                }
	}

	// write data
	if (size > MEM_SIZE_32) {
		// for rv64, write the upper 32bit value
		write_dm_register(DBG_SBDATA1, ((data >> 32u) & 0xffffffff), &error);
		if (error){
                    DEBUG_PRINT("error write DBG_SBDATA0\n\r");
		    return error;
                }
	}

	write_dm_register(DBG_SBDATA0, (data & 0xffffffff), &error);
	if (error){
            DEBUG_PRINT("error write DBG_SBDATA0\n\r");
	    return error;
        }

	// wait the write finish
	for(int i=0; i<5; i++) {
		read_dm_register(DBG_SBCS, &r_data, &error);
		if (error){
                    DEBUG_PRINT("wait the write finish\n\r");
		    return error;
                }

		// judge the sbbusy bit, if zero, mean access is finish
		if ( !((r_data >> SBCS_SBBUSY) & 0x1)) {
			// write sbcs 0, clear sbreadonaddr , sbaccess, sbautoincrement, abreadondata
			write_dm_register(DBG_SBCS, 0, &error);
			return error;
		}
	}
	return 1;
}

int write_memory_bulk(uint64_t base_addr, uint64_t *data_array, int len, MEM_ACCESS_SIZE size) {
	int error;
	uint32_t r_data;

	read_dm_register(DBG_SBCS, &r_data, &error);
	if (error)
		return error;

	r_data |= (size << SBCS_SBACCESS) | (1u << SBCS_SBAUTOINCREMENT);

	// write SBCS , select the access size
	write_dm_register(DBG_SBCS, r_data, &error);
	if (error)
		return error;

	// write address
	write_dm_register(DBG_SBADDRESS0, (base_addr & 0xffffffff), &error);
	if (error)
		return error;

	if (riscv_xlen > 32) {
		write_dm_register(DBG_SBADDRESS1, ((base_addr >> 32u) & 0xffffffff), &error);
		if (error)
			return error;
	}

	for(int i=0; i<len; i++) {
		if (size > MEM_SIZE_32) {
			// for rv64, write the upper 32bit value
			write_dm_register(DBG_SBDATA1, ((data_array[i] >> 32u) & 0xffffffff), &error);
			if (error)
				return error;
		}
		// write SBDATA0, trigger write request, when write finish, sbaddress0 incress
		write_dm_register(DBG_SBDATA0, (data_array[i] & 0xffffffff), &error);
		if (error)
			return error;
	}

	// write sbcs 0, clear sbreadonaddr , sbaccess, sbautoincrement, abreadondata
	write_dm_register(DBG_SBCS, 0, &error);
	return error;
}

// reigster access
int read_xpr(int reg_num, uint64_t * value, ACCESS_MODE mode) {
	int error;
	if (mode == ABS_CMD) {
		error = read_register_using_abs_cmd(reg_num + 0x1000, value, REG_SIZE_32);
	}
	else
		error = read_xpr_using_prg_buf(reg_num, value, REG_SIZE_32);
	return error;
}

int write_xpr(int reg_num, uint64_t value, ACCESS_MODE mode) {
	int error;
	if (mode == ABS_CMD)
		error = write_register_using_abs_cmd(reg_num + 0x1000, value, REG_SIZE_32);
	else
		error = write_xpr_using_prg_buf(reg_num, value, REG_SIZE_32);
	return error;
}

int read_freg(int reg_num, uint64_t * value, ACCESS_MODE mode) {
    return read_register_using_abs_cmd(reg_num + 0x1020, value, REG_SIZE_32);
}

int write_freg(int reg_num, uint64_t value, ACCESS_MODE mode) {
    return write_register_using_abs_cmd(reg_num + 0x1020, value, REG_SIZE_32);
}

int read_csr(int reg_num, uint64_t * value, ACCESS_MODE mode) {
    return read_register_using_abs_cmd(reg_num, value, REG_SIZE_32);
}

int write_csr(int reg_num, uint64_t value, ACCESS_MODE mode){
    return write_register_using_abs_cmd(reg_num, value, REG_SIZE_32);
}

// read memory
int read_memory(uint64_t addr , uint64_t *data, MEM_ACCESS_SIZE size, ACCESS_MODE mode) {
    if (mode == PRG_BUF)
        return read_memory_using_prg_buf(addr, data, size);
    else if (mode == ABS_CMD)
        return read_memory_using_abs_cmd(addr, data, size);
    else
        return read_memory_using_sys_bus(addr, data, size);
}

// write memory
int write_memory(uint64_t addr , uint64_t data, MEM_ACCESS_SIZE size, ACCESS_MODE mode) {
    if (mode == PRG_BUF)
        return write_memory_using_prg_buf(addr, data, size);
    else if (mode == ABS_CMD)
        return write_memory_using_abs_cmd(addr, data, size);
    else
        return write_memory_using_sys_bus(addr, data, size);
}

