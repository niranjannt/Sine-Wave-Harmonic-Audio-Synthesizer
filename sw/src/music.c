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
    // write this// Period =  80000000/7272/Freq=11,001/Freq
#define C7   (38222/64)  // 2093 Hz
#define B6  (40490/64)   // 1975.5 Hz
#define BF6  (42902/64)   // 1864.7 Hz
#define A6  (45454/64)   // 1760 Hz
#define AF6  (48157/64)   // 1661.2 Hz
#define G6   (51020/64)   // 1568 Hz
#define GF6  (54054/64)   // 1480 Hz
#define F6   (57269/64)   // 1396.9 Hz
#define E6   (60675/64)   // 1318.5 Hz
#define EF6  (64282/64)   // 1244.5 Hz
#define D6   (68102/64)  // 1174.7 Hz
#define DF6  (72156/64)  // 1108.7 Hz
#define C6   (76445/64)   // 1046.5 Hz
#define B5    (80988/64)  // 987.8 Hz
#define BF5   (85809/64)   // 932.3 Hz
#define A5    (90909/64)   // 880 Hz
#define AF5   (96315/64)   // 830.6 Hz
#define G5    (102040/64)   // 784 Hz
#define GF5  (108108/64)   // 740 Hz
#define F5   (114531/64)   // 698.5 Hz
#define E5   (121340/64)   // 659.3 Hz
#define EF5  (128555/64)   // 622.3 Hz
#define D5   (136216/64)   // 587.3 Hz
#define DF5  (144300/64)   // 554.4 Hz
#define C5  (152875/64)   // 523.3 Hz
#define B4  (161976/64)   // 493.9 Hz
#define BF4 (171600/64)   // 466.2 Hz
#define A4  (181818/64)   // 440 Hz
#define AF4 (192631/64)   // 415.3 Hz
#define G4 (204081/64)   // 392 Hz
#define GF4 (216216/64)   // 370 Hz
#define F4  (229095/64)   // 349.2 Hz
#define E4 (242718/64)   // 329.6 Hz
#define EF4 (257152/64)   // 311.1 Hz
#define D4  (272386/64)   // 293.7 Hz
#define DF4 (288600/64)   // 277.2 Hz
#define C4  (305810/64)   // 261.6 Hz
#define B3  (324017/64)   // 246.9 Hz
#define BF3 (343200/64)   // 233.1 Hz
#define A3  (363636/64)   // 220 Hz
#define AF3 (385170/64)   // 207.7 Hz
#define G3  (408163/64)   // 196 Hz
#define GF3 (432432/64)   // 185 Hz
#define F3  (458190/64)   // 174.6 Hz
#define E3  (485436/64)   // 164.8 Hz
#define EF3 (514138/64)   // 155.6 Hz
#define D3  (544959/64)   // 146.8 Hz
#define DF3 (577200/64)   // 138.6 Hz
#define C3  (611620/64)   // 130.8 Hz
#define SONGSIZE 2
void playNote(void);
#define Sixteenth 15000
#define Eighth 30000
#define Quarter 60000
#define Half 120000
#define Whole 240000
#define Silent 0



uint32_t currentnote;

typedef struct{
	
uint32_t notereload;//const uint16_t *sound;
//uint32_t pitch;
//uint32_t harmony;
uint32_t noteduration;
	
} Note;

