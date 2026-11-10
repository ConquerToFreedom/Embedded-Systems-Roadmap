#include "stm32f446xx.h"
#include "uart.h"

int main(void)
{
    UART_Handle_t uart;
    uart.USARTx = USART2;
    uart.baud_rate = 115200;

    uart_init_interrupt(&uart); // Use the interrupt init!

    uart_write_string(&uart, "Interrupt-Driven UART. Type something!\r\n");

    while (1)
    {
        // If the ISR set the flag, print the data
        if (rx_flag == 1)
        {
            uart_write_char(&uart, rx_data);
            
            // IMPORTANT: Reset the flag so we wait for the next byte
            rx_flag = 0; 
        }
        
        // Notice how the CPU is completely free here to do other work!
    }
}