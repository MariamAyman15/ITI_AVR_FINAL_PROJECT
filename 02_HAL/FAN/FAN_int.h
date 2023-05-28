/*
 * FAN_int.h
 *
 *  Created on: Apr 22, 2023
 *      Author: D E L L
 */

#ifndef HAL_FAN_FAN_INT_H_
#define HAL_FAN_FAN_INT_H_


#define FAN_ONE   0
#define FAN_TWO   1
#define FAN_THREE 2

void HFAN_voidInit(u8 Copy_u8Fan);
void HFAN_voidOn(u8 Copy_u8Fan);
void HFAN_voidOff(u8 Copy_u8Fan);
void HFAN_voidFlip(u8 Copy_u8Fan);

#endif /* HAL_FAN_FAN_INT_H_ */
