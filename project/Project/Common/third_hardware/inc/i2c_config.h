#ifndef __I2C_CONFIG_H
#define __I2C_CONFIG_H
#include <stdint.h>

uint8_t Codec_CheckOk(uint8_t _Address);
void Codec_Init();
uint8_t CodecReadByte(uint8_t device_addr, uint8_t ram_addr, uint8_t *data);
uint8_t DeviceSetSoftMode(uint8_t device_addr, uint8_t ram_addr, uint8_t data);
void DelayTest();
#endif // ! __I2C_CONFIG_H