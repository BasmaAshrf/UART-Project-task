/*
 * MC2.c
 *
 *  Created on: Nov 3, 2023
 *      Author: Sigma
 */
#include "uart.h"
#include "lcd.h"
#include "std_types.h"
#include "ultrasonic_sensor.h"
#include <avr/io.h>

//#define MC2_READY 0x10

int main(void)
{

	uint16 distance;

	/* Initialize the UART driver with Baud-rate = 9600 bits/sec */
	UART_init(9600);

	/* Initialize the LCD Driver */
	LCD_init();

	/* Display the received string on the LCD display */

	LCD_displayString("Distance=    cm");/**/

	while(1)
	{
		distance = UART_recieveByte();
		/*to move the cursor at first row to the column 10*/
		LCD_moveCursor( 0 , 10);
		if(distance >= 100){
			LCD_intgerToString(distance);
		}else{
			LCD_intgerToString(distance);
			LCD_displayCharacter(' ');
		}	}
}



