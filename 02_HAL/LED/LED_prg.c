/*
 * LED_prg.c
 *
 *  Created on: Mar 24, 2023
 *      Author: D E L L
 */

#include "LED_cfg.h"
#include "LED_int.h"
#include "../../LIB/STD_TYPES.h"
#include  "../../MCAL/DIO/DIO_int.h"




void HLED_void_LEDInit(u8 Copy_u8LED)
{
	switch(Copy_u8LED)
	{
	case GRN_LED: MDIO_voidSetPinDirection(LED_GRN_PORT,LED_GRN_PIN,PIN_OUT); break;
	case BLU_LED: MDIO_voidSetPinDirection(LED_BLU_PORT,LED_BLU_PIN,PIN_OUT); break;
	case RED_LED: MDIO_voidSetPinDirection(LED_RED_PORT,LED_RED_PIN,PIN_OUT); break;
	default:                                                                  break;
	}
}
void HLED_void_LEDOn(u8 Copy_u8LED)
{
	switch(Copy_u8LED)
	{
	case GRN_LED: MDIO_voidSetPinValue(LED_GRN_PORT,LED_GRN_PIN,PIN_HIGH); break;
	case BLU_LED: MDIO_voidSetPinValue(LED_BLU_PORT,LED_BLU_PIN,PIN_HIGH); break;
	case RED_LED: MDIO_voidSetPinValue(LED_RED_PORT,LED_RED_PIN,PIN_HIGH); break;
	default:                                                               break;
	}
}
void HLED_void_LEDOff(u8 Copy_u8LED)
{
	switch(Copy_u8LED)
	{
	case GRN_LED: MDIO_voidSetPinValue(LED_GRN_PORT,LED_GRN_PIN,PIN_LOW); break;
	case BLU_LED: MDIO_voidSetPinValue(LED_BLU_PORT,LED_BLU_PIN,PIN_LOW); break;
	case RED_LED: MDIO_voidSetPinValue(LED_RED_PORT,LED_RED_PIN,PIN_LOW); break;
	default:                                                              break;
	}
}

void HLED_void_LEDFlip(u8 Copy_u8LED)
{
	switch(Copy_u8LED)
	{
	case GRN_LED: MDIO_voidToggleBin(LED_GRN_PORT,LED_GRN_PIN); break;
	case BLU_LED: MDIO_voidToggleBin(LED_BLU_PORT,LED_BLU_PIN); break;
	case RED_LED: MDIO_voidToggleBin(LED_RED_PORT,LED_RED_PIN); break;
	default:                                                    break;
	}
}
