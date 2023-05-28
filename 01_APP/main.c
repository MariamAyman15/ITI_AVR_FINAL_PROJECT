//include delay library
#include <util/delay.h>

//include bit math library
#include "../LIB/BIT_MATH.h"

//include standard types library
#include "../LIB/STD_TYPES.h"

//include DIO driver
#include "../MCAL/DIO/DIO_int.h"

//include DIO driver
#include "../MCAL/DIO/DIO_int.h"

//include DIO driver
#include "../MCAL/EXTI/EXTI_int.h"

//include ADC driver
#include "../MCAL/ADC/ADC_int.h"
#include "../MCAL/ADC/ADC_cfg.h"
//include SPI driver
#include "../MCAL/SPI/SPI_int.h"

//include UART driver
#include "../MCAL/USART/MUSART_int.h"

//include timers
#include "../MCAL/TIMER_DRIVER/TIMER_INTERFACE.h"

//include KeyPad driver
#include "../HAL/KEYPAD/KPD_int.h"
#include "../HAL/KEYPAD/KPD_cfg.h"
//include LCD driver
#include "../HAL/LCD/LCD_int.h"
#include "../HAL/LCD/LCD_cfg.h"
//include LDR driver
#include "../HAL/LDR/LDR_int.h"
#include "../HAL/LDR/LDR_cfg.h"

//include LM35 SENSOR driver
#include "../HAL/LM_SENSOR/LM_SENSOR_int.h"

//include STEPPER MOTOR driver
#include "../HAL/STEP_MOTOR/STEP_MOTOR_int.h"

//include SERVO driver
#include "../HAL/SERVO/SERVO_int.h"

//include FAN driver
#include "../HAL/FAN/FAN_int.h"

//include BUZZER driver
#include "../HAL/BUZZER/Buzzer_int.h"

//include LED driver
#include "../HAL/LED/LED_int.h"

#define CODE 2

#if CODE == 2
//MASTER

/*______|DOOR|______*/

//function prototype to check if the password is correct or not
u8 Cheack_Password(u8 a[],u8 b[],u8 n);

//array to save the first password
u8 Password [10];

//array to save the entered password to check
u8 Checkpassword[10];

