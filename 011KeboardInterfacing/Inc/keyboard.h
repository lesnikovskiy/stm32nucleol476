#ifndef KEYBOARD_H_
#define KEYBOARD_H_

#include "stm32l476rg.h"
#include "delay.h"

typedef struct {
	GPIO_TypeDef *port;
	uint16_t pin;
} PinConfig;

void setup_ports(void);
void setup_keyboard(void);
char get_key(void);

#endif /* KEYBOARD_H_ */
