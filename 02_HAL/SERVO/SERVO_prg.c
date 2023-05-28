/*
 * SERVO_prg.c
 *
 *  Created on: Apr 25, 2023
 *      Author: D E L L
 */
#include "DIO/DIO_int.h"
#include "SERVO_int.h"
#include "SERVO_cfg.h"
#include "SERVO_prv.h"
#include "../../MCAL/TIMER_DRIVER/TIMER_INTERFACE.h"

void HSERVO_voidInit(void)
{
	MDIO_voidSetPinDirection(SERVO_PORT, SERVO_PIN, PIN_OUT);
	TIMER1_voidSetMode_14(TIMER1_CHANNEL_A,NON_INVERTING,PRESCALER_DIV_BY_8);
	TIMER1_voidSetTopValueMode_14(2000);
}
void HSERVO_voidOn(void)
{
	TIMER1_voidSetCompareMatchValue(TIMER1_CHANNEL_A,1500);
}
void HSERVO_voidOff(void)
{
	TIMER1_voidSetCompareMatchValue(TIMER1_CHANNEL_A,300);
}

