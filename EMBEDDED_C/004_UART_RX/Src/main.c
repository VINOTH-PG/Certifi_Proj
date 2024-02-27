#include "uart_tx_rx.h"
char key;
int main()
{
	RCC->AHB1ENR |=(1U<<0);


	GPIOA->MODER |=(1U<<10);
	GPIOA->MODER &=~(1U<<11);

	uart_tx_init();


while (1)
{
	key = uart2_re();
if (key == '1')
{
	GPIOA->ODR |=(1U<<5);
}

else
{
	GPIOA->ODR &=~(1U<<5);
}
}

//	for (uint32_t i=0;i<10;)
//	{
//
//		uart2_wr('C');
//		i++;
//	}


}

