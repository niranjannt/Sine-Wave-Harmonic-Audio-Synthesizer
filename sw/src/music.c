// File **********music.c***********
// Programs to play pre-programmed music and respond to switch inputs
// Spring 2025



#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"
#include "../inc/SysTickInts.h"
#include "Switch.h"
#include "../inc/TLV5616.h"
#include "music.h"
#include "mailbox.h"
#include "Timer1A.h"
    // write this
    

//-------------- Music_Init ----------------
// activate periodic interrupts and DAC
// Inputs: none
// Outputs: none
// called once
uint32_t size;
const uint16_t *sound;

void Music_Init(void){
 DAC_Init(10);
 SysTick_Init(1);
 Switch_Init();
 Timer1A_Init(1);
}



void PlayMusic(uint32_t period ,const uint16_t *pt, uint32_t count){
	 NVIC_ST_RELOAD_R = period-1;// reload value
  NVIC_ST_CURRENT_R = 1;	
   size = count;
   sound = pt;
}

void StopMusic(void){
    NVIC_ST_RELOAD_R = 0;// either set LOAD to 0 or clear bit 1 in CTRL
    // write this
}



void SysTick_Handler(void){ // called at 11 kHz
  // output one value to DAC if a sound is active
    if(size){
      DAC_Out(*sound);
      sound++;
      size--;
    }
   else{
       NVIC_ST_RELOAD_R = 0;
    }


}





