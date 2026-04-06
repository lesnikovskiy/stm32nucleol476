#include <stdint.h>

// --- Addresses ---
#define RCC_BASE              (0x40021000UL)
#define RCC_AHB2ENR           (*(volatile uint32_t *)(RCC_BASE + 0x4C))

#define GPIOA_BASE            (0x48000000UL)
#define GPIOA_MODER           (*(volatile uint32_t *)(GPIOA_BASE + 0x00))
#define GPIOA_BSRR            (*(volatile uint32_t *)(GPIOA_BASE + 0x18))

#define GPIOC_BASE            (0x48000800UL)
#define GPIOC_MODER           (*(volatile uint32_t *)(GPIOC_BASE + 0x00))
#define GPIOC_IDR             (*(volatile uint32_t *)(GPIOC_BASE + 0x10)) // Input Data Register

// --- Bits ---
#define GPIOAEN               (1U << 0) // Bit to enable Port A
#define GPIOCEN               (1U << 2) // Bit to enable Port C
#define LED_PIN               (1U << 5) // PA5
#define BUTTON_PIN            (1U << 13) // PC13

int main(void) {
	// 1. Enable Clock for Port A (LED) and Port C (Button)
	RCC_AHB2ENR |= (GPIOAEN | GPIOCEN);

	// 2. Configure PA5 (LED) as Output (01 in bits 11:10)
	GPIOA_MODER &= ~(3U << 10);
	GPIOA_MODER |= (1U << 10);

	// 3. Configure PC13 (Button) as Input (00 in bits 27:26)
	// By default it's already 00 after reset, but let's be explicit:
	GPIOC_MODER &= ~(3U << 26);

	while (1) {
		// 4. Check if button is pressed
		// On Nucleo, the button pulls the signal to LOW (0) when pressed.
		// So (GPIOC_IDR & BUTTON_PIN) == 0 means "Pressed".
		if (!(GPIOC_IDR & BUTTON_PIN)) {
			// Button is PRESSED -> LED ON
			GPIOA_BSRR = LED_PIN;
		} else {
			// Button is RELEASED -> LED OFF
			GPIOA_BSRR = (LED_PIN << 16);
		}
	}
}
