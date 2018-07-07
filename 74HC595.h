#ifndef __74HC595_H
#define __74HC595_H

#include "configuration.h"

void _74HC595_SendByte(u8 u8Data)
{
  u8 u8Mask = 0x01;
  
  for(int i=0;i<8;i++)
  {
    if(u8Data & (u8Mask << i))
    {
      P1OUT |= PX_0_Location;
    }
    else
    {
      P1OUT &= ~PX_0_Location;
    }
    
    P2OUT |= PX_3_Location;
    
    for(int i=0;i<5;i++);
    
    P2OUT &= ~PX_3_Location;
    
    for(int i=0;i<5;i++);
    
  }
}

u8 _74HC595_EnCode(u8 u8Data,bool bDot)
{
  u8 u8Code = 0xFF;
  
  switch(u8Data)
  {
  case 0: u8Code = 0x03;break;
  case 1: u8Code = 0x9F;break;
  case 2: u8Code = 0x25;break;
  case 3: u8Code = 0x0D;break;
  case 4: u8Code = 0x99;break;
  case 5: u8Code = 0x49;break;
  case 6: u8Code = 0x41;break;
  case 7: u8Code = 0x1F;break;
  case 8: u8Code = 0x01;break;
  case 9: u8Code = 0x09;break;
  default: ;
  }
  
  if(bDot)
  {
    u8Code--;
  }
  
  return u8Code;
}


#endif // __74HC595_H
