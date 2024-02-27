#include "uart_tx.h"

int main()
{
	uart_tx_init();




	for (uint32_t i=0;i<10;)
	{

		uart2_wr('C');
		i++;
	}


}

