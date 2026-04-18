// R1 - PA6
// R2 - PA7
// R3 - PB6
// R4 - PC7
// C1 - PA9
// C2 - PA8
// C3 - PB10

#include <stdio.h>
#include <stdint.h>
#include "stm32l476rg.h"
#include "itm.h"
#include "keyboard.h"

int main(void) {
	ITM_Init();

	setup_ports();

	// Configure PB2 as Alternate Function 0 (SYS_JTDO-SWO)
//	GPIOB->MODER &= ~(3 << 6);
//	GPIOB->MODER |= (2 << 6); // 10 - AF
//	GPIOB->AFRL &= ~(0xF << 12); // AF0 for pin 3 (bits 12-15)

// Make columns INPUT
// PB3, PB4, PB5 pins set INPUT and pull up resister
//	GPIOB->MODER &= ~(0x3F << 4); // 0x3F = 111111
//	GPIOB->PUPDR &= ~(0x3F << 4); // Clear bits PUPDR[3-5]
//	GPIOB->PUPDR |= (0x15 << 4); // 0x15 = 010101 (O1 - PULL UP)

	// Make ROW pins input
	// PA8 and PA9 Output Mode and pull up resistor
//	GPIOA->MODER &= ~(0xF << 14); // 0xF = 1111
//	GPIOA->MODER |= (0x5 << 14); // 0x5 = 0101
//	GPIOA->PUPDR &= ~(0xF << 14);
//	GPIOA->PUPDR |= (0x5 << 14); // 0x5 = 0101
	// PB10 OUTPUT & pull up
//	GPIOB->MODER &= ~(0x3 << 18); // 0x3 = 11
//	GPIOB->MODER |= (1 << 18); // 01 OUTPUT
//	GPIOB->PUPDR &= ~(0x3 << 18); // Clear pupdr
//	GPIOB->PUPDR |= (1 << 18);

	// PC7 OUTPUT & pull up
//	GPIOC->MODER &= ~(0x3 << 12); // 0x3 = 11
//	GPIOC->MODER |= (1 << 12); // 01 OUTPUT
//	GPIOC->PUPDR &= ~(0x3 << 12); // Clear pupdr
//	GPIOC->PUPDR |= (1 << 12);

	printf("ITM is working successfully\n");

	/* Loop forever */
	while (1) {
		// Check for C1 R1
//		if (((GPIOB->ODR << 4) == 0) && ((GPIOC->IDR << 7) == 0)) {
//			// BUTTON 1 is pressed
//		}
	}
}