int main (void)
{
	//spi initialization
	MDIO_voidSetPinDirection(PORTB,PIN4,PIN_OUT);
	MDIO_voidSetPinDirection(PORTB,PIN5,PIN_OUT);
	MDIO_voidSetPinDirection(PORTB,PIN6,PIN_IN);
	MDIO_voidSetPinDirection(PORTB,PIN7,PIN_OUT);

	MSPI_voidInit();

	//variables declaration and initialization
	u16 KPD_Read = 0xff;
	u8 i = 0;
	u8 check_counter = 0;

	//set number of password digits to 4 digits
	u8 NumOfDigits = 4;
	//variable to send data from virtual terminal to SPI
	char Send_Data;

	//LCD initialization
	HLCD_voidInit();

	//keypad initialization
	HKPD_voidInit();

	//UART initialization
	MUSART_voidInit ();

	//LED initialization
	HLED_void_LEDInit(RED_LED);

	//initialize Servo motor using timer 1
	HSERVO_voidInit();

	/*____|Set Password for First time|____*/
	//send "Enter password" to LCD then wait for 500 ms and clear the screen
	HLCD_voidSendString("ENTER PASSWORD: ");
	_delay_ms(500);
	HLCD_voidCLRScreen();

	//enter the password and save it to the array PASSWORD[]
	//iterate 4 times
	for (i=0; i<NumOfDigits;i++)
	{
		//while not pressed get the keypad value
		while (KPD_Read == 0xff)
		{
			//assign the value to KPD_READ variable
			KPD_Read = HKPD_u8GetPressedKey();
		}
		//send the number to LCD
		HLCD_voidSendNumber(KPD_Read);
		_delay_ms(300);
		//go to first line and position i , replace the number with *
		HLCD_voidGoToXy(i, 0);
		HLCD_voidSendString("*");
		//save the password to the array Password [i]
		Password [i] = KPD_Read;
		//initialize KPD_Read again
		KPD_Read = 0xff;
	}
	_delay_ms(500);
	HLCD_voidCLRScreen();

	while(1)
	{
		/*______|Enter Password To Check|______*/
		//send "check password" to LCD then wait for 500 ms and clear the screen
		HLCD_voidSendString("CHECK PASSWORD: ");
		_delay_ms(500);
		HLCD_voidCLRScreen();
		//enter the password and save it to the Checkpassword[] array
		//iterate 4 times
		for(i=0;i< NumOfDigits;i++)
		{
			//while not pressed get the keypad value
			while (KPD_Read == 0xff)
			{
				//assign the value to KPD_READ variable
				KPD_Read = HKPD_u8GetPressedKey();
			}
			//send the number to LCD
			HLCD_voidSendNumber(KPD_Read);
			_delay_ms(300);
			//go to first line and position i , replace the number with *
			HLCD_voidGoToXy(i, 0);
			HLCD_voidSendData('*');
			//save the password to the array Password [i]
			Checkpassword [i] = KPD_Read;
			//initialize KPD_Read again
			KPD_Read = 0xff;
		}
		_delay_ms(500);
		HLCD_voidCLRScreen();

		/*if the function return true: open the door, send welcome to LCD and turn on the LED*/
		if(Cheack_Password(Checkpassword,Password,NumOfDigits))
		{
			//send welcome to LCD
			HLCD_voidSendString("WELCOME HOME!");
			_delay_ms(500);
			//open the door by rotating the Servo motor by 90 degree
			HSERVO_voidOn();
			//turn on the LED
			HLED_void_LEDOn(RED_LED);
			//wait for 10 Seconds and rotate the servo to 0 degree
			_delay_ms(10000);
			HSERVO_voidOff();
			HLCD_voidCLRScreen();
			//while the password is true send data to spi
			while (Cheack_Password(Checkpassword,Password,NumOfDigits))
			{
				HLCD_voidSendString("VT: ");
				//receive data from the virtual terminal (the PC)
				Send_Data = MUSART_u8ReceiveDataSynch();
				//send the data to LCD
				HLCD_voidSendData(Send_Data);
				_delay_ms(500);
				//send the data to the slave using SPI
				MSPI_voidSendData(Send_Data);
				_delay_ms(500);
			}
		}

		/*if the password is wrong try 3 times then wait for 30 sec and try again|*/
		else
		{
			HLCD_voidGoToXy(0, 0);
			HLCD_voidSendString("WRONG PASSWORD");
			//write try again at second line and first position
			HLCD_voidGoToXy(0, 1);
			HLCD_voidSendString("TRY AGAIN");
			//wait 500 ms and clear screen
			_delay_ms(500);
			HLCD_voidCLRScreen();
			_delay_ms(500);
			//send string at first line and first position
			HLCD_voidGoToXy(0, 0);
			HLCD_voidSendString("YOU HAVE THREE");
			//send string at second line and first position
			HLCD_voidGoToXy(0, 1);
			HLCD_voidSendString("TRIALS ONLY");
			//wait 500 ms and clear screen
			_delay_ms(500);
			HLCD_voidCLRScreen();
			//count until check_counter == 3
			check_counter++;
			if (check_counter == 3)
			{
				//send from 30 to 1 to LCD screen
				for (i = 30 ; i> 0 ; i--)
				{
					HLCD_voidSendString("WAIT: ");
					HLCD_voidSendNumber(i);
					_delay_ms(1000);
					HLCD_voidCLRScreen();
				}
			}
		}
	}
}

/*__|function to compare between the saved password and the entered password|__*/
//a = password , b = check password , digit = number of digits
u8 Cheack_Password(u8 a[],u8 b[],u8 digit)
{
	//variable to count the digits
	u8 Num=0;
	for(u8 counter =0 ; counter < digit ; counter++)
	{
		if(a[counter] == b[counter])
		{
			Num++;
		}
	}
	//if Num == 4 return true
	if(Num == digit)	return 1;
	//else return false
	else                return 0;
}

#elif CODE == 1
/*_____|SLAVE MODE|_____*/

