#ifndef ITM_H_
#define ITM_H_

#include "stm32l476rg.h"

void ITM_Init(void);
void ITM_SendChar(char ch);

#endif /* ITM_H_ */
