#include "usart.h"

void USART_Init(void) {
	// Enable UART2 Clock
	RCC->APB1ENR1 |= (1 << 17);
	// Enable Port A
	RCC->AHB2ENR |= (1 << 0);

	// Set PA2 (TX) P3(RX) in AF mode (10)
	GPIOA->MODER &= ~((3 << 4) | (3 << 6));
	GPIOA->MODER |= (2 << 4) | (2 << 6);

	// Set AF7 (0111) for PA2 PA3
	GPIOA->AFRL &= ~((0xF << 8) | (0xF << 12));
	GPIOA->AFRL |= (0x7 << 8) | (0x7 << 12);

	// Set Baud Rate
	USART->BRR = 4000000 / 115200;
	// Enable TX, RX and USART
	USART->CR1 |= (1 << 3) | (1 << 2) | (1 << 0);
}

void USART_send_char(const char ch) {
	// wait until TxE transmt not empty
	while (!(USART->ISR & (1 << 7)));
	USART->TDR = ch;
}

void USART_send_str(const char *str) {
	while (*str) {
		USART_send_char(*str++);
	}
}
