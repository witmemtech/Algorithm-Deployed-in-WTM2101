//------------------------------------------------------------------------------------
// JTAG_RAM.c
//------------------------------------------------------------------------------------
// This program contains some primitive routines for the JTAG port on a RISC-V core.
//
// Target device: N307
//
// Tool chain: GCC
//
// SC.TANG

//------------------------------------------------------------------------------------
// Includes
//------------------------------------------------------------------------------------
#include "debug_common.h"
#include "jtag_port.h"

//------------------------------------------------------------------------------------
// Function PROTOTYPES
//------------------------------------------------------------------------------------

static int cjtag_mode = 0;

void send_tms_cjtag(int tms)
{ 
    if(cjtag_mode){
        JTAG_IO_SET_TMS_HIGH();
        CJTAG_STROBETCK();
        JTAG_IO_SET_TMS(tms);
        {
            JTAG_IO_SET_TCK_LOW();
            JTAG_IO_SET_TCK_HIGH();
            JTAG_SET_TMS_INPUT();
        }
        {
            JTAG_IO_SET_TCK_LOW();
            JTAG_IO_SET_TCK_HIGH();
            JTAG_SET_TMS_OUTPUT();
        }
    }else{
        JTAG_IO_SET_TMS(tms);
#ifdef CJTAG_MODE
        CJTAG_STROBETCK();
#else
        JTAG_STROBETCK ();
#endif
    }
}

void send_tms_tdi(int tms)
{ 
    if(cjtag_mode){
        JTAG_IO_SET_TMS_HIGH();
        CJTAG_STROBETCK();
        JTAG_IO_SET_TMS(tms);
        CJTAG_STROBETCK();
        JTAG_IO_SET_TMS_LOW();
        CJTAG_STROBETCK();
    }
    else{
        JTAG_IO_SET_TMS(tms);
#ifdef CJTAG_MODE
        CJTAG_STROBETCK();
#else
        JTAG_STROBETCK ();
#endif
    }
}

//------------------------------------------------------------------------------------
// cJTAG mode
//------------------------------------------------------------------------------------
void switch_jtag2cjtag(void)
{
    JTAG_IO_SET(TCK, 1);
    Delay_ms();
    for(int i = 0;i < 5;i++){
        JTAG_IO_SET(TMS, 0);
        JTAG_IO_SET(TMS, 0);
    }
	
    Delay_ms();
	
    for(int i = 0;i < 100;i++){
        CJTAG_STROBETCK();
    }
    JTAG_IO_SET(TCK, 0);
    JTAG_IO_SET(TMS, 0);
    JTAG_IO_SET(TCK, 1);
    
    Delay_ms();
    JTAG_IO_SET(TCK, 0);
    Delay_ms();
    JTAG_IO_SET(TCK, 1);
    
    Delay_ms();
    JTAG_IO_SET(TMS, 1);
    Delay_ms();
    JTAG_IO_SET(TMS, 0);
    Delay_ms();
    JTAG_IO_SET(TMS, 1);
    Delay_ms();
    JTAG_IO_SET(TMS, 0);
    Delay_ms();
    JTAG_IO_SET(TMS, 1);
    Delay_ms();
    JTAG_IO_SET(TMS, 0);
    
    Delay_ms();
    
      //OAC
    send_tms_cjtag(0);
    send_tms_cjtag(0);
    send_tms_cjtag(1);
    send_tms_cjtag(1);
    //EC
    send_tms_cjtag(0);
    send_tms_cjtag(0);
    send_tms_cjtag(0);
    send_tms_cjtag(1);
    
    Delay_ms();
    
    //CP
    send_tms_cjtag(0);
    send_tms_cjtag(0);
    send_tms_cjtag(0);
    send_tms_cjtag(0);
    
    Delay_ms();
    
    send_tms_cjtag(1);
    send_tms_cjtag(0);
    send_tms_cjtag(0);
    cjtag_mode = 1;
	
}

//------------------------------------------------------------------------------------
// JTAG_Reset
//------------------------------------------------------------------------------------
void JTAG_Reset (void)
{
    JTAG_IO_SET(TMS, 1);

    JTAG_STROBETCK(); // move to Test Logic Reset state
    JTAG_STROBETCK();
    JTAG_STROBETCK();
    JTAG_STROBETCK();
    JTAG_STROBETCK();

    JTAG_IO_SET(TMS, 0);
 
    JTAG_STROBETCK(); // move to Run_Test/Idle state
}

//------------------------------------------------------------------------------------
// JTAG_IR_Scan
//------------------------------------------------------------------------------------

void jtag_idle_to_shift_ir(void)
{
    send_tms_cjtag(1);
    send_tms_cjtag(1);
    send_tms_cjtag(0);
    send_tms_cjtag(0);
}

