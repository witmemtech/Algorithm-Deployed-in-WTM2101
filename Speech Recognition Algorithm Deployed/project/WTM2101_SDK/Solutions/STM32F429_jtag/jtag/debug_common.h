#ifndef __DEBUG_COMMON__
#define __DEBUG_COMMON__

#include <stdio.h>
#include <stdint.h>
//#include <svdpi.h>
#include "encoding.h"

#define DTM_IDCODE 0x01
#define DTM_DTMCS  0x10
#define DTM_DMI    0x11
#define DTM_BYPASS 0x1f

#define DBG_DATA0 0x04
#define DBG_DATA1 0x05
#define DBG_DATA2 0x06
#define DBG_DATA3 0x07
#define DBG_DMCONTROL 0x10
#define DBG_DMSTATUS 0x11
#define DBG_HARTINFO 0x12
#define DBG_HALTSUM1 0x13
#define DBG_HAWINDOWSEL 0x14
#define DBG_HAWINDOW 0x15
#define DBG_ABSTRACTCS 0x16
#define DBG_COMMAND 0x17
#define DBG_ABSTRACTAUTO 0x18
#define DBG_CONFSTRPTR0 0x19
#define DBG_CONFSTRPTR1 0x1a
#define DBG_CONFSTRPTR2 0x1b
#define DBG_CONFSTRPTR3 0x1c
#define DBG_NEXTDM 0x1d
#define DBG_PROGBUF0 0x20
#define DBG_PROGBUF1 0x21
#define DBG_AUTHDATA 0x30
#define DBG_HALTSUM2 0x34
#define DBG_HALTSUM3 0x35
#define DBG_SBADDRESS3 0x37
#define DBG_SBCS 0x38
#define DBG_SBADDRESS0 0x39
#define DBG_SBADDRESS1 0x3a
#define DBG_SBADDRESS2 0x3b
#define DBG_SBDATA0 0x3c
#define DBG_SBDATA1 0x3d
#define DBG_SBDATA2 0x3e
#define DBG_SBDATA3 0x3f
#define DBG_HALTSUM0 0x40

#define IDCODE_VERSION 28u
#define IDCODE_PARTNUMBER 12u
#define IDCODE_MANUFLD  1u

#define DTMCS_DMIHARDRESET 17u
#define DTMCS_DMIRESET 16u
#define DTMCS_IDLE 12
#define DTMCS_DMISTAT 10u
#define DTMCS_ABITS 4u
#define DTMCS_VERSION 0u

#define CMD_CMDTYPE 24u
#define CMD_AARSIZE 20u
#define CMD_AAMSIZE 20u
#define CMD_POSTEXEC 18u
#define CMD_TRANSFER 17u
#define CMD_WRITE 16u

#define CTRL_HALTREQ 31u
#define CTRL_RESUMEREQ 30u
#define CTRL_HARTRESET 29u
#define CTRL_ACKHAVERESET 28u
#define CTRL_SETRESETHALTREQ 3u
#define CTRL_CLRRESETHALTREQ 2u
#define CTRL_NDMRESET 1u
#define CTRL_DMACTIVE 0u

#define DMS_IMPEBREAK 22u
#define DMS_ALLHAVERESET 19u
#define DMS_ANYHAVERESET 18u
#define DMS_ALLRESUMEACK 17u
#define DMS_ANYRESUMEACK 16u
#define DMS_ALLNONEXISTENT 15u
#define DMS_ANYNONEXISTENT 14u
#define DMS_ALLUNAVAIL 13u
#define DMS_ANYUNAVAIL 12u
#define DMS_ALLRUNNING 11u
#define DMS_ANYRUNNING 10u
#define DMS_ALLHALTED 9u
#define DMS_ANYHALTED 8u
#define DMS_AUTHENTICATED 7u
#define DMS_AUTHBUSY 6u
#define DMS_HASRESETHALTREQ 5u
#define DMS_CONFSTRPTRVALID 4u
#define DMS_VERSION 0u

