// TLV5616.c
// Runs on TM4C123
// Use SSI1 to send a 16-bit code to the TLV5616 and return the reply.
// Daniel Valvano
// EE445L Fall 2015
//    Jonathan W. Valvano 9/22/15

/* This example accompanies the book
   "Embedded Systems: Real Time Interfacing to ARM Cortex M Microcontrollers",
   ISBN: 978-1463590154, Jonathan Valvano, copyright (c) 2014

 Copyright 2014 by Jonathan W. Valvano, valvano@mail.utexas.edu
    You may use, edit, run or distribute this file
    as long as the above copyright notice remains
 THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 VALVANO SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 For more information about my classes, my research, and my books, see
 http://users.ece.utexas.edu/~valvano/
 */

// SSIClk (SCLK) connected to PD0
// SSIFss (FS)   connected to PD1
// SSITx (DIN)   connected to PD3

#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"

//----------------   DAC_Init     -------------------------------------------
// Initialize TLV5616 12-bit DAC
// assumes bus clock is 80 MHz
// inputs: initial voltage output (0 to 4095)
// outputs:none
void DAC_Init(uint16_t data){
    // write this
	  // Consider the following registers:
	  // SYSCTL_RCGCSSI_R, SSI1_CR1_R, SSI1_CPSR_R, SSI1_CR0_R, SSI1_DR_R, SSI1_CR1_R
	SYSCTL_RCGCSSI_R |= 0x2;
	SYSCTL_RCGCGPIO_R |= 0x8;
	while((SYSCTL_PRGPIO_R&0x08)==0){};
	GPIO_PORTD_AFSEL_R |= 0xB;
  GPIO_PORTD_DEN_R |= 0xB;
GPIO_PORTD_PCTL_R = (GPIO_PORTD_PCTL_R&0xFFFF0F00)+0x00002022;
	GPIO_PORTD_AMSEL_R = 0;		
	SSI1_CR1_R= 0;
	SSI1_CPSR_R = 0x08;
	SSI1_CR0_R &= ~(0x0000FF00);	// SPO=0; SPH =1; SCR =0;
	SSI1_CR0_R &= ~64;
  SSI1_CR0_R |= 128;
  SSI1_CR0_R |= 0x0F;
	SSI1_DR_R |= data;
	SSI1_CR1_R = 2;	
}

// --------------     DAC_Out   --------------------------------------------
// Send data to TLV5616 12-bit DAC
// inputs:  voltage output (0 to 4095)
// 
void DAC_Out(uint16_t code){
    // write this
    // Consider the following registers:
	  // SSI1_SR_R, SSI1_DR_R
	  while((SSI1_SR_R&0x00000002)==0){};// SSI Transmit FIFO Not Full
  SSI1_DR_R = code; 
}                // data out, no reply



// --------------     DAC_OutNonBlocking   ------------------------------------
// Send data to TLV5616 12-bit DAC without checking for room in the FIFO
// inputs:  voltage output (0 to 4095)
// 
void DAC_Out_NB(uint16_t code){
    // Consider writing this (If it is what your heart desires)
    // Consider the following registers:
	  // SSI1_SR_R, SSI1_DR_R
}
