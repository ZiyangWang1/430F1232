#include "configuration.h"

int main(void)
{
  u32 u32Display = 0;
  u8 u8Data = 0;
  volatile unsigned int i = 0;
    
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
  
  ADC10CTL0 = ADC10SHT_2 + ADC10ON + ADC10IE; // ADC10ON, interrupt enabled
  ADC10AE |= 0x01;                          // P2.0 ADC option select
  

  for (;;)
  {
    i++;
    
    ADC10CTL0 |= ENC + ADC10SC;             // Sampling and conversion start
    __bis_SR_register(CPUOFF + GIE);        // LPM0, ADC10_ISR will force exit
    
    if(P1IN & PX_6_Location)
    {
      P3OUT |= PX_0_Location;
      P2OUT |= PX_1_Location;
    }
    else
    {
      P3OUT &= ~PX_0_Location;
      P2OUT &= ~PX_1_Location;
    }
      
    if(i==1000)
    {
      P1OUT ^= PX_3_Location;                 // Toggle P1.3 using exclusive-OR
      P1OUT ^= PX_4_Location;                 // Toggle P1.4 using exclusive-OR
      P2OUT ^= PX_5_Location;                 // Toggle P2.5 using exclusive-OR
      
      u32Display = 330000 * ADC10MEM / 1023000;
      P2OUT &= ~PX_4_Location;
      _74HC595_SendByte(_74HC595_EnCode(u32Display%10,false));
      _74HC595_SendByte(_74HC595_EnCode(u32Display%100/10,false));
      _74HC595_SendByte(_74HC595_EnCode(u32Display%1000/100,true));
      P2OUT |= PX_4_Location;
      
      u8Data++;
      i = 0;
    }
  }
}

// ADC10 interrupt service routine
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR (void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(ADC10_VECTOR))) ADC10_ISR (void)
#else
#error Compiler not supported!
#endif
{
    __bic_SR_register_on_exit(CPUOFF);      // Clear CPUOFF bit from 0(SR)
}
