#pragma once

#include "define.h"
#include <avr/io.h>

#ifndef F_CPU
	#warning "F_CPU not defined for <HCSR04.h>"
#endif

class HCSR04 {
	private:
		struct PinData {
			volatile uint8_t* pDdr;
			volatile uint8_t* pPort;
			volatile uint8_t* pPin;
			uint8_t pinNum;
		};
			
		PinData pinTrig;
		PinData pinEcho;
		
		uint8_t maxRange;

	public:
		HCSR04(const char[2], const char[2], uint8_t);
		~HCSR04();
		
		int pingCm();
		
	private:
		void gpioInit();
		void startPulseGenerated();
		uint8_t echoDistanceCm();
};