#define ABSCS_PROGBUFSIZE 24u
#define ABSCS_BUSY 12u
#define ABSCS_CMDERR 8u
#define ABSCS_DATACOUNT 0u

#define SBCS_SBBUSYERROR 22u
#define SBCS_SBBUSY 21u
#define SBCS_SBREADONADDR 20u
#define SBCS_SBACCESS 17u
#define SBCS_SBAUTOINCREMENT 16u
#define SBCS_SBREADONDATA 15u
#define SBCS_SBERROR 12u
#define SBCS_SBASIZE 5u
#define SBCS_SBACCESS128 4u
#define SBCS_SBACCESS64 3u
#define SBCS_SBACCESS32 2u
#define SBCS_SBACCESS16 1u
#define SBCS_SBACCESS8 0u

#define OK 0
#define DM_ACCESS_ERROR 1
#define TIMEOUT 2
#define TEST_ERROR 3
#define CHECK_ERROR 4
#define STATE_ERROR 5
#define CLEAR_CMDERR_ERROR 6

extern void write_dm_register (int reg, unsigned int value, int *done);
extern void read_dm_register (int reg, unsigned int *value, int *done);
// access register
typedef enum {
	ABS_CMD = 0,
	PRG_BUF = 1,
	SYS_BUS = 2
}ACCESS_MODE;

typedef enum {
	MEM_SIZE_8 = 0u,
	MEM_SIZE_16,
	MEM_SIZE_32,
	MEM_SIZE_64,
	MEM_SIZE_128
}MEM_ACCESS_SIZE;

typedef enum {
	REG_SIZE_32 = 2u,
	REG_SIZE_64
}REG_ACCESS_SIZE;

typedef enum {
	CPU_NONEXISTENT,
	CPU_UNAVAIL,
	CPU_RUNNING,
	CPU_HALTED
}CPU_STATE;

typedef enum {
	CMDERR_NONE,
	CMDERR_BUSY,
	CMDERR_NOT_SUPPORT,
	CMDERR_EXCEPTION,
	CMDERR_HALT_RESUMT,
	CMDERR_BUS,
	CMDERR_OTHER
}CMD_ERROR_STATE;

int enable_dmi(void); // enable dmi, debugger can access dm

int halt_cpu(void); // halt cpu
int resume_cpu(void); // result cpu

int get_cpu_state(CPU_STATE *state);
int get_cmderr(CMD_ERROR_STATE *state);
int clear_cmderr(void);

// reg access
// mode can be ABS_CMD or PRG_BUF
// the return value is the access response.
// 0: no error
// 1: access error
int read_xpr(int reg_num, uint64_t * value, ACCESS_MODE mode);
int write_xpr(int reg_num, uint64_t value, ACCESS_MODE mode);

// freg access
// mode only support ABS_CMD
// the return value is the access response.
// 0: no error
// 1: access error
int read_freg(int reg_num, uint64_t * value, ACCESS_MODE mode);
int write_freg(int reg_num, uint64_t value, ACCESS_MODE mode);

// csr access 
// default access size is 32, 
// mode only support ABS_CMD
// the return value is the access response.
// 0: no error
// 1: access error
int read_csr(int reg_num, uint64_t * value, ACCESS_MODE mode);
int write_csr(int reg_num, uint64_t value, ACCESS_MODE mode);

// memory access
// default access size is 32, 
// mode support PRG_BUF, ABS_CMD, SYS_BUS 
// the return value is the access response.
// 0: no error
// 1: access error
int read_memory(uint64_t addr , uint64_t *data, MEM_ACCESS_SIZE size, ACCESS_MODE mode);
int write_memory(uint64_t addr , uint64_t data, MEM_ACCESS_SIZE size, ACCESS_MODE mode);

// read bulk memory, using SBA mode to access memory
// the return value is the access response.
// 0: no error
// 1: access error
int read_memory_bulk(uint64_t base_addr, uint64_t *data_array, int len, MEM_ACCESS_SIZE size);
int write_memory_bulk(uint64_t base_addr, uint64_t *data_array, int len, MEM_ACCESS_SIZE size);

#endif
