#include "HCSR04.h"

#include <avr/io.h>
#include <util/delay.h>

HCSR04::HCSR04(const char trig[2], const char echo[2], uint8_t range = 255) {
	if(trig[0] == 'B') {
		pinTrig_.pDdr	= &DDRB;
		pinTrig_.pPort	= &PORTB;
	}
	else if(trig[0] == 'C')	{
		pinTrig_.pDdr	= &DDRC;
		pinTrig_.pPort	= &PORTC;
	}
	else if(trig[0] == 'D')	{
		pinTrig_.pDdr	= &DDRD;
		pinTrig_.pPort	= &PORTD;
	}
	
	if(echo[0] == 'B') {
		pinEcho_.pDdr	= &DDRB;
		pinEcho_.pPin	= &PINB;
	} 
	else if(echo[0] == 'C')	{
		pinEcho_.pDdr	= &DDRC;
		pinEcho_.pPin	= &PINC;
	}
	else if(echo[0] == 'D')	{
		pinEcho_.pDdr	= &DDRC;
		pinEcho_.pPin	= &PINC;
	}
	
	pinTrig_.pinNum = 1<<(trig[1] - '0');
	pinEcho_.pinNum = 1<<(echo[1] - '0');
	
	maxRange_ = range;
	
	this->gpioInit();
}

void HCSR04::gpioInit() {
	*pinEcho_.pDdr	&= ~pinEcho_.pinNum;
	*pinTrig_.pDdr	|= pinTrig_.pinNum;
	*pinTrig_.pPort	&= ~pinTrig_.pinNum;
}

int HCSR04::pingCm() {
	this->startPulseGenerated();
	return this->echoDistanceCm();
}

void HCSR04::startPulseGenerated() {
	*pinTrig_.pPort |= pinTrig_.pinNum;
	_delay_us(10);
	*pinTrig_.pPort &= ~pinTrig_.pinNum;
}

uint8_t HCSR04::echoDistanceCm() {
	TCCR0 = (1<<CS22)|(0<<CS21)|(1<<CS20);
	_delay_us(500);
	TCNT0 = 0;
	while(TCNT0 < 240 && *pinEcho_.pPin & pinEcho_.pinNum);
	uint8_t lenght = TCNT0;
	
	lenght = lenght * 1000000 / (F_CPU / 1024) / 58;
	
	return lenght;
}

HCSR04::~HCSR04() {
} 
