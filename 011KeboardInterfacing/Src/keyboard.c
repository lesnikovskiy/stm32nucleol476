#include "keyboard.h"

// R1 - PA6
// R2 - PA7
// R3 - PB6
// R4 - PC7
// C1 - PA9
// C2 - PA8
// C3 - PB10

static const PinConfig rows[] = { { GPIOA, 6 }, { GPIOA, 7 }, { GPIOB, 6 }, {
GPIOC, 7 } };
static const PinConfig cols[] = { { GPIOA, 9 }, { GPIOA, 8 }, { GPIOB, 10 } };

static const char keys[4][3] = { { '1', '2', '3' }, { '4', '5', '6' }, { '7', '8', '9' }, { '*', '0', '#' }, };

void setup_ports(void) {
	// Enable AHB2 Ports A, B, C
	RCC->AHB2ENR |= (1 << 0) | (1 << 1) | (1 << 2);
}

void setup_keyboard(void) {
	// 1. Configure rows as Output, Open-Drain
	for (int i = 0; i < 4; i++) {
		rows[i].port->MODER &= ~(3 << (rows[i].pin * 2));
		rows[i].port->MODER |= (1 << (rows[i].pin * 2));  // Set as Output
		rows[i].port->OTYPER |= (1 << rows[i].pin);       // Set as Open-Drain
		rows[i].port->PUPDR &= ~(3 << (rows[i].pin * 2)); // No Pull-up/down
		rows[i].port->ODR |= (1 << rows[i].pin);          // Set to High (Idle)
	}

	// 2. Configure columns as Input with Pull-up
	for (int i = 0; i < 3; i++) {
		cols[i].port->MODER &= ~(3 << (cols[i].pin * 2)); // Set as Input
		cols[i].port->PUPDR &= ~(3 << (cols[i].pin * 2));
		cols[i].port->PUPDR |= (1 << (cols[i].pin * 2)); // Enable Pull-up
	}
}

char get_key(void) {
	for (int r = 0; r < 4; r++) {
		// Activate current row by pulling it LOW
		rows[r].port->ODR &= ~(1 << rows[r].pin);

		// Allow voltage to settle (signal stabilization)
		delay_us(50);

		// Check each column in the active row
		for (int c = 0; c < 3; c++) {
			// If IDR reads 0, the button at [row][col] is pressed
			if (!(cols[c].port->IDR & (1 << cols[c].pin))) {
				// IMPORTANT: Reset row to HIGH before returning
				rows[r].port->ODR |= (1 << rows[r].pin);
				return keys[r][c];
			}
		}

		// Deactivate current row by pulling it HIGH before moving to next
		rows[r].port->ODR |= (1 << rows[r].pin);
	}

	// No key pressed
	return 0;
}
