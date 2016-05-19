/*
 * sterowaniePWM.c
 *
 * Created: 20.11.2015 04:26:55
 * Author : Przemek
 */ 

#include "defines.h"
#include "UART.h"
#include "Timerc.h"

ISR(TIMER0_COMP_vect);
ISR(USART_RXC_vect);

//ISR(INT0_vect);
//ISR(INT1_vect);

int main(void)
{
	odebrana=101;
	flaga_UART=0;
	flaga_enkondera=0;
	licznik_TIMER0=0;
	licznik_motor=0;
	enable_przerw=0;
	licznik_L=0;
	licznik_P=0;
	
	uint8_t tmp_L=0;
	uint8_t tmp_P=0;
	
	USART_Init(51);

	TIMER0_INIT();
	TIMER1_PWM_INIT();
	
	Init_Ext_Interrupt0();
	Init_Ext_Interrupt1();
	
	Motor_active;
	sei();
	run_motor;
    while (1) 
    {
		if (flaga_UART==1)
		{
			flaga_UART=0;
			switch(odebrana)
			{
				case 97:					//a
				run_motor;
				break;
				
				case 98:					//b
				back_motor;
				break;
				
				case 99:					//c
				right_motor;
				break;
				
				case 100:					//d
				left_motor;
				break;
				
				default:
				stop_motor;
				break;
			}
			licznik_motor=0;
			enable_przerw=1;			
		}//koniec if (flaga_UART==1)
		if (flaga_enkondera==1)
		{
			tmp_L=licznik_L;
			tmp_P=licznik_P;
			
			USART_Transmit('L');
			USART_Transmit(OCR1A);
			USART_Transmit(tmp_L);
			USART_Transmit('P');
			USART_Transmit(OCR1B);
			USART_Transmit(tmp_P);
			if (tmp_L>tmp_P)
			{
				if (OCR1B>=254)
				{
					OCR1A--;
				}
				else
				{
					OCR1B++;	
				}
			}
			else if (tmp_P>tmp_L)
			{
				if (OCR1A>=254)
				{
					OCR1B--;
				}
				else
				{
					OCR1A++;
				}
			}
			flaga_enkondera=0;
			licznik_L=0;
			licznik_P=0;
		}//koniec if (flaga_enkondera==1)
	}//koniech while(1)
}

ISR(USART_RXC_vect)
{
	odebrana=UDR;
	flaga_UART=1;
	//USART_Flush();
}

/*Przerwanie z TIMER0*/
ISR(TIMER0_COMP_vect)
{
	if (licznik_motor==50&&enable_przerw==1)
	{
		enable_przerw=0;
		licznik_motor=0;
		stop_motor;
	}
	if (licznik_TIMER0==250)
	{
		flaga_enkondera=1;
		licznik_TIMER0=0;
	}
	licznik_motor++;
	licznik_TIMER0++;
	
}

/*Przerwanie odbioru z UARTa*/


/*Przerwania zewnêtrzne */  
ISR(INT0_vect)
{
	licznik_L++;
}

ISR(INT1_vect)
{
	licznik_P++;
}