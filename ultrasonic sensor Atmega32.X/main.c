/*
 * File:   main.c
 * Author: Mohamed_Arafa
 *
 * Created on December 17, 2021, 6:30 AM
 */
#define F_CPU 8000000
#include <avr/io.h>
//#include <MrLcd/MrLCDmega32.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#include <avr/iom32.h>

static volatile int pulse = 0;
static volatile int i = 0;


int main(void)
{
  int16_t volatile count_a = 0; 
  //char show_a[16];	//for lcd
  //Initialise();
  
  // Set PORTD To Be Output Port (All The 8 Pins) eccept for pin 2 is input
  DDRD = 0b11111011;	
  // Set PORTB To Be Output Port (All The 8 Pins)
  DDRB = 0b11111111;
  
  PORTB=0xff;
  
  // Set PORTB To Be LOW For initial State
  _delay_ms(5000);

  PORTB =0;
    
  

  //GICR |= 1<<INT0;		for using interrupt
  //MCUCR |= 1<<ISC00;

  //sei();					global interrupt
 
  while(1)
  { 
    PORTD =1;			// Send Trigger Pulse To The Sensor
    _delay_us(15);
    PORTD =0;			
    
    while(!(PIND&4));	// Wait For The Echo Pulse From The Sensor
    TCCR1B = 2;			// Turn ON Timer Module
    while((PIND&4));	// Wait Until The Pulse Ends
    TCCR1B =0;			// Turn OFF The Timer
    pulse = TCNT1;		
    TCNT1=0;
   
    count_a =pulse/58;	// Calculate The Distance Using The Equation

    count_a/=5;
    switch(count_a){
        case 0:
            PORTB=1;
            break;
        case 1:
            PORTB=3;
            break;
        case 2:
            PORTB=7;
            break;
        case 3:
            PORTB=0x0f;
            break;
        default:
            PORTB=0;
    }
	/********** code for lcd screan **********/
    //Send_A_String("Distance Sensor");
    //GoToMrLCDLocation(1,2);
    //Send_A_String("Distance=");
    //itoa(count_a,show_a,10);
    //Send_A_String(show_a);
    //Send_A_String(" ");
    //GoToMrLCDLocation(13,2);
    //Send_A_String("cm");
    //GoToMrLCDLocation(1,1);
  }
}

/***********code for interrupt *****************/

//ISR(INT0_vect)
//{
//    
//  if(i == 0)
//  {
//    TCCR1B |= 1<<CS10;
//    i = 1;
//  }
//  else
//  {
//    TCCR1B = 0;
//    pulse = TCNT1;
//    TCNT1 = 0;
//    i = 0;
//  }
//}


