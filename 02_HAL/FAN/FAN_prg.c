/*
 * FAN_prg.c
 *
 *  Created on: Apr 22, 2023
 *      Author: D E L L
 */

#include "DIO/DIO_int.h"
#include "FAN_int.h"
#include "FAN_cfg.h"
#include "FAN_prv.h"

void HFAN_voidInit(u8 Copy_u8Fan)
{
	switch(Copy_u8Fan)
	{
	case FAN_ONE:   MDIO_voidSetPinDirection(FAN_ONE_PORT,FAN_ONE_PIN,PIN_OUT);     break;
	case FAN_TWO:   MDIO_voidSetPinDirection(FAN_TWO_PORT,FAN_TWO_PIN,PIN_OUT);     break;
	case FAN_THREE: MDIO_voidSetPinDirection(FAN_THREE_PORT,FAN_THREE_PIN,PIN_OUT); break;
	default:                                                                          break;
	}

}
void HFAN_voidOn(u8 Copy_u8Fan)
{
	switch(Copy_u8Fan)
	{
	case FAN_ONE:   MDIO_voidSetPinValue(FAN_ONE_PORT,FAN_ONE_PIN,PIN_HIGH);     break;
	case FAN_TWO:   MDIO_voidSetPinValue(FAN_TWO_PORT,FAN_TWO_PIN,PIN_HIGH);     break;
	case FAN_THREE: MDIO_voidSetPinValue(FAN_THREE_PORT,FAN_THREE_PIN,PIN_HIGH); break;
	default:                                                                          break;
	}

}
void HFAN_voidOff(u8 Copy_u8Fan)
{
	switch(Copy_u8Fan)
	{
	case FAN_ONE:   MDIO_voidSetPinValue(FAN_ONE_PORT,FAN_ONE_PIN,PIN_LOW);     break;
	case FAN_TWO:   MDIO_voidSetPinValue(FAN_TWO_PORT,FAN_TWO_PIN,PIN_LOW);     break;
	case FAN_THREE: MDIO_voidSetPinValue(FAN_THREE_PORT,FAN_THREE_PIN,PIN_LOW); break;
	default:                                                                          break;
	}
}

void HFAN_voidFlip(u8 Copy_u8Fan)
{
	switch(Copy_u8Fan)
	{
	case FAN_ONE:   MDIO_voidToggleBin(FAN_ONE_PORT,FAN_ONE_PIN);     break;
	case FAN_TWO:   MDIO_voidToggleBin(FAN_TWO_PORT,FAN_TWO_PIN);     break;
	case FAN_THREE: MDIO_voidToggleBin(FAN_THREE_PORT,FAN_THREE_PIN); break;
	default:                                                            break;
	}
}
