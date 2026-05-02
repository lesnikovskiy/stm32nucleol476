#ifndef MAIN_H_
#define MAIN_H_

#include <stdint.h>

typedef struct {
	uint32_t GPIOAEN :1;
	uint32_t GPIOBEN :1;
	uint32_t GPIOCEN :1;
	uint32_t GPIODEN :1;
	uint32_t GPIOEEN :1;
	uint32_t GPIOFEN :1;
	uint32_t GPIOGEN :1;
	uint32_t GPIOHEN :1;
	uint32_t GPIOIEN :1;
	uint32_t RESERVED1 :3;
	uint32_t OTGFSEN :1;
	uint32_t ADCEN :1;
	uint32_t DCMIEN :1;
	uint32_t RESERVED2 :1;
	uint32_t AESEN :1;
	uint32_t HASHEN :1;
	uint32_t RNGEN :1;
	uint32_t RESERVED3 :13;
} RCC_AHB2ENR_t;

typedef struct {
	uint32_t Pin_0 :2;
	uint32_t Pin_1 :2;
	uint32_t Pin_2 :2;
	uint32_t Pin_3 :2;
	uint32_t Pin_4 :2;
	uint32_t Pin_5 :2;
	uint32_t Pin_6 :2;
	uint32_t Pin_7 :2;
	uint32_t Pin_8 :2;
	uint32_t Pin_9 :2;
	uint32_t Pin_10 :2;
	uint32_t Pin_11 :2;
	uint32_t Pin_12 :2;
	uint32_t Pin_13 :2;
	uint32_t Pin_14 :2;
	uint32_t Pin_15 :2;
} GPIOx_MODE_t;

typedef struct {
	uint32_t Pin_0 :1;
	uint32_t Pin_1 :1;
	uint32_t Pin_2 :1;
	uint32_t Pin_3 :1;
	uint32_t Pin_4 :1;
	uint32_t Pin_5 :1;
	uint32_t Pin_6 :1;
	uint32_t Pin_7 :1;
	uint32_t Pin_8 :1;
	uint32_t Pin_9 :1;
	uint32_t Pin_10 :1;
	uint32_t Pin_11 :1;
	uint32_t Pin_12 :1;
	uint32_t Pin_13 :1;
	uint32_t Pin_14 :1;
	uint32_t Pin_15 :1;
	uint32_t RESERVED :16;
} GPIOx_ODR_t;

#define HIGH (1)
#define LOW  (0)

#define INPUT_MODE   (0)
#define OUTPUT_MODE  (0x1)
#define AF_MODE      (0x2)
#define ANALOG_MODE  (0x3)

#endif /* MAIN_H_ */
