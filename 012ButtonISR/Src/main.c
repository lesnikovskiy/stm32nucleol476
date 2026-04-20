#include <stdint.h>
#include <stdio.h>

// Refer to PM0214 Table 49. NVIC register map and reset values
typedef struct {
	volatile uint32_t ISER[8]; /* 0x000: Interrupt Set Enable Registers */
	uint32_t RESERVED0[24];
	volatile uint32_t ICER[8]; /* 0x080: Interrupt Clear Enable Registers */
	uint32_t RSERVED1[24];
	volatile uint32_t ISPR[8]; /* 0x100: Interrupt Set Pending Registers */
	uint32_t RESERVED2[24];
	volatile uint32_t ICPR[8]; /* 0x180: Interrupt Clear Pending Registers */
	uint32_t RESERVED3[24];
	volatile uint32_t IABR[8]; /* 0x200: Interrupt Active Bit Registers */
	uint32_t RESERVED4[56];
	volatile uint8_t IP[240]; /* 0x300: Interrupt Priority Registers (8-bit!) */
	uint32_t RESERVED5[644];
	volatile uint32_t STIR; /* 0xE00: Software Trigger Interrupt Register */
} NVIC_TypeDef;

#define RCC_BASE    (0x40021000UL)
#define GPIOA_BASE  (0x48000000UL)
#define GPIOC_BASE  (0x48000800UL)
#define USART2_BASE (0x40004400UL)
#define EXTI_BASE   (0x40010400UL)
#define SYSCFG_BASE (0x40010000UL)
// Refer to PM0214 Table 49. NVIC register map and reset values
#define NVIC_BASE   (0xE000E100UL) // PM0214 4.1

#define RCC_AHB2ENR    (*(volatile uint32_t*)(RCC_BASE + 0x4C))
#define RCC_APB1ENR1   (*(volatile uint32_t*)(RCC_BASE + 0x58))
#define RCC_APB2ENR    (*(volatile uint32_t*)(RCC_BASE + 0x60))
#define GPIOA_MODER    (*(volatile uint32_t*)(GPIOA_BASE + 0x00))
#define GPIOA_PUPDR    (*(volatile uint32_t*)(GPIOA_BASE + 0x0C))
#define GPIOA_AFRL     (*(volatile uint32_t*)(GPIOA_BASE + 0x20))
#define GPIOC_MODER    (*(volatile uint32_t*)(GPIOC_BASE + 0x00))
#define GPIOC_PUPDR    (*(volatile uint32_t*)(GPIOC_BASE + 0x0C))
#define USART_CR1      (*(volatile uint32_t*)(USART2_BASE + 0x00))
#define USART_BRR      (*(volatile uint32_t*)(USART2_BASE + 0x0C))
#define USART_ISR      (*(volatile uint32_t*)(USART2_BASE + 0x1C))
#define USART_TDR      (*(volatile uint32_t*)(USART2_BASE + 0x28))
#define EXTI_IMR1      (*(volatile uint32_t*)(EXTI_BASE + 0x00))
#define EXTI_FTSR1     (*(volatile uint32_t*)(EXTI_BASE + 0x0C))
#define EXTI_PR1       (*(volatile uint32_t*)(EXTI_BASE + 0x14))
#define SYSCFG_EXTICR4 (*(volatile uint32_t*)(SYSCFG_BASE + 0x14))
#define NVIC_ISER1     (*(volatile uint32_t*)(NVIC_BASE + 0x04))

// PC13 - Button Pin

// Global shared variable between the global and ISR
uint8_t volatile g_button_pressed = 0;
uint32_t g_button_press_count = 0UL;

void button_init(void);
void usart_init(void);
void usart_send_char(char ch);
void usart_send_str(const char *str);

int main(void) {
	button_init();
	usart_init();

	printf("USART has been initialized\r\n");

	while (1) {
		if (g_button_pressed) {
			// Disable interrupt
			EXTI_IMR1 &= ~(1 << 13);

			g_button_pressed = 0;
			g_button_press_count++;

			// debounce
			for (uint32_t volatile i = 0; i < 20000; i++);

			// Enable interrupt
			EXTI_IMR1 |= (1 << 13);

			printf("Button is pressed : %lu\r\n", g_button_press_count);
		}
	}
}

void button_init(void) {
	// Enable Port C for PC13
	RCC_AHB2ENR |= (1 << 2);

	// Enable SYS_CFGEN
	RCC_APB2ENR |= (1 << 0);

	// Setup PC13 Input with Pull up resistor
	GPIOC_MODER &= ~(3 << (13 * 2));
	GPIOC_PUPDR &= ~(3 << (13 * 2));
	GPIOC_PUPDR |= (1 << (13 * 2));

	// Map EXTI13 to PORT C
	// in EXITCR4 bits 4-7 control line 13. 0010 is Port C.
	// refer to RM0351 9.26 SYSCFG external interrupt configuration register 4
	SYSCFG_EXTICR4 &= ~(0xF << 4);
	SYSCFG_EXTICR4 |= (2 << 4);

	// Configure EXIT Line 13
	EXTI_FTSR1 |= (1 << 13); // Falling edge (button press)
	EXTI_IMR1 |= (1 << 13);  // Unmask interrupt

	// Refer to RM0351 13.3 Interrupt and exception vectors Table 58
	// Enable NVIC IRQ 40 EXTI15_10
	// IRQ 40 is bit 8 of ISER[1] (40 - 32 = 8)
	NVIC_ISER1 |= (1 << 8);
}

void usart_init(void) {
	// Enable Port A
	RCC_AHB2ENR |= (1 << 0);

	// Enable USART2
	RCC_APB1ENR1 |= (1 << 17);

	// Set PA2(TX) and PA3(RX) in AF Mode (10)
	GPIOA_MODER &= ~((3 << 4) | (3 << 6));
	GPIOA_MODER |= (2 << 4) | (2 << 6);

	// Set PA2(TX) and PA3(RX) pull up resistor
	GPIOA_PUPDR &= ~((3 << 4) | (3 << 6));
	GPIOA_PUPDR |= (1 << 4) | (1 << 6);

	// Set PA2(TX) and PA3(RX) AF7
	GPIOA_AFRL &= ~((0xF << 8) | (0xF << 12));
	GPIOA_AFRL |= (0x7 << 8) | (0x7 << 12);

	// Set Baud Rate
	USART_BRR = 4000000 / 115200;

	// Enable TX, RX and USART
	USART_CR1 |= (1 << 3) | (1 << 2) | (1 << 0);
}

void usart_send_char(char ch) {
	while (!(USART_ISR & (1 << 7)));
	USART_TDR = ch;
}

void usart_send_str(const char *str) {
	while (*str) {
		usart_send_char(*str++);
	}
}

void EXTI15_10_IRQHandler(void) {
	if (EXTI_PR1 & (1 << 13)) {
		g_button_pressed = 1;
		EXTI_PR1 |= (1 << 13); // Clear pending bit by writing 1
	}
}
