#include "keyboard.h"

void setup_ports(void) {
	// Enable AHB2 Ports A, B, C
	RCC->AHB2ENR |= (1 << 0) | (1 << 1) | (1 << 2);
}
