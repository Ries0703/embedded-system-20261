//----------------------------------------------------------------------------//
// This file is from https://github.com/adem-alnajjar/Gyroscope-L3GD20-_STM32 //
// and was modified by Cong Thuan Do (HUST) for STM32F429-DISC1 board         //
//----------------------------------------------------------------------------//

#ifndef __L3GD20_H
#define __L3GD20_H
#include <stdint.h>

#ifdef __cplusplus
 extern "C" {
#endif
	 
	 void L3GD20_Init(void);
	 
	 void L3GD20_loop(void);
	 
	 float get_Angle_X(void);
	 float get_Angle_Y(void);
	 float get_Angle_Z(void);

/* Ex2 integration: angular rates in deg/s, before angle integration. */
float get_Rate_X(void);
float get_Rate_Y(void);
float get_Rate_Z(void);
uint8_t L3GD20_IsCalibrated(void);


	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 #ifdef __cplusplus
}
#endif

#endif
