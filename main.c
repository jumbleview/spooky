/*
 * main.c
 *
 * Created: 9/28/2024 7:44:14 PM
 *  Author: jumbleview
 */ 

#include <xc.h>

#include <avr/io.h>
//  CKDIV8 set. 1 MHz;
#define 	F_CPU   1000000UL 
//  CKDIV8 cleared. 8 MHz;
// #define 	F_CPU   8000000UL
#include <util/delay.h>
#include <stdlib.h>

#define PinOutHigh(bit) PORTB |= (1 << (bit))

#define PinOutLow(bit) PORTB &= ~(1 << (bit))

#define LEFT_EYE	PB1
#define RIGHT_EYE	PB0
#define MOUTH		PB4
#define LEFT_BODY	PB2
#define RIGHT_BODY	PB3



void allLight() {
	PinOutLow(LEFT_EYE);
	PinOutLow(RIGHT_EYE);
	PinOutLow(MOUTH);
	PinOutHigh(LEFT_BODY);
	PinOutHigh(RIGHT_BODY);
}

void allDark() {
	PinOutHigh(LEFT_EYE);
	PinOutHigh(RIGHT_EYE);
	PinOutHigh(MOUTH);
	PinOutLow(LEFT_BODY);
	PinOutLow(RIGHT_BODY);
}

void faceDark() {
	PinOutHigh(LEFT_EYE);
	PinOutHigh(RIGHT_EYE);
	PinOutHigh(MOUTH);
}




void delay(int delay) {
	switch(delay) {
		case 0:
			_delay_ms(250.0);
			break;
		case 1:
			_delay_ms(1000.0);
			break;
		case 2:
			_delay_ms(2000.0);
			break;
		case 3:
			_delay_ms(3000.0);
			break;
		case 4:
			_delay_ms(4000.0);
			break;
		default:
			_delay_ms(5000.0);
	}
}


int main(void)
{
	DDRB |= (1 << DDB0) | (1 << DDB1) | (1 << DDB2) | (1 << DDB3) | (1 << DDB4);
	allLight();
	_delay_ms(2000.0);
    while(1)
    {
		// dark body, light face
		if (rand()%3 == 0) {
			PinOutLow(LEFT_BODY);
			PinOutLow(RIGHT_BODY);
			delay(rand()%5);
		}
		// dark body, dark mouth, light eyes
		PinOutHigh(MOUTH);
		delay(rand()%5);
		// all dark
		faceDark();
		delay(rand()%5);
		// Light one eye or mouth
		int mod = rand()%3;
		switch(mod) {
			case 0:
				PinOutLow(LEFT_EYE); break;	
			case 1:
				PinOutLow(RIGHT_EYE); break;	
			default:
				PinOutLow(MOUTH);	
		}
		delay(rand()%5);
		// Light eyes and mouth
		PinOutLow(LEFT_EYE);
		PinOutLow(RIGHT_EYE);
		PinOutLow(MOUTH);
		delay(rand()%5);
		// Light half Body
		if (rand()%2 == 0) {
			PinOutHigh(LEFT_BODY);
		} else {
			PinOutHigh(RIGHT_BODY);
		}
		_delay_ms(300.0);
		// all light
		allLight();
		delay(3000.0); 
    }
}