#ifndef USART_H_
#define USART_H_

#include "stm32l476rg.h"

/*
 * To use USART on Mac terminal
 * $ ls /dev/tty.usb*
 * $ screen /dev/tty.usbmodem1234 115200
 *
 * To quit Ctrl+A K y
 * */

void USART_Init(void);

void USART_send_char(const char ch);
void USART_send_str(const char *str);

int USART_is_data_available(void);
char USART_read_char(void);

#endif /* USART_H_ */
