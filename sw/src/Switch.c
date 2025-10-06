// File **********Switch.c***********
// Spring 2025

// define your hardware interface



#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"
    // write this
    
void Switch_Init(){

	          SYSCTL_RCGCGPIO_R |= 0x20;        // 1) activate clock for Port F
            while((SYSCTL_PRGPIO_R & 0x20) == 0){}; // wait for clock to stabilize
            GPIO_PORTF_LOCK_R = 0x4C4F434B;   // 2) unlock GPIO Port F
            GPIO_PORTF_CR_R |= 0x11;          // allow changes to PF0, PF4
            GPIO_PORTF_DIR_R &= ~0x11;        // 3) make PF0, PF4 inputs
            GPIO_PORTF_DEN_R |= 0x11;         // 4) enable digital I/O on PF0, PF4
            GPIO_PORTF_PUR_R |= 0x11;         // 5) enable weak pull-up on PF0, PF4
        SYSCTL_RCGCGPIO_R |= 0x04;  // activate clock for Port C
         while((SYSCTL_PRGPIO_R & 0x04) == 0){}; // wait for clock to stabilize
        GPIO_PORTC_DIR_R &= ~64;  // direction PC6 input
        GPIO_PORTC_DEN_R |= 64;   // enable PC6 digital port

}



uint32_t ModeSwitch(){

return((GPIO_PORTC_DATA_R&64));
	
}

uint32_t PauseSwitch(){
	
return(((~GPIO_PORTF_DATA_R&1)));	
	
}


uint32_t RewindSwitch(){
	
return(((~GPIO_PORTF_DATA_R&16)));	
	
}