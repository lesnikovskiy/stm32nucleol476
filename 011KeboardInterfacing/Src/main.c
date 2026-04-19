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
//#include "itm.h"
#include "usart.h"
#include "keyboard.h"

int main(void) {
	// ITM_Init();
	USART_Init();

	setup_ports();

	setup_row1();
	setup_row2();
	setup_row3();
	setup_row4();

	setup_col1();
	setup_col2();
	setup_col3();

	printf("ITM is working successfully\r\n");

	char last_key = 0;

	while (1) {
		char current_key = get_key();

		if (current_key != 0 && current_key != last_key) {
			printf("%c\r\n", current_key);
		}

		last_key = current_key;

		for (int i = 0; i < 50000; i++)
			__asm("nop");
	}
}
