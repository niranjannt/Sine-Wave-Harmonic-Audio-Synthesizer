// File **********music.h***********
// Lab 5
// Programs to play pre-programmed music and respond to switch
// inputs.
// EE445L Spring 2025


//-------------- Music_Init ----------------
// activate SysTick, Timer0 and Timer1 periodic interrupts,
// and DAC
// Inputs: none
// Outputs: none
// called once
#include <stdio.h>
#include <stdint.h>

void Music_Init(void);
void playNote(void);
 void Rewind(void);
void PausePlay(void);
void Mode(void);


	
const uint16_t WaveSmall[64] = {  
  1024,1122,1219,1314,1407,1495,1580,1658,1731,1797,1855,
  1906,1948,1981,2005,2019,2024,2019,2005,1981,1948,1906,
  1855,1797,1731,1658,1580,1495,1407,1314,1219,1122,1024,
  926,829,734,641,553,468,390,317,251,193,142,
  100,67,43,29,24,29,43,67,100,142,193,
  251,317,390,468,553,641,734,829,926
};  
