/*
 * timer.c
 *
 * Created: 28.02.2016 17:26:11
 *  Author: Przemek
 */ 
#include "Timerc.h"
#include "UART.h"
/* ustawienie TIMER0 jako licznika */
void TIMER0_INIT()
{
	TCCR0 |= (1<<CS02);						//presklaler na 1024
	TCCR0 |= (1<<WGM01);								//tryb CTC
	OCR0 =124;											//dla 8MHz
	TIMSK |= (1<<OCIE0);								//co 4ms 
}

/*Ustawienie TIMER0 jako PWM*/
/*void TIMER0_INIT()
{
	 DDRB  |= (1<<PB3);
	 TCCR0 |= (0<<FOC0);
	 TCCR0 |= (1<<WGM00);			//Tryb PWM z korekcja
	 TCCR0 |= (1<<COM01);			//Zeruj przy porównaniu
	 
	 TCCR0 |= (1<<CS01) ;			 // Ÿród³em CLK, preskaler 8 to daje 8MHz/8=1MHz
	 OCR0 = 150;
}*/


/* Ustawienie TIMER1B w tryb licznika*/
void TIMER1_PWM_INIT()
{
	DDRD|=(1<<DDRD4); //PWMA
	DDRD|=(1<<DDRD5); //PWMB

	TCCR1A|=(1<<WGM10);						//Tryb PWM z popraw¹  fazy (wskazany dla sterowania silnikami)
	TCCR1A|= (1<<COM1A1)|(1<<COM1B1);		//Zeruj przy zrownaniu
	TCCR1B|=(1<<CS10);						//NO prescaler

	OCR1A=190;								//LEWY
	OCR1B=190;								//PRAWY
}


//****** za³¹czenie przerwañ zewnêtrzenych***/

void Init_Ext_Interrupt0()
{
	DDRD &= ~(1<<DDRD2); 
	PORTD |= (1<<DDRD2);  
	MCUCR|=(1<<ISC01)|(1<<ISC00);
	GICR|=(1<<INT0);
}
void Init_Ext_Interrupt1()
{
	DDRD &= ~(1<<DDRD3);
	PORTD |= (1<<DDRD3);
	MCUCR|=(1<<ISC11)|(1<<ISC10);
	GICR|=(1<<INT1);
}