 /******************************************************************************
 *
 * Module: ULTRASONIC SENSOR
 *
 * File Name: ultrasonic_sensor.c
 *
 * Description: Source file for the ULTRASONIC SENSOR driver
 *
 * Author: Basma Ashraf Kamel
 *
 *
 *
 *******************************************************************************/

#include "ultrasonic_sensor.h"
#include "icu.h"
#include "gpio.h"
#include "std_types.h"
#include <util/delay.h>

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

volatile uint8 g_count = 0; /*to count the number of detected edges*/
uint16 g_icuValue; /*to store the value of Icu*/
uint16 distance = 0; /*to store the distance value*/

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/


void Ultrasonic_init(void){
	/*configure the ICU with F_CPU_8 and detects RISING edge*/
	Icu_ConfigType myIcu = {F_CPU_8 , RISING};
	Icu_init(&myIcu); /*calling Icu_init() to initialize the Icu*/
	/*to set the callback function with Ultrasonic_edgeProcessing to execute as ICU's ISR*/
	Icu_setCallBack(Ultrasonic_edgeProcessing);
	/*setup the trigger pin direction as output pin*/
	GPIO_setupPinDirection(PORTB_ID , TRIGGER_PIN , PIN_OUTPUT);
}


void Ultrasonic_Trigger(void){
	GPIO_writePin(PORTB_ID , TRIGGER_PIN , LOGIC_HIGH); /*making the trigger pin high*/
	/*making the trigger pin high delay 10micro-sec to make the ultrasonic sensor get ready*/
	_delay_us(10);
	GPIO_writePin(PORTB_ID , TRIGGER_PIN , LOGIC_LOW); /*making the trigger pin low*/
}


uint16 Ultrasonic_readDistance(void){
	Ultrasonic_Trigger(); /*calling the "Ultrasonic_Trigger" function*/
	if(g_count == 2){
		g_count = 0; /*reset the edge counter*/
		distance = g_icuValue /58.8; /*calculate the distance in Centimeter*/
	}
	return distance; /*return the measured distance*/
}

void Ultrasonic_edgeProcessing(void){
	g_count++;
	if(g_count == 1){
		/*
		 * Clear the timer counter register to start measurements from the
		 * first detected rising edge
		 */
		Icu_clearTimerValue();
		/* Detect falling edge */
		Icu_setEdgeDetectionType(FALLING);
	}else if(g_count == 2){
		/* Store the High time value */
		g_icuValue = Icu_getInputCaptureValue();
		/* Clear the timer counter register to start measurements again */
		Icu_clearTimerValue();
		/* Detect rising edge */
		Icu_setEdgeDetectionType(RISING);
	}
}
