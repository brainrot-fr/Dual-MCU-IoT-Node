#include "usart.h"

static uint16_t compute_baud_rate(uint32_t peripheral_clock, uint32_t baud_rate){
    return (peripheral_clock + (baud_rate / 2) / baud_rate);
}

void usart_enable(usart_peripheral_t usart, uint32_t peripheral_clock, uint32_t baud_rate, GPIO_TypeDef *port, uint8_t tx_pin, uint8_t rx_pin){

    rcc_usart_enable(usart, *port, tx_pin, rx_pin);

    switch (usart){

        case USART1_PERIPH:
            USART1->CR1 |= USART_CR1_UE_Msk;     // Set UE bit in CR1     - usart enable
            USART1->CR1 |= USART_CR1_RE_Msk;     // Set RE bit in CR1     - receiver enable
            USART1->CR1 |= USART_CR1_TE_Msk;     // Set TE bit in CR1     - transmitter enable
            USART1->CR1 &= ~(USART_CR1_M_Msk);   // reset M bit in CR1    - 8 data bits, 1 start bit and n stop bits
            USART1->CR1 &= ~(USART_CR1_PCE_Msk); // reset PE bit in CR1   - no parity
            USART1->CR2 &= ~(USART_CR2_STOP_1);   // reset the STOP bits   - 1 stop bit
            USART1->BRR = compute_baud_rate(peripheral_clock, baudrate)
            break;

        case USART2_PERIPH:
            USART2->CR1 |= USART_CR1_UE_Msk;     // Set UE bit in CR1     - usart enable
            USART2->CR1 |= USART_CR1_RE_Msk;     // Set RE bit in CR1     - receiver enable
            USART2->CR1 |= USART_CR1_TE_Msk;     // Set TE bit in CR1     - transmitter enable
            USART2->CR1 &= ~(USART_CR1_M_Msk);   // reset M bit in CR1    - 8 data bits, 1 start bit and n stop bits
            USART2->CR1 &= ~(USART_CR1_PCE_Msk); // reset PE bit in CR1   - no parity
            USART2->CR2 &= ~(USART_CR2_STOP_1);   // reset the STOP bits   - 1 stop bit
            USART2->BRR = compute_baud_rate(peripheral_clock, baudrate);
            break;

        case USART6_PERIPH:
            USART6->CR1 |= USART_CR1_UE_Msk;     // Set UE bit in CR1     - usart enable
            USART6->CR1 |= USART_CR1_RE_Msk;     // Set RE bit in CR1     - receiver enable
            USART6->CR1 |= USART_CR1_TE_Msk;     // Set TE bit in CR1     - transmitter enable
            USART6->CR1 &= ~(USART_CR1_M_Msk);   // reset M bit in CR1    - 8 data bits, 1 start bit and n stop bits
            USART6->CR1 &= ~(USART_CR1_PCE_Msk); // reset PE bit in CR1   - no parity
            USART6->CR2 &= ~(USART_CR2_STOP_1);  // reset the STOP bits   - 1 stop bit
            USART6->BRR = compute_baud_rate(peripheral_clock, baudrate);
            break;

        default: //use USART2 as default.
            USART2->CR1 |= USART_CR1_UE_Msk;     // Set UE bit in CR1     - usart enable
            USART2->CR1 |= USART_CR1_RE_Msk;     // Set RE bit in CR1     - receiver enable
            USART2->CR1 |= USART_CR1_TE_Msk;     // Set TE bit in CR1     - transmitter enable
            USART2->CR1 &= ~(USART_CR1_M_Msk);   // reset M bit in CR1    - 8 data bits, 1 start bit and n stop bits
            USART2->CR1 &= ~(USART_CR1_PCE_Msk); // reset PE bit in CR1   - no parity
            USART2->CR2 &= ~(USART_CR2_STOP_1);  // reset the STOP bits   - 1 stop bit
            USART2->BRR = compute_baud_rate(peripheral_clock, baudrate);
            break;
    }
}

uint32_t usart_send_char(usart_peripheral_t usart, uint8_t data){
    switch (usart) {
    case USART1_PERIPH:
        while (!is_bit_set(USART1->SR, USART_SR_TXE)) {}    //wait until transmitter register is ready

        USART1->DR = data;                                      //write data into data register

        while (!is_bit_set(USART1->SR, USART_SR_TC)) {}     //wait until Transmission is complete
        break;

    case USART2_PERIPH:
        while (!is_bit_set(USART2->SR, USART_SR_TXE)) {}    //wait until transmitter register is ready

        USART2->DR = data;                                      //write data into data register

        while (!is_bit_set(USART2->SR, USART_SR_TC)) {}     //wait until Transmission is complete
        break;

    case USART6_PERIPH:
        while (!is_bit_set(USART6->SR, USART_SR_TXE)) {}    //wait until transmitter register is ready

        USART6->DR = data;                                      //write data into data register

        while (!is_bit_set(USART6->SR, USART_SR_TC)) {}     //wait until Transmission is complete
        break;

    default:
        while (!is_bit_set(USART2->SR, USART_SR_TXE)) {}    //wait until transmitter register is ready

        USART2->DR = data;                                      //write data into data register

        while (!is_bit_set(USART2->SR, USART_SR_TC)) {}     //wait until Transmission is complete
        break;
    }

    return 0U;
}