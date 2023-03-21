#pragma once

#include "define.h"
#include <avr/io.h>

#ifndef F_CPU
	#warning "F_CPU not defined for <HCSR04.h>"
#endif

class HCSR04 {
	private:
		struct PinData_ {
			volatile uint8_t* pDdr;
			volatile uint8_t* pPort;
			volatile uint8_t* pPin;
			uint8_t pinNum;
		};
			
		PinData_ pinTrig_;
		PinData_ pinEcho_;
		
		uint8_t maxRange_;

	public:
		HCSR04(const char[2], const char[2], uint8_t);
		~HCSR04();
		
		int pingCm();
		
	private:
		void gpioInit();
		void startPulseGenerated();
		uint8_t echoDistanceCm();
};