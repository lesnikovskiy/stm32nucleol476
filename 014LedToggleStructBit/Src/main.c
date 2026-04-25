#include <stdint.h>
#include "main.h"

int main(void) {
	RCC_AHB2ENR_t volatile *const AHB2_ENR = (RCC_AHB2ENR_t*) 0x4002104C;
	GPIOx_MODE_t volatile *const GPIOA_MODER = (GPIOx_MODE_t*) 0x48000000;
	GPIOx_ODR_t volatile *const GPIOA_ODR = (GPIOx_ODR_t*) 0x48000014;

//	volatile uint32_t *const AHB2_ENR = (volatile uint32_t*) 0x4002104C;
//	volatile uint32_t *const GPIOA_MODER = (volatile uint32_t*) 0x48000000;
//	volatile uint32_t *const GPIOA_ODR = (volatile uint32_t*) 0x48000014;

// 1. Enable clock for GPIOA Peripheral
	AHB2_ENR->GPIOAEN = 1;

	// 2. Configure a mode of PA5 as Output
	GPIOA_MODER->Pin_5 = 1;
//	*GPIOA_MODER &= ~(3 << 10);
//	*GPIOA_MODER |= (1 << 10);

// 3. Put data to data register
	GPIOA_ODR->Pin_5 = 1;
//	*GPIOA_ODR &= ~(1 << 5);
//	*GPIOA_ODR |= (1 << 5);

	/* Loop forever */
	for (;;) {
//		*GPIOA_ODR ^= (1 << 5);
		GPIOA_ODR->Pin_5 ^= 1;
		for (volatile uint32_t i = 0; i < 400000; i++);
	}
}