uint32_t currentnote;
Note betteroffalonelead[] = {
    {F5, Eighth/135},{Silent, (Eighth * 14)/135},{E5, Eighth/135},{F5, Eighth/135},{Silent, (Eighth * 15)/135},
    {F5, Eighth/135},{Silent, (Eighth * 14)/135},{E5, Eighth/135},{F5, Eighth/135},{Silent, (Eighth * 15)/135},
    {F5, Eighth/135},{Silent, Eighth/135},{F5, Eighth/135},{D5, Eighth/135},{Silent, (Eighth * 7)/135},{C5, Eighth/135},{C6, Eighth/135},{Silent, Sixteenth/135},{C6, Eighth/135},{Silent, Sixteenth/135},{A5, Eighth/135},{F5, Eighth/135},{Silent, Eighth/135},{F5, Eighth/135},{D5, Eighth/135},{Silent, (Eighth * 7)/135},{C5, Eighth/135},{BF5, Eighth/135},{Silent, Sixteenth/135},{BF5, Eighth/135},{Silent, Sixteenth/135},{A5, Eighth/135},
    {F5, Eighth/135},{Silent, Eighth/135},{F5, Eighth/135},{D5, Eighth/135},{Silent, (Eighth * 7)/135},{C5, Eighth/135},{C6, Eighth/135},{Silent, Sixteenth/135},{C6, Eighth/135},{Silent, Sixteenth/135},{A5, Eighth/135},{F5, Eighth/135},{Silent, Eighth/135},{F5, Eighth/135},{D5, Eighth/135},{Silent, (Eighth * 7)/135},{C5, Eighth/135},{BF5, Eighth/135},{Silent, Sixteenth/135},{BF5, Eighth/135},{Silent, Sixteenth/135},{A5, Eighth/135},
    {F5, Eighth/135},{Silent, Eighth/135},{F5, Eighth/135},{D5, Eighth/135},{Silent, Eighth/135},{F5, Eighth/135},{Silent, Eighth/135},{F5, Eighth/135},{Silent, Eighth/135},{E5, Eighth/135},{Silent, Eighth/135},{C5, Eighth/135},{C6, Eighth/135},{Silent, Sixteenth/135},{C6, Eighth/135},{Silent, Sixteenth/135},{A5, Eighth/135},{F5, Eighth/135},{Silent, Eighth/135},{F5, Eighth/135},{D5, Eighth/135},{Silent, Eighth/135},{F5, Eighth/135},{Silent, Eighth/135},{F5, Eighth/135},{Silent, Eighth/135},{E5, Eighth/135},{Silent, Eighth/135},{C5, Eighth/135},{BF5, Eighth/135},{Silent, Sixteenth/135},{BF5, Eighth/135},{Silent, Sixteenth/135},{A5, Eighth/135},
    {F5, Eighth/135},{Silent, Eighth/135},{F5, Eighth/135},{D5, Eighth/135},{Silent, Eighth/135},{F5, Eighth/135},{Silent, Eighth/135},{F5, Eighth/135},{Silent, Eighth/135},{E5, Eighth/135},{Silent, Eighth/135},{C5, Eighth/135},{C6, Eighth/135},{Silent, Sixteenth/135},{C6, Eighth/135},{Silent, Sixteenth/135},{A5, Eighth/135},{F5, Eighth/135},{Silent, Eighth/135},{F5, Eighth/135},{D5, Eighth/135},{Silent, Eighth/135},{F5, Eighth/135},{Silent, Eighth/135},{F5, Eighth/135},{Silent, Eighth/135},{E5, Eighth/135},{Silent, Eighth/135},{C5, Eighth/135},{BF5, Eighth/135},{Silent, Sixteenth/135},{BF5, Eighth/135},{Silent, Sixteenth/135},{A5, Eighth/135},
    {F5, Eighth/135},{Silent, Eighth/135},{F5, Eighth/135},{D5, Eighth/135},{Silent, Eighth/135},{F5, Eighth/135},{Silent, Eighth/135},{F5, Eighth/135},{Silent, Eighth/135},{E5, Eighth/135},{Silent, Eighth/135},{C5, Eighth/135},{C6, Eighth/135},{Silent, Sixteenth/135},{C6, Eighth/135},{Silent, Sixteenth/135},{A5, Eighth/135},{F5, Eighth/135},{Silent, Eighth/135},{F5, Eighth/135},{D5, Eighth/135},{Silent, Eighth/135},{F5, Eighth/135},{Silent, Eighth/135},{F5, Eighth/135},{Silent, Eighth/135},{E5, Eighth/135},{Silent, Eighth/135},{C5, Eighth/135},{BF5, Eighth/135},{Silent, Sixteenth/135},{BF5, Eighth/135},{Silent, Sixteenth/135},{A5, Eighth/135},
    {F5, Eighth/135},{Silent, Eighth/135},{F5, Eighth/135},{D5, Eighth/135},{Silent, Eighth/135},{F5, Eighth/135},{Silent, Eighth/135},{F5, Eighth/135},{Silent, Eighth/135},{E5, Eighth/135},{Silent, Eighth/135},{C5, Eighth/135},{C6, Eighth/135},{Silent, Sixteenth/135},{C6, Eighth/135},{Silent, Sixteenth/135},{A5, Eighth/135},{F5, Eighth/135},{Silent, Eighth/135},{F5, Eighth/135},{D5, Eighth/135},{Silent, Eighth/135},{F5, Eighth/135},{Silent, Eighth/135},{F5, Eighth/135},{Silent, Eighth/135},{E5, Eighth/135},{Silent, Eighth/135},{C5, Eighth/135},{BF5, Eighth/135},{Silent, Sixteenth/135},{BF5, Eighth/135},{Silent, Sixteenth/135},{A5, Eighth/135},

};

Note betteroffalonebass[] = {

};

