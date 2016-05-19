//------------------------------------------------------------------------------------
// Obs³uga transmisji UART
//
// 
// Plik : UART.h
// Mikrokontroler : Atmel AVR
// Kompilator : avr-gcc
// Autor : 
// Data : 20.12.2014
//------------------------------------------------------------------------------------
#include "defines.h"


void USART_Init( unsigned int ubrr);
void USART_Transmit( unsigned char data );
uint8_t USART_Receive( void );

void USART_Flush(void);

//------------------------------------------------------------------------------------
//
// Koniec pliku GSM_UART.h
//
//------------------------------------------------------------------------------------