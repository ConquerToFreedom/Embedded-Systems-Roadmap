#include "stm32f446xx.h"
#include "uart.h"

int main(void)
{
    UART_Handle_t uart;
    uart.USARTx    = USART2;
    uart.baud_rate = 115200;

    uart_init(&uart);

    uart_write_string(&uart, "UART RX test. Type a character.\r\n");

    while (1)
    {
        char c = uart_read_char(&uart);
        uart_write_char(&uart, c);
    }
}