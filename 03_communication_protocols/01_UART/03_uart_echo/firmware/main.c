#include "stm32f446xx.h"
#include "uart.h"

#define LINE_MAX 64

int main(void)
{
    UART_Handle_t uart;
    uart.USARTx    = USART2;
    uart.baud_rate = 115200;

    uart_init(&uart);

    uart_write_string(&uart, "UART Line Echo Test\r\n");

    char line_buffer[LINE_MAX];

    while (1)
    {
        uart_write_string(&uart, "> ");
        uart_read_line(&uart, line_buffer, LINE_MAX);
        uart_write_string(&uart, "You typed: ");
        uart_write_string(&uart, line_buffer);
        uart_write_string(&uart, "\r\n");
    }
}