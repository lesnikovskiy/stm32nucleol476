#include <stdint.h>
#include <stdio.h>

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

#define RCC_BASE   (0x40021000UL)
#define GPIOC_BASE (0x48000800UL)
#define EXTI_BASE  (0x40010400UL)

#define RCC_AHB2ENR (*(volatile uint32_t*)(RCC_BASE + 0x4C))
#define RCC_APB2ENR (*(volatile uint32_t*)(RCC_BASE + 0x60))
#define NVIC ((NVIC_TypeDef *) 0xE000E100UL)

// PC13 - Button Pin

// Global shared variable between the global and ISR
uint8_t g_button_pressed = 0;
uint32_t g_button_press_count = 0;

void button_init(void);

int main(void) {
	/* Loop forever */
	for (;;);
}

void button_init(void) {

}
