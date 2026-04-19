#ifndef KEYBOARD_H_
#define KEYBOARD_H_

#include "stm32l476rg.h"
#include "delay.h"

void setup_ports(void);

void setup_row1(void);
void setup_row2(void);
void setup_row3(void);
void setup_row4(void);

void setup_col1(void);
void setup_col2(void);
void setup_col3(void);

char get_key(void);

// Optimized version
typedef struct {
	GPIO_TypeDef* port;
	uint16_t pin;
} PinConfig;

void setup_keyboard(void);
char get_opt_key(void);

#endif /* KEYBOARD_H_ */
