#include "define.h"
#include <avr/io.h>

#include "HCSR04.h"

int main(void) {
	HCSR04 ultrasonicSensor("D7", "B0", 200);
	
    while (1) {
		int range = ultrasonicSensor.pingCm();
	}
}

