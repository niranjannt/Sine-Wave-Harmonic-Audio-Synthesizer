// File **********music.c***********
// Programs to play pre-programmed music and respond to switch inputs
// Spring 2025



#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"
#include "../inc/SysTickInts.h"
#include "Switch.h"
#include "../inc/TLV5616.h"
#include "mailbox.h"
#include "Timer1A.h"
    // write this// Period =  80000000/7272/Freq=11,001/Freq
#define C1   (38222/64)  // 2093 Hz
#define B1   (40490/64)   // 1975.5 Hz
#define BF1  (42902/64)   // 1864.7 Hz
#define A1   (45454/64)   // 1760 Hz
#define AF1  (48157/64)   // 1661.2 Hz
#define G1   (51020/64)   // 1568 Hz
#define GF1  (54054/64)   // 1480 Hz
#define F1   (57269/64)   // 1396.9 Hz
#define E1   (60675/64)   // 1318.5 Hz
#define EF1  (64282/64)   // 1244.5 Hz
#define D1   (68102/64)  // 1174.7 Hz
#define DF1  (72156/64)  // 1108.7 Hz
#define C    (76445/64)   // 1046.5 Hz
#define B    (80988/64)  // 987.8 Hz
#define BF   (85809/64)   // 932.3 Hz
#define A    (90909/64)   // 880 Hz
#define AF   (96315/64)   // 830.6 Hz
#define G    (102040/64)   // 784 Hz
#define GF  (108108/64)   // 740 Hz
#define F   (114531/64)   // 698.5 Hz
#define E   (121340/64)   // 659.3 Hz
#define EF  (128555/64)   // 622.3 Hz
#define D   (136216/64)   // 587.3 Hz
#define DF  (144300/64)   // 554.4 Hz
#define C0  (152875/64)   // 523.3 Hz
#define B0  (161976/64)   // 493.9 Hz
#define BF0 (171600/64)   // 466.2 Hz
#define A0  (181818/64)   // 440 Hz
#define AF0 (192631/64)   // 415.3 Hz
#define G0  (204081/64)   // 392 Hz
#define GF0 (216216/64)   // 370 Hz
#define F0  (229095/64)   // 349.2 Hz
#define E0  (242718/64)   // 329.6 Hz
#define EF0 (257152/64)   // 311.1 Hz
#define D0  (272386/64)   // 293.7 Hz
#define DF0 (288600/64)   // 277.2 Hz
#define C7  (305810/64)   // 261.6 Hz
#define B7  (324017/64)   // 246.9 Hz
#define BF7 (343200/64)   // 233.1 Hz
#define A7  (363636/64)   // 220 Hz
#define AF7 (385170/64)   // 207.7 Hz
#define G7  (408163/64)   // 196 Hz
#define GF7 (432432/64)   // 185 Hz
#define F7  (458190/64)   // 174.6 Hz
#define E7  (485436/64)   // 164.8 Hz
#define EF7 (514138/64)   // 155.6 Hz
#define D7  (544959/64)   // 146.8 Hz
#define DF7 (577200/64)   // 138.6 Hz
#define C6  (611620/64)   // 130.8 Hz
#define SONGSIZE 1
void playNote(void);

typedef struct{
	
uint32_t notereload;//const uint16_t *sound;
//uint32_t pitch;
//uint32_t harmony;
uint32_t noteduration;
	
} Note;

uint32_t currentnote;
Note song[] = {
    {A, 500},  
    {DF7, 500}, 
    {C6, 1000}, 

};


uint32_t switchnote;

typedef struct{
	Note* notes;
	uint32_t songlength;
	
	
	
} Song;


Song songlist[]={
	{song, 3},
	
};
uint32_t currentsong;
//-------------- Music_Init ----------------
// activate periodic interrupts and DAC
// Inputs: none
// Outputs: none

void Music_Init(void){
 DAC_Init(10);
 SysTick_Init(7272);
 Switch_Init();
 Timer1A_Init(80000);
}



void SysTick_Handler(void){ // called at 11 kHz
  // output one value to DAC if a sound is active
 playNote(); //Plays actual note


}



const uint16_t Wave[64] = {  
  1024,1122,1219,1314,1407,1495,1580,1658,1731,1797,1855,
  1906,1948,1981,2005,2019,2024,2019,2005,1981,1948,1906,
  1855,1797,1731,1658,1580,1495,1407,1314,1219,1122,1024,
  926,829,734,641,553,468,390,317,251,193,142,
  100,67,43,29,24,29,43,67,100,142,193,
  251,317,390,468,553,641,734,829,926
};  


void playNote(void){
	NVIC_ST_RELOAD_R=songlist[currentsong].notes[currentnote].notereload;
	NVIC_ST_CURRENT_R=0;
	static uint32_t sampleindex=0;
  DAC_Out(Wave[sampleindex]);
	sampleindex++;
  if(sampleindex>=64){
  sampleindex=0;

	}		
	switchnote++;
	
	
}
uint32_t mscounter;
void Timer1A_Handler(void){
	if(switchnote==((80000)/(songlist[currentsong].notes[currentnote].notereload))){
	 	mscounter++;
		switchnote=0;
		
	}
	if(mscounter==((songlist[currentsong].notes[currentnote].noteduration))){
	 mscounter=0;
   currentnote=((((currentnote+1))%(songlist[currentsong].songlength)));
	}
}


void Mode(void){	
uint32_t mode, moderelease=0;	
mode=ModeSwitch();
if(mode==16 && moderelease==0){
moderelease=mode;		
}
else if(mode==0 && moderelease==16){
currentsong=((currentsong+1)%	(SONGSIZE));
	
	
}	
	

}
uint32_t playpausetoggle=1;
void PausePlay(void){
uint32_t pauseplay, pauseplayrelease=0;	
pauseplay=PauseSwitch();
if(pauseplay==1 && pauseplayrelease==0){
pauseplayrelease=pauseplay;		
}
else if(pauseplay==0 && pauseplayrelease==1){
	 playpausetoggle=!playpausetoggle;
	 if(playpausetoggle==0){
		NVIC_ST_RELOAD_R=0; 
	
    }
   else if(playpausetoggle==1){	 
	NVIC_ST_RELOAD_R=songlist[currentsong].notes[currentnote].notereload;
	NVIC_ST_CURRENT_R=0;

	
	
	
	
	
}
	 }
 }

 
 void Rewind(void){
	uint32_t rewind, rewindrelease=0;
  rewind= RewindSwitch();
  if(rewind==16 && rewindrelease==0){ 
  rewindrelease=rewind;

 }
	if(rewind==0 && rewindrelease==16){
		 NVIC_ST_RELOAD_R=songlist[currentsong].notes[0].notereload;
		  rewindrelease=rewind;
	}
}
 
