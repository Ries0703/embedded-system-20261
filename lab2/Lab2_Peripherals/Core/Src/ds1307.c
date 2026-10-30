#include "ds1307.h"
#include <stddef.h>
extern I2C_HandleTypeDef hi2c3;
static uint8_t bcd(uint8_t v) { return (uint8_t)(((v / 10) << 4) | (v % 10)); }
static uint8_t decimal(uint8_t v) { return (uint8_t)((v >> 4) * 10 + (v & 15)); }
static int valid_bcd(uint8_t v) { return (v & 15) <= 9 && (v >> 4) <= 9; }
static int valid(const Time *t) {
    static const uint8_t days[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    if (!t || t->sec > 59 || t->min > 59 || t->hour > 23 ||
        t->weekday < 1 || t->weekday > 7 || t->month < 1 || t->month > 12 || t->year > 99) return 0;
    unsigned limit=days[t->month-1] + (t->month == 2 && t->year % 4 == 0);
    return t->day >= 1 && t->day <= limit;
}
uint8_t TimeWeekday(unsigned year, unsigned month, unsigned day) {
    static const unsigned offsets[] = {0,3,2,5,0,3,5,1,4,6,2,4};
    if (month < 1 || month > 12) return 0;
    if (month < 3) year--;
    return (uint8_t)((year + year/4 - year/100 + year/400 + offsets[month-1] + day) % 7 + 1);
}
HAL_StatusTypeDef SetTime(const Time *t) {
    if (!valid(t)) return HAL_ERROR;
    uint8_t bytes[7]={bcd(t->sec),bcd(t->min),bcd(t->hour),t->weekday,bcd(t->day),bcd(t->month),bcd(t->year)};
    return HAL_I2C_Mem_Write(&hi2c3,0x68 << 1,0,I2C_MEMADD_SIZE_8BIT,bytes,7,50);
}
HAL_StatusTypeDef GetTime(Time *t) {
    if (!t) return HAL_ERROR;
    uint8_t bytes[7];
    HAL_StatusTypeDef status=HAL_I2C_Mem_Read(&hi2c3,0x68 << 1,0,I2C_MEMADD_SIZE_8BIT,bytes,7,50);
    if (status != HAL_OK) return status;
    if (bytes[0] & 0x80) return HAL_ERROR; /* CH: stopped oscillator */
    if (bytes[1] & 0x80 || bytes[2] & 0x80 || bytes[3] & 0xF8 || bytes[4] & 0xC0 || bytes[5] & 0xE0) return HAL_ERROR;
    for (unsigned i=0; i<7; ++i) {
        uint8_t v=bytes[i];
        if (i == 2) v &= (bytes[2] & 0x40) ? 0x1F : 0x3F;
        if (!valid_bcd(v)) return HAL_ERROR;
    }
    Time result={decimal(bytes[0]),decimal(bytes[1]),0,bytes[3],decimal(bytes[4]),decimal(bytes[5]),decimal(bytes[6])};
    if (bytes[2] & 0x40) {
        unsigned hour=decimal(bytes[2] & 0x1F);
        if (hour < 1 || hour > 12) return HAL_ERROR;
        result.hour=(uint8_t)(hour % 12 + ((bytes[2] & 0x20) ? 12 : 0));
    } else result.hour=decimal(bytes[2] & 0x3F);
    if (!valid(&result)) return HAL_ERROR;
    *t=result;
    return HAL_OK;
}
