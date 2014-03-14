/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** rc_uart.cpp
** Basic UART functions
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <Arduino.h>

#include <rc_uart.h>


namespace rc
{
namespace uart
{

static FILE s_stdout;
static FILE s_stdin;


void init(uint16_t p_baud)
{
	uint16_t ubrr = ((F_CPU / 8) / p_baud) - 1;
	if (ubrr > 4095)
	{
		UCSR0A = 0; // single rate
		ubrr = ((F_CPU / 16) / p_baud) - 1;
	}
	else
	{
		UCSR0A = 1 << U2X0; // dual rate
	}

	UBRR0H = (ubrr >> 8) & 0x0F;
	UBRR0L = ubrr & 0xFF;

	UCSR0B |=  _BV(TXEN0);  // TX enabled
	UCSR0B |=  _BV(RXEN0);  // RX enabled
	UCSR0B &= ~_BV(UDRIE0); // Data Register Empty Interrupt disabled
}


void put(uint8_t p_byte)
{
	loop_until_bit_is_set(UCSR0A, UDRE0); // Data register empty
	UDR0 = p_byte;
}


uint8_t get()
{
	loop_until_bit_is_set(UCSR0A, RXC0); // Receive complete
	return UDR0;
}


static int uart_putchar(char p_c, FILE* p_stream)
{
	put(static_cast<uint8_t>(p_c));
	return 0;
}


static int uart_getchar(FILE* p_stream)
{
	return static_cast<int>(get());
}


void setStdOut()
{
	fdev_setup_stream(&s_stdout, uart_putchar, NULL, _FDEV_SETUP_WRITE);
	stdout = &s_stdout; 
}


void setStdIn()
{
	fdev_setup_stream(&s_stdin, NULL, uart_getchar, _FDEV_SETUP_READ);
	stdin = &s_stdin; 
}


// namespace end
}
}
