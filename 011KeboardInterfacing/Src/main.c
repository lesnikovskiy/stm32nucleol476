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
#include "delay.h"
#include "usart.h"
#include "keyboard.h"

int main(void) {
	// ITM_Init();
	USART_Init();

	setup_ports();
	setup_keyboard();

	// Setup PA5 (LED) to OUTPUT
	GPIOA->MODER &= ~(3 << 10);
	GPIOA->MODER |= (1 << 10);

	// Setup PC13 (Button) to INPUT
	GPIOC->MODER &= ~(3 << 26);

	printf("UART is initialized successfully\r\n");

	char last_key = 0;
	static uint8_t btn_last = 1;

	while (1) {
		// Read key from keyboard
		char current_key = get_key();

		if (current_key != 0 && current_key != last_key) {
			printf("%c\r\n", current_key);
			delay_ms(20);
		}

		last_key = current_key;

		// Read key from terminal
		if (USART_is_data_available()) {
			char rx_char = USART_read_char();
			// echo
			USART_send_char(rx_char);

			if (rx_char == 'l' || rx_char == 'L') {
				GPIOA->ODR ^= (1 << 5);
				printf("\r\nLED Toggled\r\n");
			}
		}

		// Toggle LED if PC13 (User Button) pressed
		uint8_t btn_now = (GPIOC->IDR >> 13) & 0x1;

		if (btn_now == 0 && btn_last == 1) {
			GPIOA->ODR ^= (1 << 5);
			printf("Button pressed. LED toggled.\r\n");
			delay_ms(20);
		}
		btn_last = btn_now;
	}
}
