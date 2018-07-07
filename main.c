#include "configuration.h"

int main(void)
{
  u8 u8Data = 0;
    
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
  // Intialize the I/O registers
  P1SEL |= P1SEL_INIT;
  P2SEL |= P2SEL_INIT;
  P3SEL |= P3SEL_INIT;
  
  P1DIR |= P1DIR_INIT;
  P2DIR |= P2DIR_INIT;
  P3DIR |= P3DIR_INIT;
  
  P1OUT &= ~PX_2_Location;                  // Turn off PWM LED
  P3OUT &= ~PX_6_Location;                  // Turn off BELL
  P3OUT |= PX_1_Location|PX_2_Location|PX_3_Location;                   // Turn off RGB
  
  P1OUT |= PX_3_Location|PX_4_Location;                 // Turn off all LEDs
  P2OUT |= PX_1_Location|PX_5_Location;
  P3OUT |= PX_0_Location;
  

  for (;;)
  {
    volatile unsigned int i;

    P1OUT ^= PX_3_Location;                 // Toggle P1.3 using exclusive-OR
    P1OUT ^= PX_4_Location;                 // Toggle P1.4 using exclusive-OR
    P2OUT ^= PX_5_Location;                 // Toggle P2.5 using exclusive-OR
    
    if(P1IN & PX_6_Location)
    {
      P3OUT &= ~PX_0_Location;
    }
    else
    {
      P2OUT &= ~PX_1_Location;
    }
    
    P2OUT &= ~PX_4_Location;
    _74HC595_SendByte(_74HC595_EnCode(u8Data%10,false));
    _74HC595_SendByte(_74HC595_EnCode(u8Data%100/10,true));
    _74HC595_SendByte(_74HC595_EnCode(u8Data/100,false));
    P2OUT |= PX_4_Location;
    
    u8Data++;
    
    i = 50000;                              // Delay
    do (i--);
    while (i != 0);
  }
}
