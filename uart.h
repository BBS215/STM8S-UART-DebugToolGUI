#pragma once
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "COMM.H"

#define DEBUG_DEV_CMD_READ_8		(BYTE)0x1
#define DEBUG_DEV_CMD_READ_16		(BYTE)0x2
#define DEBUG_DEV_CMD_WRITE_8		(BYTE)0x3
#define DEBUG_DEV_CMD_WRITE_16		(BYTE)0x4
#define START_BYTE 					(uint8_t)0x55
#define STOP_BYTE 					(uint8_t)0xAA
#define TIMEOUT_MS					2000

int Read_Register(_TCHAR *COM_port_name, uint16_t reg_addr, uint8_t width, uint16_t *p_reg_data);
int Write_Register(_TCHAR *COM_port_name, uint16_t reg_addr, uint8_t width, uint16_t reg_data);

