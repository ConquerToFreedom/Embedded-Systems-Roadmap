#include "uart.h"

void uart_init(UART_Handle_t *handle)
{
    /* 1. Enable GPIOA clock */
    RCC->AHB1ENR |= (1U << RCC_AHB1ENR_GPIOAEN_Pos);

    /* 2. Enable USART2 clock */
    RCC->APB1ENR |= (1U << RCC_APB1ENR_USART2EN_Pos);

   /* 3. Configure PA2 as Alternate Function (USART2_TX) */
    GPIOA->MODER &= ~(3U << (GPIO_PIN_2 * 2));
    GPIOA->MODER |=  (2U << (GPIO_PIN_2 * 2));

    /* 4. Select AF7 for PA2 → USART2_TX */
    GPIOA->AFRL &= ~(0xFU << (GPIO_PIN_2 * 4));
    GPIOA->AFRL |=  (7U << (GPIO_PIN_2 * 4));

    /* 5. Configure PA3 as Alternate Function (USART2_RX) */
    GPIOA->MODER &= ~(3U << (GPIO_PIN_3 * 2));
    GPIOA->MODER |=  (2U << (GPIO_PIN_3 * 2));

    /* 6. Select AF7 for PA3 → USART2_RX */
    GPIOA->AFRL &= ~(0xFU << (GPIO_PIN_3 * 4));
    GPIOA->AFRL |=  (7U << (GPIO_PIN_3 * 4));

    /* 5. Configure baud rate */
    handle->USARTx->BRR = 139U;

    /* Enable transmitter and receiver */
    handle->USARTx->CR1 |= (1U << USART_CR1_TE_Pos);
    handle->USARTx->CR1 |= (1U << USART_CR1_RE_Pos);

    /* 7. Enable USART */
    handle->USARTx->CR1 |= (1U << USART_CR1_UE_Pos);
}


void uart_write_char(UART_Handle_t *handle, char data)
{
    /* Wait until transmit data register is empty */
    while (!(handle->USARTx->SR & (1U << USART_SR_TXE_Pos)))
    {
        /* Wait */
    }

    /* Put character into transmit data register */
    handle->USARTx->DR = data;
}


void uart_write_string(UART_Handle_t *handle, const char *str)
{
    while (*str)
    {
        uart_write_char(handle, *str);
        str++;
    }
}

char uart_read_char(UART_Handle_t *handle)
{
    /* Wait until a byte has been received */
    while (!(handle->USARTx->SR & (1U << USART_SR_RXNE_Pos)))
    {
        /* Wait */
    }

    /* Reading DR returns the received byte and clears RXNE (and ORE if set) */
    return (char)(handle->USARTx->DR & 0xFFU);
}

void uart_read_line(UART_Handle_t *handle, char *buffer, uint32_t max_len)
{
    uint32_t index = 0;
    char c;

    while (1) 
    {
        c = uart_read_char(handle);
        
        if (c == '\b' || c == 0x7F) 
        {
           if (index > 0) 
           {
              index--;
              uart_write_string(handle, "\b \b");
           }
           continue;
        }
        
        if (c == '\r' || c == '\n') 
        {
            buffer[index] = '\0';
            uart_write_string(handle, "\r\n");
            return;
        }

        if (index < (max_len - 1)) 
        {
            buffer[index] = c;
            index++;
            uart_write_char(handle, c);
        }

    }
}