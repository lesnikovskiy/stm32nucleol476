#include <stdint.h>
#include "main.h"

void delay(void);

int main(void) {
	RCC_AHB2ENR_t volatile *const AHB2_ENR = (RCC_AHB2ENR_t*) 0x4002104C;
	GPIOx_MODE_t volatile *const GPIOA_MODER = (GPIOx_MODE_t*) 0x48000000;
	GPIOx_ODR_t volatile *const GPIOA_ODR = (GPIOx_ODR_t*) 0x48000014;

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
