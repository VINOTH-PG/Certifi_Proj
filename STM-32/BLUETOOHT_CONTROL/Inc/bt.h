

#ifndef BT_H_
#define BT_H_
#include "stm32f4xx.h"
#include <stdint.h>


void uart_init(void);
void set_uart_baudrate(uint32_t CLOCK , uint32_t BAUD);
void uart_tx(char ch);
char uart_rx(void);
#endif /* BT_H_ */
