#include "stm32f446xx.h"
#include "uart.h"

int main(void)
{
    UART_Handle_t uart;

    uart.USARTx = USART2;
    uart.baud_rate = 115200;

    uart_init(&uart);

    while (1)
    {
        uart_write_string(&uart, "Hello STM32!, I AM CHETAN\r\n");
    }
}