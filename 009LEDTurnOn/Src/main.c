#include <stdint.h>

int main(void) {
	uint32_t *const gpioa_peripheral = (uint32_t*) 0x4002104C;
	uint32_t *const gpioa_moder = (uint32_t*) 0x48000000;
	uint32_t *const gpioa_data = (uint32_t*) 0x48000014;
//	uint32_t *const gpioa_bsrr = (uint32_t*) 0x48000018;

	// 1. Enable clock for GPIOA Peripheral
	*gpioa_peripheral |= (1 << 0);

	// 2. Configure a mode of PA5 as Output
	*gpioa_moder &= ~(3 << 10);
	*gpioa_moder |= (1 << 10);

	// 3. Put data to data register
	*gpioa_data &= ~(1 << 5);
	*gpioa_data |= (1 << 5);
	//*gpioa_bsrr |= (1 << 5);

	/* Loop forever */
	for (;;) {
		*gpioa_data ^= (1 << 5);
		for (volatile uint32_t i = 0; i < 400000; i++);
	}
}
