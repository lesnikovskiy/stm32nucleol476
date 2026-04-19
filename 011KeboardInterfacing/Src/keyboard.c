#include "keyboard.h"

// R1 - PA6
// R2 - PA7
// R3 - PB6
// R4 - PC7
// C1 - PA9
// C2 - PA8
// C3 - PB10

void setup_ports(void) {
	// Enable AHB2 Ports A, B, C
	RCC->AHB2ENR |= (1 << 0) | (1 << 1) | (1 << 2);
}

void setup_row1(void) {
	// PA6 - Mode OUTPUT PUPDR Open Drain
	GPIOA->MODER &= ~(3 << 12);
	GPIOA->MODER |= (1 << 12);
	GPIOA->OTYPER |= (1 << 6);
	GPIOA->PUPDR &= ~(3 << 12);
}

void setup_row2(void) {
	// PA7 - Mode OUTPUT PUPDR Open Drain
	GPIOA->MODER &= ~(3 << 14);
	GPIOA->MODER |= (1 << 14);
	GPIOA->OTYPER |= (1 << 7);
	GPIOA->PUPDR &= ~(3 << 14);
}

void setup_row3(void) {
	// PB6 - Mode OUTPUT PUPDR Open Drain
	GPIOB->MODER &= ~(3 << 12);
	GPIOB->MODER |= (1 << 12);
	GPIOB->OTYPER |= (1 << 6);
	GPIOB->PUPDR &= ~(3 << 12);
}

void setup_row4(void) {
	// PC7 - Mode OUTPUT PUPDR Open Drain
	GPIOC->MODER &= ~(3 << 14);
	GPIOC->MODER |= (1 << 14);
	GPIOC->OTYPER |= (1 << 7);
	GPIOC->PUPDR &= ~(3 << 14);
}

void setup_col1(void) {
	// PA9 - Mode INPUT PUPDR Pull up
	GPIOA->MODER &= ~(3 << 18);
	GPIOA->PUPDR &= ~(3 << 18);
	GPIOA->PUPDR |= (1 << 18);
}

void setup_col2(void) {
	// PA8 - Mode INPUT PUPDR Pull up
	GPIOA->MODER &= ~(3 << 16);
	GPIOA->PUPDR &= ~(3 << 16);
	GPIOA->PUPDR |= (1 << 16);
}

void setup_col3(void) {
	// PB10 - Mode INPUT PUPDR Pull up
	GPIOB->MODER &= ~(3 << 20);
	GPIOB->PUPDR &= ~(3 << 20);
	GPIOB->PUPDR |= (1 << 20);
}

char get_key(void) {
	// Set all rows to HIGH (PA6, PA7, PB6, PC7)
	GPIOA->ODR |= (1 << 6) | (1 << 7);
	GPIOB->ODR |= (1 << 6);
	GPIOC->ODR |= (1 << 7);

	// Check the first row PA6
	GPIOA->ODR &= ~(1 << 6);

	delay_us(50);

	// check columns for low state (PA9, PA8, PB10)
	if (!(GPIOA->IDR & (1 << 9)))
		return '1';
	if (!(GPIOA->IDR & (1 << 8)))
		return '2';
	if (!(GPIOB->IDR & (1 << 10)))
		return '3';

	// Reset PA6 to HIGH
	GPIOA->ODR |= (1 << 6);

	// Check the second row PA7
	GPIOA->ODR &= ~(1 << 7);

	delay_us(50);

	// check columns for low state (PA9, PA8, PB10)
	if (!(GPIOA->IDR & (1 << 9)))
		return '4';
	if (!(GPIOA->IDR & (1 << 8)))
		return '5';
	if (!(GPIOB->IDR & (1 << 10)))
		return '6';

	// Reset PA7 to HIGH
	GPIOA->ODR |= (1 << 7);

	// Check the third row PB6
	GPIOB->ODR &= ~(1 << 6);

	delay_us(50);

	// check columns for low state (PA9, PA8, PB10)
	if (!(GPIOA->IDR & (1 << 9)))
		return '7';
	if (!(GPIOA->IDR & (1 << 8)))
		return '8';
	if (!(GPIOB->IDR & (1 << 10)))
		return '9';

	// Reset PB6 to HIGH
	GPIOB->ODR |= (1 << 6);

	// Check the fourth row PC7
	GPIOC->ODR &= ~(1 << 7);

	delay_us(50);

	// check columns for low state (PA9, PA8, PB10)
	if (!(GPIOA->IDR & (1 << 9)))
		return '*';
	if (!(GPIOA->IDR & (1 << 8)))
		return '0';
	if (!(GPIOB->IDR & (1 << 10)))
		return '#';

	return 0;
}
