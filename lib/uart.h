#pragma once

//
// Utilities for UART communication.
//
// First, init uart with desired baud rate using uart_init(baud).
// Then enable interrupts you want with uart_isr_XXX().
//

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <stdbool.h>
#include <stdint.h>


/** Init UART for given baudrate */
void _uart_init_do(uint16_t ubrr); // internal, needed for the macro.
#define uart_init(baud) _uart_init_do(F_CPU / 16 / (baud) - 1)

/** Check if there's a byte in the RX register */
#define uart_rx_ready() (0 != (UCSR0A & (1 << RXC0)))

/** Check if transmission of everything is done */
#define uart_tx_ready() (0 != (UCSR0A & (1 << UDRE0)))



// Enable UART interrupts

/** Enable or disable RX ISR */
void uart_isr_rx(bool enable);

/** Enable or disable TX ISR (1 byte is sent) */
void uart_isr_tx(bool enable);

/** Enable or disable DRE ISR (all is sent) */
void uart_isr_dre(bool enable);



// Basic IO

/** Receive one byte over UART */
uint8_t uart_rx();

/** Send byte over UART */
#define uart_putc(data) uart_tx((data))
void uart_tx(uint8_t data);

/** Clear receive buffer */
void uart_flush();



// Strings

/** Send string over UART */
void uart_puts(const char* str);

/** Send progmem string over UART */
void uart_puts_pgm(const char* str);


// Numbers

/** Send unsigned int */
void uart_put8i(const int8_t num);

/** Send signed int */
void uart_put8u(const uint8_t num);

/** Send unsigned int */
void uart_put16i(const int16_t num);

/** Send signed int */
void uart_put16u(const uint16_t num);

/** Send unsigned long */
void uart_put32u(const uint32_t num);

/** Send signed long */
void uart_put32i(const int32_t num);

/** Send signed int as float */
void uart_put16if(const int16_t num, const uint8_t places);

/** Send unsigned int as float */
void uart_put16uf(const uint16_t num, const uint8_t places);

/** Send signed long as float */
void uart_put32if(const int32_t num, const uint8_t places);

/** Send unsigned long as float */
void uart_put32uf(const uint32_t num, const uint8_t places);


// Extras

/** Send CRLF */
void uart_nl();
