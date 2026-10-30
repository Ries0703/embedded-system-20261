#include "ds1307.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
I2C_HandleTypeDef hi2c3;
static uint8_t registers[7];
static HAL_StatusTypeDef transport_status = HAL_OK;
HAL_StatusTypeDef HAL_I2C_Mem_Write(I2C_HandleTypeDef *bus, uint16_t addr, uint16_t reg, uint16_t size, uint8_t *data, uint16_t len, uint32_t timeout) {
    assert(bus == &hi2c3 && addr == 0xD0 && reg == 0 && size == 1 && len == 7 && timeout <= 100);
    if (transport_status == HAL_OK) memcpy(registers, data, 7);
    return transport_status;
}
HAL_StatusTypeDef HAL_I2C_Mem_Read(I2C_HandleTypeDef *bus, uint16_t addr, uint16_t reg, uint16_t size, uint8_t *data, uint16_t len, uint32_t timeout) {
    assert(bus == &hi2c3 && addr == 0xD0 && reg == 0 && size == 1 && len == 7 && timeout <= 100);
    if (transport_status == HAL_OK) memcpy(data, registers, 7);
    return transport_status;
}
int main(void) {
    Time t = {.sec=59,.min=59,.hour=23,.weekday=6,.day=30,.month=10,.year=26}, out;
    assert(SetTime(&t) == HAL_OK);
    assert(registers[0] == 0x59 && registers[1] == 0x59 && registers[2] == 0x23);
    assert(registers[4] == 0x30 && registers[5] == 0x10 && registers[6] == 0x26);
    assert(GetTime(&out) == HAL_OK && out.hour == 23 && out.sec == 59 && out.day == 30);
    t.month=2; t.day=31; assert(SetTime(&t) == HAL_ERROR);
    t.day=29; t.year=24; assert(SetTime(&t) == HAL_OK);
    t.year=25; assert(SetTime(&t) == HAL_ERROR);
    t.day=28; t.weekday=0; assert(SetTime(&t) == HAL_ERROR);
    t.weekday=6; t.hour=24; assert(SetTime(&t) == HAL_ERROR);
    t.hour=12; assert(SetTime(&t) == HAL_OK);
    registers[2]=0x72; assert(GetTime(&out) == HAL_OK && out.hour == 12);
    registers[2]=0x52; assert(GetTime(&out) == HAL_OK && out.hour == 0);
    registers[2]=0x61; assert(GetTime(&out) == HAL_OK && out.hour == 13);
    registers[0]|=0x80; assert(GetTime(&out) == HAL_ERROR);
    registers[0]=0x6A; assert(GetTime(&out) == HAL_ERROR);
    transport_status=HAL_TIMEOUT; assert(GetTime(&out) == HAL_TIMEOUT);
    puts("PASS: RTC BCD, calendar, 12h/24h, oscillator, address and transport checks");
}
