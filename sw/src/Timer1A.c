#include <stdio.h>
#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"
#include "Timer1A.h"
void Timer1A_Init(uint32_t period){

  SYSCTL_RCGCTIMER_R |= 0x02;               // 1) activate Timer1
  while((SYSCTL_PRTIMER_R & 0x02) == 0){}   // 2) wait for clock to stabilize
  TIMER1_CTL_R = 0x00000000;                // 3) disable Timer1A during setup
  TIMER1_CFG_R = 0x00000000;                // 4) 32-bit mode
  TIMER1_TAMR_R = 0x00000002;               // 5) periodic mode
  TIMER1_TAILR_R = period - 1;              // 6) set reload value
  TIMER1_TAPR_R = 0;                        // 7) no prescale
  TIMER1_ICR_R = TIMER_ICR_TATOCINT;        // 8) clear timeout flag
  TIMER1_IMR_R = TIMER_IMR_TATOIM;
  NVIC_EN0_R |= (1 << 21);                  // 10) enable IRQ 21 in NVIC (Timer1A)
  TIMER1_CTL_R |= 0x01;                     // 11) enable Timer1A

}


