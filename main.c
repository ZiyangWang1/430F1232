
#include <msp430.h>

int main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
  P1DIR |= 0x04;  
  P2DIR |= 0x02;                            // Set P2.1 to output direction
  P3DIR |= 0x40; 
  P1OUT &= 0xFB;
  P3OUT &= 0xBF;

  for (;;)
  {
    volatile unsigned int i;

    P2OUT ^= 0x02;                          // Toggle P2.1 using exclusive-OR

    i = 50000;                              // Delay
    do (i--);
    while (i != 0);
  }
}
