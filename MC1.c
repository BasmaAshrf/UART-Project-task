/*
 * MC1.c
 *
 *  Created on: Nov 3, 2023
 *      Author: Sigma
 */

#include "uart.h"
#include "std_types.h"
#include "ultrasonic_sensor.h"
#include "lcd.h"
#include <util/delay.h>
#include <avr/io.h>


//#define MC2_READY 0x10

int main(void)
{
	uint16 distanceMeasured;
		SREG |= (1<<7); /*Enable the interrupts*/

		Ultrasonic_init(); /*initialize the ULTRASONIC SENSOR*/

	UART_init(9600);

    while(1)
    {
    	distanceMeasured = Ultrasonic_readDistance();
    	_delay_ms(10);
    	UART_sendByte(distanceMeasured);

    }
}

