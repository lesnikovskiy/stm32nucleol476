#include <stdint.h>
#include "main.h"

void delay(void);

int main(void) {
	// 1. Enable clock for GPIOA Peripheral
	AHB2_ENR->GPIOAEN = HIGH;

	// 2. Configure a mode of PA5 as Output
	GPIOA_MODER->Pin_5 = OUTPUT_MODE;

	// 3. Put data to data register
	GPIOA_ODR->Pin_5 = HIGH;

	/* Loop forever */
	for (;;) {
		GPIOA_ODR->Pin_5 = HIGH;
		delay();
		GPIOA_ODR->Pin_5 = LOW;
		delay();
	}
}

void delay(void) {
	for (volatile uint32_t i = 0; i < 400000; i++);
}
