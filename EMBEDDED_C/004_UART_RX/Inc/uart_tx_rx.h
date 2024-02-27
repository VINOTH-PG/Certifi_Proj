
#ifndef UART_TX_RX_H_
#define UART_TX_RX_H_

#include"stm32f4xx.h"
#include <stdint.h>

#define SYS_CLK    (16000000)

#define APB1_CLK	SYS_CLK

#define SYS_BAUDRATE (115200)


//static void computate_set_baudrate (uint32_t periclk , uint32_t baudrate);
void computate_baudrate_bd (uint32_t periclk , uint32_t baudrate);
void uart_tx_init(void);
void uart2_wr (int ch);
char uart2_re (void);
int __io_putchar(int ch);



void uart_tx_init(void)
{
/*  CONFIGUR THE GPIO MODULE*/

	// ENABLE THE CLOCK ACCESS FOR GPIO

	RCC->AHB1ENR |=(1U<<0);


	//SET THE MODE AS ALTERNATE FUNCTION MODE

	GPIOA->MODER &=~(1U<<4);
	GPIOA->MODER |=(1U<<5);



	//SET THE ALTERNATE FUNCTION MODE AS THE 'UART TX - AF07' 0111

	GPIOA->AFR[0] |=(1U<<8);
	GPIOA->AFR[0] |=(1U<<9);
	GPIOA->AFR[0] |=(1U<<10);
	GPIOA->AFR[0] &=~(1U<<11);

	//SET THE MODE AS ALTERNATE FUNCTION MODE

	GPIOA->MODER &=~(1U<<6);
	GPIOA->MODER |=(1U<<7);

	//SET THE ALTERNATE FUNCTION MODE AS THE 'UART TX - AF07' 0111

	GPIOA->AFR[0] |=(1U<<12);
	GPIOA->AFR[0] |=(1U<<13);
	GPIOA->AFR[0] |=(1U<<14);
	GPIOA->AFR[0] &=~(1U<<15);

	/*   CONFIGURE THE UART MODULE*/


	// ENABLE THE CLOCK ACCESS TO UART MODULE

	RCC->APB1ENR |=(1U<<17);


	// SET THE BAUDRATE TO THE  UART

	computate_baudrate_bd(APB1_CLK,SYS_BAUDRATE);

	// SET THE DIRECTION OF THE UART

	USART2->CR1 =(1U<<3)|(1U<<2);


	// ENABLE THE UART MODULE

	USART2->CR1 |=(1U<<13);

}



int __io_putchar(int ch)
{
	uart2_wr(ch);
	return (ch);
}
char uart2_re (void)

{
	// MAKE SURE THE RX DATA REGISTER NOT IS EMPTY
		while(!(USART2->SR & (1U<<5) ))
		{}

	return USART2->DR;
}
void uart2_wr (int ch)

{
	// MAKE SURE THE TX DATA REGISTER IS EMPTY
	while(!(USART2->SR & (1U<<7) ))
	{}

	// WRITE TO TX DATA REGISTER
	USART2->DR = (ch & 0xFF);


}
//static void computate_set_baudrate (uint32_t periclk , uint32_t baudrate)
//{
//USART2->BRR = computate_baudrate_bd(periclk,baudrate);
//
//}
void computate_baudrate_bd (uint32_t periclk , uint32_t baudrate)
{

uint32_t UART2 = ((periclk+(baudrate/2U))/baudrate);
USART2->BRR = UART2;
}



#endif /* UART_TX_H_ */
