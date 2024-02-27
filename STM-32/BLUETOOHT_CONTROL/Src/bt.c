#include "stm32f4xx.h"
#include <stdint.h>
#include "bt.h"


				// PROGRAM FOR BLUETOOTH CONTROL AUTOMATION

				// THE Tx AND Rx PINS ARE USED TO CONNECT THE BLUETOOTH MODULE
#define PERICLK  (16000000)
#define BAUDRATE (9600)




void uart_init(void)
{

			/* INITILIZE THE THE GPIO MODULE */


	// ENABLE THE CLK ACCES TO THE GPIOC

	RCC->AHB1ENR |= (1U<<2); // USART6 CONNECTED TO GPIOC

	// SET THE GPIOC  MODE (ALTRENATE FUNCTIONMODE)

	GPIOC->MODER &=~(1U<<12);
	GPIOC->MODER |=(1U<<13);  // FOR PORTC 6 UART TX

	GPIOC->MODER &=~(1U<<14);
	GPIOC->MODER |=(1U<<15);  	// FOR PORTC 7 UART RX

	// SET THE MODE TO ALTRENATE FUNCTION MODE (AF08) FOR UART6 MODULE


	GPIOC->AFR [0] &= ~(1U<<24);   // FOR USART TX AF08
	GPIOC->AFR [0] &= ~(1U<<25);
	GPIOC->AFR [0] &= ~(1U<<26);
	GPIOC->AFR [0] |=  (1U<<27);

	GPIOC->AFR [0] &= ~(1U<<28);    //FOR USART RX AF08
	GPIOC->AFR [0] &= ~(1U<<29);
	GPIOC->AFR [0] &= ~(1U<<30);
	GPIOC->AFR [0] |=  (1U<<31);



			/* INITILIZE THE UART MODULE  */


	// ENABLE THE CLOCK ACCESS TO THE UART MODULE

		RCC->APB2ENR |=(1U<<5);

	// SET THE  BADURATE TO THE UART MODULE

		set_uart_baudrate(PERICLK,BAUDRATE);

	// SET THE DIRECTION OF THE UART

		USART6->CR1 |=(1U<<2) | (1U<<3);

	// ENABLE THE UART MODULE

		USART6->CR1 |=(1U<<13);



}

void set_uart_baudrate(uint32_t CLOCK , uint32_t BAUD)
{

	// SET THE UART BADURATE(BAUDRATE,PERICLK)

	uint32_t UART6 =  ((CLOCK + (BAUD/2U)) / BAUD) ;

	// STORE THE BAUDRATE TO THE BAUDRATE REGISTER

	USART6->BRR = UART6;

}


void uart_tx(char temp)
{
	// WAIT UNTIL THE TX DATA REG IS SET

	while (!(USART6->SR & (1U<<7)))
	{


	}

	// WRITE THE DATA TO DATA REG

	USART6->DR = (temp & 0xFF);
}

char uart_rx(void)
{
	// WAIT UNTIL THE RX DATA REG IS SET

	while (!(USART6->SR & (1U<<5)))
	{}

	// READ THE DATA FROM DR REG

	    return USART6->DR;


}

