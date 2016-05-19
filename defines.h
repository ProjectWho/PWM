//------------------------------------------------------------------------------------
// U�ywane biblioteki w programie
// Plik : defines.h
// Mikrokontroler : Atmel AVR
// Kompilator : avr-gcc
// Autor : 
// Data : 20.12.2014
//------------------------------------------------------------------------------------
#include <stdlib.h> 
#include <string.h>
#include <avr/io.h>
//#define F_CPU 7382700
#define F_CPU 8000000
//#include <util/delay.h>
#define BAUD 9600			//transmisja z pr�dko�ci� 9600 bod�w
#define MYUBRR F_CPU/16/BAUD-1
#include <util/setbaud.h>
#include <avr/interrupt.h>			//do��czenie pliku nag��wkowego zawieraj�cego obs�ug� przerwa�

#define DDR_motor1 0x03									//ustawienie kt�re piny na Porcie dla silnika 1
#define DDR_motor2 0x0C									//ustawienie kt�re piny na Porcie dla silnika 2
#define Motor_active DDRC=DDR_motor1|DDR_motor2			//ustawienie DDR dla silnik�w

#define Port_motor PORTC
#define Pin0_m1 PC0										//Pin steruj�cy silnik 1 
#define Pin1_m1 PC1										//Pin steruj�cy silnik 1 

#define Pin0_m2 PC2										//Pin steruj�cy silnik 2
#define Pin1_m2 PC3										//Pin steruj�cy silnik 2

#define run_motor Port_motor=(1<<Pin0_m1)|(0<<Pin1_m1)|(1<<Pin0_m2)|(0<<Pin1_m2)
#define back_motor Port_motor=(0<<Pin0_m1)|(1<<Pin1_m1)|(0<<Pin0_m2)|(1<<Pin1_m2)
#define left_motor Port_motor=(1<<Pin0_m1)|(0<<Pin1_m1)|(0<<Pin0_m2)|(1<<Pin1_m2)
#define right_motor Port_motor=(0<<Pin0_m1)|(1<<Pin1_m1)|(1<<Pin0_m2)|(0<<Pin1_m2)
#define stop_motor Port_motor=(0<<Pin0_m1)|(0<<Pin1_m1)|(0<<Pin0_m2)|(0<<Pin1_m2)

uint8_t odebrana;
//uint16_t licznik;
volatile uint8_t licznik_L;
volatile uint8_t licznik_P;
volatile uint16_t licznik_TIMER0;
volatile uint8_t licznik_motor;
volatile uint8_t flaga_UART;
volatile uint8_t flaga_enkondera;
volatile uint8_t enable_przerw;
//------------------------------------------------------------------------------------
//
// Koniec pliku defines.h
//
//------------------------------------------------------------------------------------