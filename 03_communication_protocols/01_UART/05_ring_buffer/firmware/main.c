#include "stm32f446xx.h"
#include "uart.h"

int main(void)
{
    UART_Handle_t uart;
    uart.USARTx = USART2;
    uart.baud_rate = 115200;

    uart_init_interrupt(&uart); 

    uart_write_string(&uart, "Ring Buffer Active. Type fast!\r\n");

    while (1)
    {
        // Ask for a character
        char c = uart_get_char();
        
        // If there is data (c != 0), echo it back
        if (c != 0)
        {
            uart_write_char(&uart, c);
        }
    }
}