Note toujourlead[] = {
    {D4, Whole/128},{GF4, Whole/128},{B4, Whole/128},{G4, Whole/128},
    {D4, (Quarter * 2)/128},{GF4, Eighth/128},{Silent, Eighth/128},{GF4, Eighth/128},{D5, Eighth/128},{DF5, Quarter/128},{Silent, (Quarter * 5)/128},{B4, Eighth/128},{Silent, Eighth/128},{B4, Eighth/128},{A4, Eighth/128},{B4, Quarter/128},{Silent, (Quarter * 5)/128},
    {GF4, Eighth/128},{Silent, Eighth/128},{GF4, Eighth/128},{D5, Eighth/128},{DF5, Quarter/128},{Silent, (Quarter * 5)/128},{B4, Eighth/128},{Silent, Eighth/128},{B4, Eighth/128},{A4, Eighth/128},{B4, Quarter/128},{Silent, Quarter/128},{B4, Quarter/128},{Silent, Quarter/128},{B4, Quarter/128},{A4, Eighth/128},{B4, Quarter/128},{A4, Eighth/128},
    {GF4, Quarter/128},{Silent, Quarter/128},{GF4, Eighth/128},{Silent, Eighth/128},{GF4, Eighth/128},{D5, Eighth/128},{DF5, Quarter/128},{Silent, Quarter/128},{DF5, Eighth/128},{Silent, Eighth/128},{DF5, Eighth/128},{D5, Eighth/128},{B4, Quarter/128},{Silent, Quarter/128},{B4, Eighth/128},{Silent, Eighth/128},{B4, Eighth/128},{A4, Eighth/128},{B4, Eighth/128},{Silent, Eighth/128},{B4, Eighth/128},{Silent, Eighth/128},{B4, Eighth/128},{A4, Eighth/128},{B4, Eighth/128},{A4, Eighth/128},
    {GF4, Quarter/128},{Silent, Quarter/128},{GF4, Eighth/128},{Silent, Eighth/128},{GF4, Eighth/128},{D5, Eighth/128},{DF5, Quarter/128},{Silent, Quarter/128},{DF5, Eighth/128},{Silent, Eighth/128},{DF5, Eighth/128},{D5, Eighth/128},{B4, Quarter/128},{Silent, Quarter/128},{B4, Eighth/128},{Silent, Eighth/128},{B4, Eighth/128},{A4, Eighth/128},{B4, Eighth/128},{Silent, Eighth/128},{B4, Eighth/128},{Silent, Eighth/128},{B4, Eighth/128},{A4, Eighth/128},{B4, Eighth/128},{A4, Eighth/128},
    {GF4, Quarter/128},{Silent, Quarter/128},{GF4, Eighth/128},{Silent, Eighth/128},{GF4, Eighth/128},{D5, Eighth/128},{DF5, Quarter/128},{Silent, Quarter/128},{DF5, Eighth/128},{Silent, Eighth/128},{DF5, Eighth/128},{D5, Eighth/128},{B4, Quarter/128},{Silent, Quarter/128},{B4, Eighth/128},{Silent, Eighth/128},{B4, Eighth/128},{A4, Eighth/128},{B4, Eighth/128},{Silent, Eighth/128},{B4, Eighth/128},{Silent, Eighth/128},{B4, Eighth/128},{A4, Eighth/128},{B4, Eighth/128},{A4, Eighth/128},
    {GF4, Quarter/128},{Silent, Quarter/128},{GF4, Eighth/128},{Silent, Eighth/128},{GF4, Eighth/128},{D5, Eighth/128},{DF5, Quarter/128},{Silent, Quarter/128},{DF5, Eighth/128},{Silent, Eighth/128},{DF5, Eighth/128},{D5, Eighth/128},{B4, Quarter/128},{Silent, Quarter/128},{B4, Eighth/128},{Silent, Eighth/128},{B4, Eighth/128},{A4, Eighth/128},{B4, Eighth/128},{Silent, Eighth/128},{B4, Eighth/128},{Silent, Eighth/128},{B4, Eighth/128},{A4, Eighth/128},{B4, Eighth/128},{A4, Eighth/128},
    {GF4, Quarter/128},{Silent, Quarter/128},{GF4, Eighth/128},{Silent, Eighth/128},{GF4, Eighth/128},{D5, Eighth/128},{DF5, Quarter/128},{Silent, Quarter/128},{DF5, Eighth/128},{Silent, Eighth/128},{DF5, Eighth/128},{D5, Eighth/128},{B4, Quarter/128},{Silent, Quarter/128},{B4, Eighth/128},{Silent, Eighth/128},{B4, Eighth/128},{A4, Eighth/128},{B4, Quarter/128},{Silent, (Quarter * 3)/128}

};

uint32_t switchnote;

typedef struct{
	Note* notes;
	uint32_t songlength;
	
	
	
} Song;


Song songlist[]={
	{betteroffalonelead, 190},
	{toujourlead, 159}
	
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
 
