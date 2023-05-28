/*
 * LED_int.h
 *
 *  Created on: Mar 24, 2023
 *      Author: D E L L
 */

#ifndef LED_LED_INT_H_
#define LED_LED_INT_H_

#include "../../LIB/STD_TYPES.h"

#define GRN_LED  0
#define BLU_LED  1
#define RED_LED  2

void HLED_void_LEDInit(u8 Copy_u8LED);
void HLED_void_LEDOn(u8 Copy_u8LED);
void HLED_void_LEDOff(u8 Copy_u8LED);
void HLED_void_LEDFlip(u8 Copy_u8LED);


#endif /* LED_LED_INT_H_ */
