#ifndef STM32L476RG_H_
#define STM32L476RG_H_

#include <stdint.h>

typedef struct {
	volatile uint32_t PORT[32]; /* 0x000 to 0x07C: Stimulus Ports 0-31 */
	uint32_t RESERVED0[864]; /* 0x080 to 0xDF0: Reserved gap */
	volatile uint32_t TER; /* 0xE00: Trace Enable Register */
	uint32_t RESERVED1[15]; /* 0xE04 to 0xE3C: Reserved */
	volatile uint32_t TPR; /* 0xE40: Trace Privilege Register */
	uint32_t RESERVED2[15]; /* 0xE44 to 0xE7C: Reserved */
	volatile uint32_t TCR; /* 0xE80: Trace Control Register */
	uint32_t RESERVED3[75]; /* 0xE84 to 0xFA8: Reserved */
	volatile uint32_t LAR; /* 0xFB0: Lock Access Register (Write 0xC5ACCE55 to unlock) */
	volatile uint32_t LSR; /* 0xFB4: Lock Status Register */
} ITM_TypeDef;

typedef struct {
	volatile uint32_t CR; /* 0x00 */
	volatile uint32_t ICSCR; /* 0x04 */
	volatile uint32_t CFGR; /* 0x08 */
	volatile uint32_t PLLCFGR; /* 0x0C */
	volatile uint32_t PLLSAI1CFGR; /* 0x10 */
	volatile uint32_t PLLSAI2CFGR; /* 0x14 */
	volatile uint32_t CIER; /* 0x18 */
	volatile uint32_t CIFR; /* 0x1C */
	volatile uint32_t CICR; /* 0x20 */
	uint32_t RESERVED0; /* 0x24 */
	volatile uint32_t AHB1RSTR; /* 0x28 */
	volatile uint32_t AHB2RSTR; /* 0x2C */
	volatile uint32_t AHB3RSTR; /* 0x30 */
	uint32_t RESERVED1; /* 0x34 */
	volatile uint32_t APB1RSTR1; /* 0x38 */
	volatile uint32_t APB1RSTR2; /* 0x3C */
	volatile uint32_t APB2RSTR; /* 0x40 */
	uint32_t RESERVED2; /* 0x44 */
	volatile uint32_t AHB1ENR; /* 0x48 */
	volatile uint32_t AHB2ENR; /* 0x4C */
	volatile uint32_t AHB3ENR; /* 0x50 */
	uint32_t RESERVED3; /* 0x54 */
	volatile uint32_t APB1ENR1; /* 0x58 */
	volatile uint32_t APB1ENR2; /* 0x5C */
	volatile uint32_t APB2ENR; /* 0x60 */
	uint32_t RESERVED4; /* 0x64 */
	volatile uint32_t AHB1SMENR; /* 0x68 */
	volatile uint32_t AHB2SMENR; /* 0x6C */
	volatile uint32_t AHB3SMENR; /* 0x70 */
	uint32_t RESERVED5; /* 0x74 */
	volatile uint32_t APB1SMENR1; /* 0x78 */
	volatile uint32_t APB1SMENR2; /* 0x7C */
	volatile uint32_t APB2SMENR; /* 0x80 */
	uint32_t RESERVED6; /* 0x84 */
	volatile uint32_t CCIPR; /* 0x88 */
	uint32_t RESERVED7; /* 0x8C */
	volatile uint32_t BDCR; /* 0x90 */
	volatile uint32_t CSR; /* 0x94 */
	volatile uint32_t CRRCR; /* 0x98 */
} RCC_TypeDef;

typedef struct {
	volatile uint32_t MODER; /* 0x00: (Input, Output, Alt, Analog) */
	volatile uint32_t OTYPER; /* 0x04:(Push-pull or Open-drain) */
	volatile uint32_t OSPEEDR; /* 0x08:(Low, Medium, High, Very High) */
	volatile uint32_t PUPDR; /* 0x0C: (None, Pull-up, Pull-down) */
	volatile uint32_t IDR; /* 0x10: Input Data */
	volatile uint32_t ODR; /* 0x14: Output Data */
	volatile uint32_t BSRR; /* 0x18: Bit Set Reset Register */
	volatile uint32_t LCKR; /* 0x1C: (Lock) */
	volatile uint32_t AFRL; /* 0x20: Alternate functions (pins 0-7) */
	volatile uint32_t AFRH; /* 0x24: Alternate functions (pins 8-15) */
	volatile uint32_t BRR; /* 0x28: Bit Reset Register */
	volatile uint32_t ASCR; /* 0x2C: Analog Switch Control */
} GPIO_TypeDef;

#define ITM_BASE    (0xE0000000UL)
#define RCC_BASE    (0x40021000UL)
#define GPIOA_BASE  (0x48000000UL)
#define GPIOB_BASE  (0x48000400UL)
#define GPIOC_BASE  (0x48000800UL)

#define ITM         ((ITM_TypeDef  *) ITM_BASE)
#define RCC         ((RCC_TypeDef  *) RCC_BASE)
#define GPIOA       ((GPIO_TypeDef *) GPIOA_BASE)
#define GPIOB       ((GPIO_TypeDef *) GPIOB_BASE)
#define GPIOC       ((GPIO_TypeDef *) GPIOC_BASE)

#define DEMCR       (*(volatile uint32_t *)0xE000EDFC)

#endif /* STM32L476RG_H_ */