int main (void)
{
	//Declaration a variable to save the LDR read in it
	u16 LDR_Read;

	//Declaration a variable to save the LM35 SENSOR read in it
	u16 Temp_Read;

	//Declaration a variable to save the SPI read in it
	u8 Local_u8SPI_Read = 0;

	/*__|initialization of drivers|__*/
	//SPI initialization
	MDIO_voidSetPinDirection(PORTB , PIN5 ,PIN_IN);   //MOSI
	MDIO_voidSetPinDirection(PORTB , PIN6 ,PIN_OUT);  //MISO
	MDIO_voidSetPinDirection(PORTB , PIN7 ,PIN_IN);   //CLOCK
	MDIO_voidSetPinDirection(PORTB , PIN4 ,PIN_IN);   //SLAVE SELECT

	MSPI_voidInit();

	//LDR initialization
	LDR_voidInit();

	//LCD initialization
	HLCD_voidInit();

	//Servo motor initialization
	HSERVO_voidInit();

	//LM35 SENSOR initialization
	HLM35_voidInit();

	//BUZZER initialization
	HBZR_void_BZRInit();

	//FAN initialization one,two and three
	HFAN_voidInit(FAN_ONE);
	HFAN_voidInit(FAN_TWO);
	HFAN_voidInit(FAN_THREE);

	//LED initialization blue, green and red
	HLED_void_LEDInit(BLU_LED);
	HLED_void_LEDInit(GRN_LED);
	HLED_void_LEDInit(RED_LED);

	while(1)
	{
		/*|____|CURTAIN|_____|*/
		//using LDR task
		//take the read from the sensor and save it to LDR Read variable
		LDR_Read = LDR_u16Read();
		//send the read to LCD
		HLCD_voidSendString("LDR READ: ");
		HLCD_voidSendNumber(LDR_Read);

		//if the light intensity > 300 close the curtain automatically
		if ( LDR_Read >= 300)
		{
			//turn the sevo motor by 90 degree to close the curtain
			HSERVO_voidOn();
		}
		//if the light intensity < 300 open the curtain automatically
		else
		{
			//return the sevo motor to 0 degree to open the curtain
			HSERVO_voidOff();
		}
		//wait 500 ms and clear the LCD screen
		_delay_ms(500);
		HLCD_voidCLRScreen();

		//fire alarm and fan task
		//assign the read from LM35 sensor to TEMP_READ variable
		Temp_Read = HLM35_u8ReadTemp();
		//send the read to LCD then wait 500 ms and clear it
		HLCD_voidSendString("TEMP READ: ");
		HLCD_voidSendNumber(Temp_Read);
		_delay_ms(500);
		HLCD_voidCLRScreen();

		/*|___|FIRE_ALARM|___|*/
		//if the temperature sensor read >= 50 turn on the buzzer for 500 ms
		if(Temp_Read >= 50)
		{
			HBZR_voidBZROn();
			_delay_ms(500);
			HBZR_voidBZROff();
		}

		//IF TEMPERATURE BETWEEN 25 & 45 TURN ON THE FAN
		else if(Temp_Read >= 25 && Temp_Read <= 45)
		{
			HFAN_voidOn(FAN_ONE);
		}

		else
		{
			HFAN_voidOff(FAN_ONE);
		}

		/*SPI RECIEVING DATA TASK*/
		Local_u8SPI_Read = MSPI_u8RecieveData();

		//send the spi received data to LCD then wait 500 ms and clear it
		HLCD_voidSendData(Local_u8SPI_Read);
		_delay_ms(500);
		HLCD_voidCLRScreen();

		/*ROOM 1*/
		//when SPI receive a turn on the fan in room 1
		//when SPI receive a again turn off the fan in room 1
		if( Local_u8SPI_Read == 'a')
		{
			HLED_void_LEDFlip(BLU_LED);
		}

		//when SPI receive b turn on the fan in room 1
		//when SPI receive b again turn off the fan in room 1
		else if (Local_u8SPI_Read == 'b')
		{
			HFAN_voidFlip(FAN_TWO);
		}

		/*ROOM  2*/
		//when SPI receive c turn on the LED in room 2
		//when SPI receive c again turn off the LED in room 2
		else if (Local_u8SPI_Read == 'c')
		{
			HLED_void_LEDFlip(GRN_LED);
		}

		//when SPI receive d turn on the fan in room 2
		//when SPI receive d again turn off the fan in room 2
		else if (Local_u8SPI_Read == 'd')
		{
			HFAN_voidFlip(FAN_THREE);
		}

		else
		{
			//do nothing
		}
	}
}
#endif

