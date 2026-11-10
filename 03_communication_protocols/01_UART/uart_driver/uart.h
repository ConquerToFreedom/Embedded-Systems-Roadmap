#ifndef UART_H
#define UART_H

#include "stm32f446xx.h"

typedef struct
{
    USART_TypeDef *USARTx;
    uint32_t baud_rate;

} UART_Handle_t;

// Tell the compiler this variable can change unexpectedly
extern volatile char rx_data; 
extern volatile uint8_t rx_flag;

/* UART Initialization */
void uart_init_interrupt(UART_Handle_t *handle);


/* UART Polling TX */
void uart_write_char(UART_Handle_t *handle, char data);
void uart_write_string(UART_Handle_t *handle, const char *str);
/* UART Polling RX */
char uart_read_char(UART_Handle_t *handle);

void uart_read_line(UART_Handle_t *handle, char *buffer, uint32_t max_len);

#endif