void jtag_idle_to_shift_dr(void)
{
    send_tms_cjtag(1);
    send_tms_cjtag(0);
    send_tms_cjtag(0);
}
unsigned int JTAG_IR_Scan (unsigned int instruction, int num_bits)
{

    unsigned int retval; // JTAG instruction read
    int i;               // JTAG IR bit counter

    retval = 0x0;

    jtag_idle_to_shift_ir();
    if (cjtag_mode){
        JTAG_SET_TMS_OUTPUT();
        for (i = 0; i < num_bits; i++) //send_ir(5'h11);
        {
            JTAG_IO_SET_TMS(0x1 - (instruction & 0x01));
            instruction = instruction >> 1;
            CJTAG_STROBETCK();
            if (i == (num_bits - 1))
            {
                JTAG_IO_SET_TMS_HIGH();
            }else{
                JTAG_IO_SET_TMS_LOW();
            }
            {
                JTAG_IO_SET_TCK_LOW();
                JTAG_IO_SET_TCK_HIGH();
                JTAG_SET_TMS_INPUT();
	    }
            {
                JTAG_IO_SET_TCK_LOW();
                JTAG_IO_SET_TCK_HIGH();
                JTAG_SET_TMS_OUTPUT();
            }
	}
    }else{
        for (i = 0; i < num_bits; i++) //send_ir(5'h11);
        {
            JTAG_IO_SET_TDI((instruction & 0x01));
            instruction = instruction >> 1;

            retval = retval >> 1;
            if (JTAG_READ_TDO())
            {
                retval |= (0x01 << (num_bits - 1));
            }

            if (i == (num_bits - 1))
            {
                JTAG_IO_SET_TMS_HIGH();
            }

            JTAG_STROBETCK();
        }
    }

    send_tms_cjtag(1);
    send_tms_cjtag(0);

    return retval;
}

//------------------------------------------------------------------------------------
// JTAG_DR_Scan
//------------------------------------------------------------------------------------
unsigned long long JTAG_DR_Scan (unsigned long long dat, int num_bits)
{
    int i = 0;                     // JTAG DR bit counter
    unsigned int *retval_l;
    unsigned int *retval_h;
	
    unsigned int *dat_l;
    unsigned int *dat_h;
    unsigned long long retval; // JTAG return value
    unsigned long long dataval = dat;
    retval_l = ((unsigned int *)(&retval)) + 0;
    retval_h = ((unsigned int *)(&retval)) + 1;
	
    dat_l = ((unsigned int *)(&dataval)) + 0;
    dat_h = ((unsigned int *)(&dataval)) + 1;

    retval = 0x0L;

    jtag_idle_to_shift_dr();
    if (cjtag_mode){
        JTAG_SET_TMS_OUTPUT();
        for (i = 0; i < num_bits; i++)
        {
            if(i < 32){
                JTAG_IO_SET_TMS(1 - (*dat_l & 0x01));
                *dat_l = *dat_l >> 1;
            }else{
                JTAG_IO_SET_TMS(1 - (*dat_h & 0x01));
                *dat_h = *dat_h >> 1;
            }
            CJTAG_STROBETCK ();
            if (i == (num_bits - 1))
            {
                JTAG_IO_SET_TMS_HIGH();
            }else{
                JTAG_IO_SET_TMS_LOW();
            }
            {
                JTAG_IO_SET_TCK_LOW();
                JTAG_IO_SET_TCK_HIGH();
                JTAG_SET_TMS_INPUT();
	    }

            JTAG_IO_SET_TCK_LOW();
            if (JTAG_READ_TMS())
            {
                if(i < 32)
                    *(retval_l) |= (0x01L << i);
                else
                    *(retval_h) |= (0x01L << (i-32));
            }
            JTAG_IO_SET_TCK_HIGH();
            JTAG_SET_TMS_OUTPUT();
        }	
    }else{
        for (i = 0; i < num_bits; i++)
        {
            if(i < 32){
                JTAG_IO_SET_TDI((*dat_l & 0x01));
                *dat_l = *dat_l >> 1;
	    }else{
                JTAG_IO_SET_TDI((*dat_h & 0x01));
                *dat_h = *dat_h >> 1;
            }
			
            if (JTAG_READ_TDO())
            {
                if(i < 32)
                    *(retval_l) |= (0x01L << i);
                else
                    *(retval_h) |= (0x01L << (i-32));
            }
				
            if (i == (num_bits - 1))
            {
                JTAG_IO_SET_TMS_HIGH();
            }
            JTAG_STROBETCK ();
        }
    }
    send_tms_cjtag(1);
    send_tms_cjtag(0);

    return retval;
}


