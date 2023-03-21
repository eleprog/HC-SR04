#include "HCSR04.h"

#include <avr/io.h>
#include <util/delay.h>

HCSR04::HCSR04(const char trig[2], const char echo[2], uint8_t range = 255) {
	if(trig[0] == 'B') {
		pinTrig.pDdr	= &DDRB;
		pinTrig.pPort	= &PORTB;
	}
	else if(trig[0] == 'C')	{
		pinTrig.pDdr	= &DDRC;
		pinTrig.pPort	= &PORTC;
	}
	else if(trig[0] == 'D')	{
		pinTrig.pDdr	= &DDRD;
		pinTrig.pPort	= &PORTD;
	}
	
	if(echo[0] == 'B')		{
		pinEcho.pDdr	= &DDRB;
		pinEcho.pPin	= &PINB;
	} 
	else if(echo[0] == 'C')	{
		pinEcho.pDdr	= &DDRC;
		pinEcho.pPin	= &PINC;
	}
	else if(echo[0] == 'D')	{
		pinEcho.pDdr	= &DDRC;
		pinEcho.pPin	= &PINC;
	}
	
	pinTrig.pinNum = 1<<(trig[1] - '0');
	pinEcho.pinNum = 1<<(echo[1] - '0');
	
	maxRange = range;
	
	this->gpioInit();
}

void HCSR04::gpioInit() {
	*pinEcho.pDdr	&= ~pinEcho.pinNum;
	*pinTrig.pDdr	|= pinTrig.pinNum;
	*pinTrig.pPort	&= ~pinTrig.pinNum;
}

int HCSR04::pingCm() {
	this->startPulseGenerated();
	return this->echoDistanceCm();
}

void HCSR04::startPulseGenerated() {
	*pinTrig.pPort |= pinTrig.pinNum;
	_delay_us(10);
	*pinTrig.pPort &= ~pinTrig.pinNum;
}

uint8_t HCSR04::echoDistanceCm() {
	TCCR0 = (1<<CS22)|(0<<CS21)|(1<<CS20);
	_delay_us(500);
	TCNT0 = 0;
	while(TCNT0 < 240 && *pinEcho.pPin & pinEcho.pinNum);
	uint8_t lenght = TCNT0;
	
	lenght = lenght * 1000000 / (F_CPU / 1024) / 58;
	
	return lenght;
}

HCSR04::~HCSR04() {
} 
