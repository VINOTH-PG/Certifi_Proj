

#include <stdint.h>
#include <stm32f4xx.h>

#include "bt.h"


int main(void)
{

		RCC->AHB1ENR |=(1U<<0);

		GPIOA->MODER |= (1U<<10);
		GPIOA->MODER &= ~(1U<<11);

	uart_init();


	while (1)
	{
		uint32_t temp =  uart_rx();
		uart_tx(temp);

		if (temp == '1')

		{

			GPIOA->ODR |=(1U<<5);


		}


		else if(temp == '0')

	     {

				GPIOA->ODR &= ~(1U<<5);

			}


	}






}




