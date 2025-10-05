#include <stdio.h>
#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"
#include "Timer2A.h"
void Timer2A_Init(uint32_t period){

  SYSCTL_RCGCTIMER_R |= 0x04;               // 1) activate Timer1
  while((SYSCTL_PRTIMER_R & 0x04) == 0){}   // 2) wait for clock to stabilize
  TIMER2_CTL_R = 0x00000000;                // 3) disable Timer1A during setup
  TIMER2_CFG_R = 0x00000000;                // 4) 32-bit mode
  TIMER2_TAMR_R = 0x00000002;               // 5) periodic mode
  TIMER2_TAILR_R = period - 1;              // 6) set reload value
  TIMER2_TAPR_R = 0;                        // 7) no prescale
  TIMER2_ICR_R = TIMER_ICR_TATOCINT;        // 8) clear timeout flag
  TIMER2_IMR_R = TIMER_IMR_TATOIM;
  NVIC_EN0_R |= (1 << 23);                  // 10) enable IRQ 21 in NVIC (Timer1A)
  TIMER2_CTL_R |= 0x01;                     // 11) enable Timer1A

}
