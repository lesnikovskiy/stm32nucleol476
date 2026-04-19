#ifndef DELAY_H_
#define DELAY_H_

#include "stm32l476rg.h"

extern const uint32_t SystemCoreClock;

void delay_us(uint32_t us);
void delay_ms(uint32_t ms);

#endif /* DELAY_H_ */
