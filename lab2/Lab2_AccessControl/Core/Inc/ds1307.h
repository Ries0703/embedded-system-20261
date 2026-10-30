#ifndef DS1307_H
#define DS1307_H
#include "stm32f4xx_hal.h"
typedef struct { uint8_t sec, min, hour, weekday, day, month, year; } Time;
HAL_StatusTypeDef SetTime(const Time *time);
HAL_StatusTypeDef GetTime(Time *time);
uint8_t TimeWeekday(unsigned year, unsigned month, unsigned day);
#endif
