/*
 * MUSART_prg.c
 *
 *  Created on: Apr 5, 2023
 *      Author: Mariam
 */
#include "MUSART_cfg.h"
#include "MUSART_int.h"
#include "MUSART_prv.h"

#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"

#include "../DIO/DIO_int.h"
#include "../DIO/DIO_prv.h"

u8 USART_u8Data = 0;

void MUSART_voidInit (void)
{
	u8 Local_u8UBRR;
	//SELECT BAUD_RATE -> 9600
	Local_u8UBRR = (u8) BAUD_RATE_RESULT;
	UBRRH = ( (u8)Local_u8UBRR >> 8 );
	UBRRL = (u8)Local_u8UBRR;

	//ENABLE TX CICUIT
	SET_BIT(UCSRB,TXEN);

	//ENABLE RX CICUIT//
	SET_BIT(UCSRB,RXEN);

	//SELECT CONFIGURATION AS ASYNC
	SET_BIT(Local_u8UBRR,URSEL);

	//SLECET CHARACHER SIZE -> 8_BITS
	SET_BIT(Local_u8UBRR,UCSZ0);
	SET_BIT(Local_u8UBRR,UCSZ1);
	CLR_BIT(Local_u8UBRR,UCSZ2);

	//SELECT STOP BIT -> 1BIT
	//SET_BIT(UCSRA,U2X);

}

void MUSART_voidTransmitDataSynch (u8 copy_u8Data)
{

	while(GET_BIT(UCSRA,UDRE) == 0);
	//assign data to UDR register
	UDR = copy_u8Data;
}

u8 MUSART_u8ReceiveDataSynch (void)
{
	while(GET_BIT(UCSRA,RXC) == 0);
	return UDR;
}

void MUSART_voidTransmitDataASynch (u8 copy_u8Data)
{
	//assign the data passed to the function to the global variable
	USART_u8Data = copy_u8Data;
	//enable the UDR empty interrupt
	SET_BIT(UCSRB , UDRIE);
}

void __vector_14 (void) __attribute__((signal));
void __vector_14 (void)
{
	//check if the global variable equal zero
	if(USART_u8Data != 0)
	{
		UDR = USART_u8Data;
	}
	else
	{
		//do nothing
	}
	//disable the UDR empty interrupt
	CLR_BIT(UCSRB , UDRIE);
}
