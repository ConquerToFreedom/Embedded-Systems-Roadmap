#include "uart.h"

void uart_init(UART_Handle_t *handle)
{
    /* 1. Enable GPIOA clock */
    RCC->AHB1ENR |= (1U << RCC_AHB1ENR_GPIOAEN_Pos);

    /* 2. Enable USART2 clock */
    RCC->APB1ENR |= (1U << RCC_APB1ENR_USART2EN_Pos);

    /* 3. Configure PA2 as Alternate Function */
    GPIOA->MODER &= ~(3U << (GPIO_PIN_2 * 2));
    GPIOA->MODER |=  (2U << (GPIO_PIN_2 * 2));

    /* 4. Select AF7 for PA2 → USART2_TX */
    GPIOA->AFRL &= ~(0xFU << (GPIO_PIN_2 * 4));
    GPIOA->AFRL |=  (7U << (GPIO_PIN_2 * 4));

    /* 5. Configure baud rate */
    handle->USARTx->BRR = 139U;

    /* 6. Enable transmitter */
    handle->USARTx->CR1 |= (1U << USART_CR1_TE_Pos);

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