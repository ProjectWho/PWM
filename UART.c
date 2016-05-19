//-------------------------------------------------------------------------------------------------
// Obs³uga transmisji UART
// 
// 
// Plik : GPS_UART.c
// Mikrokontroler : Atmel AVR
// Kompilator : avr-gcc
// Autor :
// Data : 20.12.2014
//------------------------------------------------------------------------------------
#include "UART.h"
//licznik=0;
//------------------------------------------------------------------------------------
//
//Ustawienie transmisji USART wraz z przerwaniami
//
//------------------------------------------------------------------------------------
void USART_Init(unsigned int ubrr)
{
	UBRRH = (unsigned char)(ubrr>>8);
	UBRRL = (unsigned char)ubrr;
	UCSRB = (1<<RXEN)|(1<<TXEN)|(1<<RXCIE);
	/* Format Ramki: 8data, 1 stop bit */
	UCSRC = (1<<URSEL)|(3<<UCSZ0);
	UCSRB = (1<<RXEN)|(1<<TXEN)|(1<<RXCIE); // w³¹czenie przerwañ
}
//------------------------------------------------------------------------------------
//
//Transmisja USART
//
//------------------------------------------------------------------------------------
void USART_Transmit( unsigned char data )
{
	/* Wait for empty transmit buffer */
	while ( !( UCSRA & (1<<UDRE)) );
	/* Put data into buffer, sends the data */
	UDR = data;
}

unsigned char USART_Receive( void )
{
	/* Wait for data to be received */
	while ( !(UCSRA & (1<<RXC)) )
	;
	/* Get and return received data from buffer */
	return UDR;
}

void USART_Flush(void)								// czyœci bufor UART
{
	unsigned char dummy;
	while(UCSRA&(1<<RXC))
	{
		dummy=UDR;
	}
}
