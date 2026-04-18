#ifndef KEYBOARD_H_
#define KEYBOARD_H_

#include "stm32l476rg.h"

void setup_ports(void);

void setup_row1(void);
void setup_row2(void);
void setup_row3(void);
void setup_row4(void);

void setup_col1(void);
void setup_col2(void);
void setup_col3(void);

#endif /* KEYBOARD_H_ */