void idel_tck(int num)
{
    for (int idx = 0; idx < num; idx++)
    {
        send_tms_tdi(0);
    }
}
//------------------------------------------------------------------------------------
// write_dm_register
//------------------------------------------------------------------------------------
void write_dm_register (int reg, unsigned int value, int *done)
{

    unsigned long long tdi_date = 0; 
    unsigned long long tdo_reg = 0;
	
    *((unsigned int*)(&tdi_date) + 0) = (value << 2) | 0x2;;
    *((unsigned int*)(&tdi_date) + 1) = (value >> 30) | ((reg & 0x7F)<< 2);
	
    int timeout = 0;

    JTAG_IR_Scan (REG_DMI, INST_LENGTH); // load IR with REG_DM

    JTAG_DR_Scan (tdi_date, 41); // initiate the JTAG write

    // return value      for what
    // 2'b00             pass
    // 2'b01             reserve
    // 2'b10             write error
    // 2'b11             busy, need next read
    while (1)
    {

        idel_tck(10);

        tdo_reg = JTAG_DR_Scan (0x0L, 41); // poll for the write response

        switch (tdo_reg & 0x3)
        {
            case 0x00:
                *done = 0;
                return;
            case 0x03:
                timeout++;
                if (timeout > 10)
                {
                    *done = 2;
                    return;
                }
                break;
            case 0x01:
            case 0x10:
                *done = 0;
                return;
            default:
                break;
        };
    }
}


//------------------------------------------------------------------------------------
// read_dm_register
//------------------------------------------------------------------------------------
// Returns TRUE if the operation was successful; FALSE otherwise.
//
void read_dm_register (int reg, unsigned int *value, int *done)
{
    unsigned long long retval; // value returned from READ operation
    unsigned long long tdi_date = 0;
    unsigned int *retval_l;
    unsigned int *retval_h;
	
    *((unsigned int*)(&tdi_date) + 0) = 0x1;
    *((unsigned int*)(&tdi_date) + 1) = ((reg & 0x7F)<< 2);
	
    retval_l = ((unsigned int *)(&retval)) + 0;
    retval_h = ((unsigned int *)(&retval)) + 1;
    int timeout = 0;

    JTAG_IR_Scan (REG_DMI, INST_LENGTH); // load IR with REG_DM

    JTAG_DR_Scan (tdi_date, 41); // initiate the JTAG read

    // return value      for what
    // 2'b00             pass
    // 2'b01             reserve
    // 2'b10             write error
    // 2'b11             busy, need next read
    while (1)
    {
        idel_tck(10);
        retval = JTAG_DR_Scan (0x0L, 41);
        switch (retval & 0x03)
        {
            case 0x00:
                *done = 0;
                *value = (*retval_l) >> 2 | ((*retval_h & 0x3) << 30);
                return;
            case 0x03:
                timeout++;
                if (timeout < 10)
                    continue;
                else
                {
                    *done = 0;
                    *value = 0;
                    return;
                }
            case 0x01:
            case 0x10:
                *value = 0;
                *done = 2;
                return;
            default:
                return;
        }
    }
}

//------------------------------------------------------------------------------------
// access_dtm_register
//------------------------------------------------------------------------------------
unsigned long long access_dtm_register (int reg, unsigned int value, unsigned int bits)
{

    unsigned long long retval; // value returned from READ operation
    unsigned long long tdi_date = value;

    JTAG_IR_Scan (REG_DMI, INST_LENGTH); // load IR with REG_DMI

    retval = JTAG_DR_Scan (tdi_date, bits); // initiate the JTAG operation

    for (int idx = 0; idx < 10; idx++)
    {
        JTAG_IO_SET(TMS, 0);
        JTAG_STROBETCK (); // keep in RTI state
    }

    retval = retval >> 9;

    return retval;
}

void set_pc(uint32_t addr)
{
    write_csr(0X7B1, addr, ABS_CMD); //set pc to 0x00000000
}

void Jtag_Download_Bin(const uint32_t *file, int size)
{
    unsigned long read_id = 0x12345678L;
    int pass;

    JTAG_Reset (); // Reset the JTAG state machine on DUT

#ifdef CJTAG_MODE
    switch_jtag2cjtag();
#endif
  
    JTAG_IR_Scan (DTM_IDCODE, INST_LENGTH);   // load IDCODE into IR and HALT the DUT
	
    read_id = JTAG_DR_Scan (0x0L, IDCODE_LEN); // read the IDCODE
    DEBUG_PRINT("id 0x%x\n\r", read_id);  //N307 id 0x13070a6d

    enable_dmi();
    halt_cpu ();

    for(int i = 0;i < size / 4;i++)  //download bin file
    {
        pass = write_memory (0x4*i, *(file + i), MEM_SIZE_32, SYS_BUS);
        if(pass != 0) 
        {
            DEBUG_PRINT("write memory error addr:0x%x data:0x%x\n\r", 0x4*i, *(file + i));
        }
    }
			 
    set_pc(0x00000000);

    resume_cpu ();// GO

  return;
}


