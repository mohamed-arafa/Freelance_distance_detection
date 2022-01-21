#include "config.h"
#define trigger RC2
#define echo    RC3
#define _XTAL_FREQ 4000000

// Definition Of The calc_dist() Function
int calc_dist(void)
{
  int distance=0;
  TMR1=0;
  // Send Trigger Pulse To The Sensor
  trigger=1;
  __delay_us(10);
  trigger=0;
  // Wait For The Echo Pulse From The Sensor
  while(!echo);
  // Turn ON Timer Module
  TMR1ON=1;
  // Wait Until The Pulse Ends
  while(echo);
  // Turn OFF The Timer
  TMR1ON=0;
  // Calculate The Distance Using The Equation
  distance=TMR1/58.82;
  return distance;
}

void main(void)
{
  // Create Distance Variable
  int dist=0;
  
  //--[ Configure The IO Pins ]--
  // Set PORTB To Be Output Port (All The 8 Pins)
  TRISB = 0x00;
  // Set PORTB To Be LOW For initial State
  PORTB=0xff;
  __delay_ms(1000);
  PORTB = 0x00;
  // Set RC2 To Be Output Pin ( Trigger )
  TRISC2 = 0;
  RC2 = 0;
  // Set RC3 To Be Input Pin ( Echo )
  TRISC3 = 1;
  
  //--[ Configure Timer Module To Operate in Timer Mode ]--
  // Clear The Pre-Scaler Select Bits
  T1CKPS0=0;
  T1CKPS1=0;
  // Choose The Local Clock As Clock Source
  TMR1CS=0;
  
  // Write The System's Main Routine !
  while(1)
  {
    dist = calc_dist()/5;
    if(dist==1)
    {PORTB = 0x01; __delay_ms(50);}
    if(dist==2)
    {PORTB = 0x03; __delay_ms(50);}
    if(dist==3)
    {PORTB = 0x07; __delay_ms(50);}
    if(dist==4)
    {PORTB = 0x0F; __delay_ms(50);}
    else
    {PORTB = 0x00; __delay_ms(50);}
  }
  return;
}