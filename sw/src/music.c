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
#define CC7   (38222/64)  // 2093 Hz
#define BB6  (40490/64)   // 1975.5 Hz
#define BF6  (42902/64)   // 1864.7 Hz
#define AA6  (45454/64)   // 1760 Hz
#define AF6  (48157/64)   // 1661.2 Hz
#define GG6   (51020/64)   // 1568 Hz
#define GF6  (54054/64)   // 1480 Hz
#define FF6   (57269/64)   // 1396.9 Hz
#define EE6   (60675/64)   // 1318.5 Hz
#define EF6  (64282/64)   // 1244.5 Hz
#define DD6   (68102/64)  // 1174.7 Hz
#define DF6  (72156/64)  // 1108.7 Hz
#define CC6   (76445/64)   // 1046.5 Hz
#define BB5    (80988/64)  // 987.8 Hz
#define BF5   (85809/64)   // 932.3 Hz
#define AA5    (90909/64)   // 880 Hz
#define AF5   (96315/64)   // 830.6 Hz
#define GG5    (102040/64)   // 784 Hz
#define GF5  (108108/64)   // 740 Hz
#define FF5   (114531/64)   // 698.5 Hz
#define EE5   (121340/64)   // 659.3 Hz
#define EF5  (128555/64)   // 622.3 Hz
#define DD5   (136216/64)   // 587.3 Hz
#define DF5  (144300/64)   // 554.4 Hz
#define CC5  (152875/64)   // 523.3 Hz
#define BB4  (161976/64)   // 493.9 Hz
#define BF4 (171600/64)   // 466.2 Hz
#define AA4  (181818/64)   // 440 Hz
#define AF4 (192631/64)   // 415.3 Hz
#define GG4 (204081/64)   // 392 Hz
#define GF4 (216216/64)   // 370 Hz
#define FF4  (229095/64)   // 349.2 Hz
#define EE4 (242718/64)   // 329.6 Hz
#define EF4 (257152/64)   // 311.1 Hz
#define DD4  (272386/64)   // 293.7 Hz
#define DF4 (288600/64)   // 277.2 Hz
#define CC4  (305810/64)   // 261.6 Hz
#define BB3  (324017/64)   // 246.9 Hz
#define BF3 (343200/64)   // 233.1 Hz
#define AA3  (363636/64)   // 220 Hz
#define AF3 (385170/64)   // 207.7 Hz
#define GG3  (408163/64)   // 196 Hz
#define GF3 (432432/64)   // 185 Hz
#define FF3  (458190/64)   // 174.6 Hz
#define EE3  (485436/64)   // 164.8 Hz
#define EF3 (514138/64)   // 155.6 Hz
#define DD3  (544959/64)   // 146.8 Hz
#define DF3 (577200/64)   // 138.6 Hz
#define CC3  (611620/64)   // 130.8 Hz
#define SONGSIZE 2
void playNote(void);
#define Sixteenth 15000
#define Eighth 30000
#define Quarter 60000
#define Half 120000
#define Whole 240000
#define Silent 0
void  playleadnote(void);
void playbassnote(void);


uint32_t currentnotelead;
uint32_t currentnotebass;

typedef struct{
	
uint32_t notereload;//const uint16_t *sound;
//uint32_t pitch;
//uint32_t harmony;
uint32_t noteduration;
	
} Note;

//uint32_t currentnote;
Note betteroffalonelead[] = { // length is 190

    {CC5, Eighth/135},{Silent, (Eighth * 14)/135},{BB4, Eighth/135},{CC5, Eighth/135},{Silent, (Eighth * 15)/135},

    {CC5, Eighth/135},{Silent, (Eighth * 14)/135},{BB4, Eighth/135},{CC5, Eighth/135},{Silent, (Eighth * 15)/135},

    {CC5, Eighth/135},{Silent, Eighth/135},{CC5, Eighth/135},{AA4, Eighth/135},{Silent, (Eighth * 7)/135},{GG4, Eighth/135},{GG5, Eighth/135},{Silent, Sixteenth/135},{GG5, Eighth/135},{Silent, Sixteenth/135},{EE5, Eighth/135},{CC5, Eighth/135},{Silent, Eighth/135},{CC5, Eighth/135},{AA4, Eighth/135},{Silent, (Eighth * 7)/135},{GG4, Eighth/135},{FF5, Eighth/135},{Silent, Sixteenth/135},{FF5, Eighth/135},{Silent, Sixteenth/135},{EE5, Eighth/135},

    {CC5, Eighth/135},{Silent, Eighth/135},{CC5, Eighth/135},{AA4, Eighth/135},{Silent, (Eighth * 7)/135},{GG4, Eighth/135},{GG5, Eighth/135},{Silent, Sixteenth/135},{GG5, Eighth/135},{Silent, Sixteenth/135},{EE5, Eighth/135},{CC5, Eighth/135},{Silent, Eighth/135},{CC5, Eighth/135},{AA4, Eighth/135},{Silent, (Eighth * 7)/135},{GG4, Eighth/135},{FF5, Eighth/135},{Silent, Sixteenth/135},{FF5, Eighth/135},{Silent, Sixteenth/135},{EE5, Eighth/135},

    {CC5, Eighth/135},{Silent, Eighth/135},{CC5, Eighth/135},{AA4, Eighth/135},{Silent, Eighth/135},{CC5, Eighth/135},{Silent, Eighth/135},{CC5, Eighth/135},{Silent, Eighth/135},{BB4, Eighth/135},{Silent, Eighth/135},{GG4, Eighth/135},{GG5, Eighth/135},{Silent, Sixteenth/135},{GG5, Eighth/135},{Silent, Sixteenth/135},{EE5, Eighth/135},{CC5, Eighth/135},{Silent, Eighth/135},{CC5, Eighth/135},{AA4, Eighth/135},{Silent, Eighth/135},{CC5, Eighth/135},{Silent, Eighth/135},{CC5, Eighth/135},{Silent, Eighth/135},{BB4, Eighth/135},{Silent, Eighth/135},{GG4, Eighth/135},{FF5, Eighth/135},{Silent, Sixteenth/135},{FF5, Eighth/135},{Silent, Sixteenth/135},{EE5, Eighth/135},

    {CC5, Eighth/135},{Silent, Eighth/135},{CC5, Eighth/135},{AA4, Eighth/135},{Silent, Eighth/135},{CC5, Eighth/135},{Silent, Eighth/135},{CC5, Eighth/135},{Silent, Eighth/135},{BB4, Eighth/135},{Silent, Eighth/135},{GG4, Eighth/135},{GG5, Eighth/135},{Silent, Sixteenth/135},{GG5, Eighth/135},{Silent, Sixteenth/135},{EE5, Eighth/135},{CC5, Eighth/135},{Silent, Eighth/135},{CC5, Eighth/135},{AA4, Eighth/135},{Silent, Eighth/135},{CC5, Eighth/135},{Silent, Eighth/135},{CC5, Eighth/135},{Silent, Eighth/135},{BB4, Eighth/135},{Silent, Eighth/135},{GG4, Eighth/135},{FF5, Eighth/135},{Silent, Sixteenth/135},{FF5, Eighth/135},{Silent, Sixteenth/135},{EE5, Eighth/135},

    {CC5, Eighth/135},{Silent, Eighth/135},{CC5, Eighth/135},{AA4, Eighth/135},{Silent, Eighth/135},{CC5, Eighth/135},{Silent, Eighth/135},{CC5, Eighth/135},{Silent, Eighth/135},{BB4, Eighth/135},{Silent, Eighth/135},{GG4, Eighth/135},{GG5, Eighth/135},{Silent, Sixteenth/135},{GG5, Eighth/135},{Silent, Sixteenth/135},{EE5, Eighth/135},{CC5, Eighth/135},{Silent, Eighth/135},{CC5, Eighth/135},{AA4, Eighth/135},{Silent, Eighth/135},{CC5, Eighth/135},{Silent, Eighth/135},{CC5, Eighth/135},{Silent, Eighth/135},{BB4, Eighth/135},{Silent, Eighth/135},{GG4, Eighth/135},{FF5, Eighth/135},{Silent, Sixteenth/135},{FF5, Eighth/135},{Silent, Sixteenth/135},{EE5, Eighth/135},

    {CC5, Eighth/135},{Silent, Eighth/135},{CC5, Eighth/135},{AA4, Eighth/135},{Silent, Eighth/135},{CC5, Eighth/135},{Silent, Eighth/135},{CC5, Eighth/135},{Silent, Eighth/135},{BB4, Eighth/135},{Silent, Eighth/135},{GG4, Eighth/135},{GG5, Eighth/135},{Silent, Sixteenth/135},{GG5, Eighth/135},{Silent, Sixteenth/135},{EE5, Eighth/135},{CC5, Eighth/135},{Silent, Eighth/135},{CC5, Eighth/135},{AA4, Eighth/135},{Silent, Eighth/135},{CC5, Eighth/135},{Silent, Eighth/135},{CC5, Eighth/135},{Silent, Eighth/135},{BB4, Eighth/135},{Silent, Eighth/135},{GG4, Eighth/135},{FF5, Eighth/135},{Silent, Sixteenth/135},{FF5, Eighth/135},{Silent, Sixteenth/135},{EE5, Eighth/135},



};



Note betteroffalonebass[] = { // length is 193

    {FF3, Eighth/135},{FF4, Eighth/135},{FF3, Eighth/135},{FF4, Eighth/135},{FF3, Eighth/135},{FF4, Eighth/135},{FF3, Eighth/135},{FF4, Eighth/135},{EE3, Eighth/135},{EE4, Eighth/135},{EE3, Eighth/135},{EE4, Eighth/135},{EE3, Eighth/135},{EE4, Eighth/135},{EE3, Eighth/135},{EE4, Eighth/135},{AA3, Eighth/135},{AA4, Eighth/135},{AA3, Eighth/135},{AA4, Eighth/135},{AA3, Eighth/135},{AA4, Eighth/135},{AA3, Eighth/135},{AA4, Eighth/135},{GG3, Eighth/135},{GG4, Eighth/135},{GG3, Eighth/135},{GG4, Eighth/135},{GG3, Eighth/135},{GG4, Eighth/135},{GG3, Eighth/135},{GG4, Eighth/135},

    {FF3, Eighth/135},{FF4, Eighth/135},{FF3, Eighth/135},{FF4, Eighth/135},{FF3, Eighth/135},{FF4, Eighth/135},{FF3, Eighth/135},{FF4, Eighth/135},{EE3, Eighth/135},{EE4, Eighth/135},{EE3, Eighth/135},{EE4, Eighth/135},{EE3, Eighth/135},{EE4, Eighth/135},{EE3, Eighth/135},{EE4, Eighth/135},{AA3, Eighth/135},{AA4, Eighth/135},{AA3, Eighth/135},{AA4, Eighth/135},{AA3, Eighth/135},{AA4, Eighth/135},{AA3, Eighth/135},{AA4, Eighth/135},{GG3, Eighth/135},{GG4, Eighth/135},{GG3, Eighth/135},{GG4, Eighth/135},{GG3, Eighth/135},{GG4, Eighth/135},{GG3, Eighth/135},{GG4, Eighth/135},

    {FF3, Eighth/135},{FF4, Eighth/135},{FF3, Eighth/135},{FF4, Eighth/135},{FF3, Eighth/135},{FF4, Eighth/135},{FF3, Eighth/135},{FF4, Eighth/135},{EE3, Eighth/135},{EE4, Eighth/135},{EE3, Eighth/135},{EE4, Eighth/135},{EE3, Eighth/135},{EE4, Eighth/135},{EE3, Eighth/135},{EE4, Eighth/135},{AA3, Eighth/135},{AA4, Eighth/135},{AA3, Eighth/135},{AA4, Eighth/135},{AA3, Eighth/135},{AA4, Eighth/135},{AA3, Eighth/135},{AA4, Eighth/135},{GG3, Eighth/135},{GG4, Eighth/135},{GG3, Eighth/135},{GG4, Eighth/135},{GG3, Eighth/135},{GG4, Eighth/135},{GG3, Eighth/135},{GG4, Eighth/135},

    {FF3, Eighth/135},{FF4, Eighth/135},{FF3, Eighth/135},{FF4, Eighth/135},{FF3, Eighth/135},{FF4, Eighth/135},{FF3, Eighth/135},{FF4, Eighth/135},{EE3, Eighth/135},{EE4, Eighth/135},{EE3, Eighth/135},{EE4, Eighth/135},{EE3, Eighth/135},{EE4, Eighth/135},{EE3, Eighth/135},{EE4, Eighth/135},{AA3, Eighth/135},{AA4, Eighth/135},{AA3, Eighth/135},{AA4, Eighth/135},{AA3, Eighth/135},{AA4, Eighth/135},{AA3, Eighth/135},{AA4, Eighth/135},{GG3, Eighth/135},{GG4, Eighth/135},{GG3, Eighth/135},{GG4, Eighth/135},{GG3, Eighth/135},{GG4, Eighth/135},{GG3, Eighth/135},{GG4, Eighth/135},

    {Silent, (Whole * 8)/135},

    {FF3, Eighth/135},{FF4, Eighth/135},{FF3, Eighth/135},{FF4, Eighth/135},{FF3, Eighth/135},{FF4, Eighth/135},{FF3, Eighth/135},{FF4, Eighth/135},{EE3, Eighth/135},{EE4, Eighth/135},{EE3, Eighth/135},{EE4, Eighth/135},{EE3, Eighth/135},{EE4, Eighth/135},{EE3, Eighth/135},{EE4, Eighth/135},{AA3, Eighth/135},{AA4, Eighth/135},{AA3, Eighth/135},{AA4, Eighth/135},{AA3, Eighth/135},{AA4, Eighth/135},{AA3, Eighth/135},{AA4, Eighth/135},{GG3, Eighth/135},{GG4, Eighth/135},{GG3, Eighth/135},{GG4, Eighth/135},{GG3, Eighth/135},{GG4, Eighth/135},{GG3, Eighth/135},{GG4, Eighth/135},

    {FF3, Eighth/135},{FF4, Eighth/135},{FF3, Eighth/135},{FF4, Eighth/135},{FF3, Eighth/135},{FF4, Eighth/135},{FF3, Eighth/135},{FF4, Eighth/135},{EE3, Eighth/135},{EE4, Eighth/135},{EE3, Eighth/135},{EE4, Eighth/135},{EE3, Eighth/135},{EE4, Eighth/135},{EE3, Eighth/135},{EE4, Eighth/135},{AA3, Eighth/135},{AA4, Eighth/135},{AA3, Eighth/135},{AA4, Eighth/135},{AA3, Eighth/135},{AA4, Eighth/135},{AA3, Eighth/135},{AA4, Eighth/135},{GG3, Eighth/135},{GG4, Eighth/135},{GG3, Eighth/135},{GG4, Eighth/135},{GG3, Eighth/135},{GG4, Eighth/135},{GG3, Eighth/135},{GG4, Eighth/135},

};





Note toujourlead[] = { // length is 159

    {DD4, Whole/128},{GF4, Whole/128},{BB4, Whole/128},{GG4, Whole/128},

    {DD4, (Quarter * 2)/128},{GF4, Eighth/128},{Silent, Eighth/128},{GF4, Eighth/128},{DD5, Eighth/128},{DF5, Quarter/128},{Silent, (Quarter * 5)/128},{BB4, Eighth/128},{Silent, Eighth/128},{BB4, Eighth/128},{AA4, Eighth/128},{BB4, Quarter/128},{Silent, (Quarter * 5)/128},

    {GF4, Eighth/128},{Silent, Eighth/128},{GF4, Eighth/128},{DD5, Eighth/128},{DF5, Quarter/128},{Silent, (Quarter * 5)/128},{BB4, Eighth/128},{Silent, Eighth/128},{BB4, Eighth/128},{AA4, Eighth/128},{BB4, Eighth/128},{Silent, Eighth/128},{BB4, Eighth/128},{Silent, Eighth/128},{BB4, Eighth/128},{AA4, Eighth/128},{BB4, Eighth/128},{AA4, Eighth/128},

    {GF4, Quarter/128},{Silent, Quarter/128},{GF4, Eighth/128},{Silent, Eighth/128},{GF4, Eighth/128},{DD5, Eighth/128},{DF5, Quarter/128},{Silent, Quarter/128},{DF5, Eighth/128},{Silent, Eighth/128},{DF5, Eighth/128},{DD5, Eighth/128},{BB4, Quarter/128},{Silent, Quarter/128},{BB4, Eighth/128},{Silent, Eighth/128},{BB4, Eighth/128},{AA4, Eighth/128},{BB4, Eighth/128},{Silent, Eighth/128},{BB4, Eighth/128},{Silent, Eighth/128},{BB4, Eighth/128},{AA4, Eighth/128},{BB4, Eighth/128},{AA4, Eighth/128},

    {GF4, Quarter/128},{Silent, Quarter/128},{GF4, Eighth/128},{Silent, Eighth/128},{GF4, Eighth/128},{DD5, Eighth/128},{DF5, Quarter/128},{Silent, Quarter/128},{DF5, Eighth/128},{Silent, Eighth/128},{DF5, Eighth/128},{DD5, Eighth/128},{BB4, Quarter/128},{Silent, Quarter/128},{BB4, Eighth/128},{Silent, Eighth/128},{BB4, Eighth/128},{AA4, Eighth/128},{BB4, Eighth/128},{Silent, Eighth/128},{BB4, Eighth/128},{Silent, Eighth/128},{BB4, Eighth/128},{AA4, Eighth/128},{BB4, Eighth/128},{AA4, Eighth/128},

    {GF4, Quarter/128},{Silent, Quarter/128},{GF4, Eighth/128},{Silent, Eighth/128},{GF4, Eighth/128},{DD5, Eighth/128},{DF5, Quarter/128},{Silent, Quarter/128},{DF5, Eighth/128},{Silent, Eighth/128},{DF5, Eighth/128},{DD5, Eighth/128},{BB4, Quarter/128},{Silent, Quarter/128},{BB4, Eighth/128},{Silent, Eighth/128},{BB4, Eighth/128},{AA4, Eighth/128},{BB4, Eighth/128},{Silent, Eighth/128},{BB4, Eighth/128},{Silent, Eighth/128},{BB4, Eighth/128},{AA4, Eighth/128},{BB4, Eighth/128},{AA4, Eighth/128},

    {GF4, Quarter/128},{Silent, Quarter/128},{GF4, Eighth/128},{Silent, Eighth/128},{GF4, Eighth/128},{DD5, Eighth/128},{DF5, Quarter/128},{Silent, Quarter/128},{DF5, Eighth/128},{Silent, Eighth/128},{DF5, Eighth/128},{DD5, Eighth/128},{BB4, Quarter/128},{Silent, Quarter/128},{BB4, Eighth/128},{Silent, Eighth/128},{BB4, Eighth/128},{AA4, Eighth/128},{BB4, Eighth/128},{Silent, Eighth/128},{BB4, Eighth/128},{Silent, Eighth/128},{BB4, Eighth/128},{AA4, Eighth/128},{BB4, Eighth/128},{AA4, Eighth/128},

    {GF4, Quarter/128},{Silent, Quarter/128},{GF4, Eighth/128},{Silent, Eighth/128},{GF4, Eighth/128},{DD5, Eighth/128},{DF5, Quarter/128},{Silent, Quarter/128},{DF5, Eighth/128},{Silent, Eighth/128},{DF5, Eighth/128},{DD5, Eighth/128},{BB4, Quarter/128},{Silent, Quarter/128},{BB4, Eighth/128},{Silent, Eighth/128},{BB4, Eighth/128},{AA4, Eighth/128},{BB4, Quarter/128},{Silent, (Quarter * 3)/128}



};



Note toujourbass[] = { // length is 116

    {DD3, Whole/128},{GF3, Whole/128},{BB3, Whole/128},{GG3, Whole/128},

    {DD3, Whole/128},{GF3, Whole/128},{BB3, Whole/128},{GG3, Whole/128},

    {DD3, Whole/128},{GF3, Whole/128},{BB3, Whole/128},{GG3, Whole/128},

    {DD3, Whole/128},{GF3, Whole/128},{BB3, Whole/128},{GG3, Whole/128},

    {DD3, Whole/128},{GF3, Whole/128},{BB3, Whole/128},{GG3, Whole/128},

    {DD3, Eighth/128},{DD4, Eighth/128},{DD3, Eighth/128},{DD4, Eighth/128},{DD3, Eighth/128},{DD4, Eighth/128},{DD3, Eighth/128},{DD4, Eighth/128},{GF3, Eighth/128},{GF4, Eighth/128},{GF3, Eighth/128},{GF4, Eighth/128},{GF3, Eighth/128},{GF4, Eighth/128},{GF3, Eighth/128},{GF4, Eighth/128},{BB3, Eighth/128},{BB4, Eighth/128},{BB3, Eighth/128},{BB4, Eighth/128},{BB3, Eighth/128},{BB4, Eighth/128},{BB3, Eighth/128},{BB4, Eighth/128},{GG3, Eighth/128},{GG4, Eighth/128},{GG3, Eighth/128},{GG4, Eighth/128},{GG3, Eighth/128},{GG4, Eighth/128},{GG3, Eighth/128},{GG4, Eighth/128},

    {DD3, Eighth/128},{DD4, Eighth/128},{DD3, Eighth/128},{DD4, Eighth/128},{DD3, Eighth/128},{DD4, Eighth/128},{DD3, Eighth/128},{DD4, Eighth/128},{GF3, Eighth/128},{GF4, Eighth/128},{GF3, Eighth/128},{GF4, Eighth/128},{GF3, Eighth/128},{GF4, Eighth/128},{GF3, Eighth/128},{GF4, Eighth/128},{BB3, Eighth/128},{BB4, Eighth/128},{BB3, Eighth/128},{BB4, Eighth/128},{BB3, Eighth/128},{BB4, Eighth/128},{BB3, Eighth/128},{BB4, Eighth/128},{GG3, Eighth/128},{GG4, Eighth/128},{GG3, Eighth/128},{GG4, Eighth/128},{GG3, Eighth/128},{GG4, Eighth/128},{GG3, Eighth/128},{GG4, Eighth/128},

    {DD3, Eighth/128},{DD4, Eighth/128},{DD3, Eighth/128},{DD4, Eighth/128},{DD3, Eighth/128},{DD4, Eighth/128},{DD3, Eighth/128},{DD4, Eighth/128},{GF3, Eighth/128},{GF4, Eighth/128},{GF3, Eighth/128},{GF4, Eighth/128},{GF3, Eighth/128},{GF4, Eighth/128},{GF3, Eighth/128},{GF4, Eighth/128},{BB3, Eighth/128},{BB4, Eighth/128},{BB3, Eighth/128},{BB4, Eighth/128},{BB3, Eighth/128},{BB4, Eighth/128},{BB3, Eighth/128},{BB4, Eighth/128},{GG3, Eighth/128},{GG4, Eighth/128},{GG3, Eighth/128},{GG4, Eighth/128},{GG3, Eighth/128},{GG4, Eighth/128},{GG3, Eighth/128},{GG4, Eighth/128},

};




uint32_t switchnote;

typedef struct{
	Note* lead;
	uint32_t leadlength;
	Note* bass;
	uint32_t basslength;
	
	
	
} Song;


Song songlist[]={
    {toujourlead, 159, toujourbass, 116},
	{betteroffalonelead, 190, betteroffalonebass, 193},
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

uint32_t nosoundlead=0;
uint32_t previousnote=1;
void SysTick_Handler(void){ // called at 11 kHz
  // output one value to DAC if a sound is active
	if(currentnotelead!=previousnote){
	if(songlist[currentsong].lead[currentnotelead].notereload==0){
		nosoundlead=1;
//		NVIC_ST_RELOAD_R=10;
//	NVIC_ST_CURRENT_R=0;
	previousnote=currentnotelead;
	
	}
	else{
	    nosoundlead = 0;
	NVIC_ST_RELOAD_R=songlist[currentsong].lead[currentnotelead].notereload;
	NVIC_ST_CURRENT_R=0;
	previousnote=currentnotelead;
	}
	}
 playleadnote(); //Plays actual note

}



const uint16_t Wave[64] = {  
  1024,1122,1219,1314,1407,1495,1580,1658,1731,1797,1855,
  1906,1948,1981,2005,2019,2024,2019,2005,1981,1948,1906,
  1855,1797,1731,1658,1580,1495,1407,1314,1219,1122,1024,
  926,829,734,641,553,468,390,317,251,193,142,
  100,67,43,29,24,29,43,67,100,142,193,
  251,317,390,468,553,641,734,829,926
};  

	static uint32_t leadindex=0;
  static uint32_t bassindex=0;

void playleadnote(void){
	if(nosoundlead==1){
		DAC_Out(Wave[leadindex]+Wave[bassindex]);
	}
	else{
  DAC_Out(Wave[leadindex]+Wave[bassindex]);
	leadindex++;
  if(leadindex>=64){
  leadindex=0;

	}		
}
	
}
uint32_t mscounterlead;
uint32_t mscounterbass;
void Timer1A_Handler(void){
	  TIMER1_ICR_R = TIMER_ICR_TATOCINT;  // acknowledge timeout
	 	mscounterlead++;
		mscounterbass++;
	
	if(mscounterlead==((songlist[currentsong].lead[currentnotelead].noteduration))){
	 mscounterlead=0;
   currentnotelead=((((currentnotelead+1))%(songlist[currentsong].leadlength)));
	}
	if(mscounterbass==((songlist[currentsong].bass[currentnotebass].noteduration))){
		mscounterbass=0;
		currentnotebass=((((currentnotebass+1))%(songlist[currentsong].basslength)));

		
}
}

void Mode(void){	
uint32_t mode, moderelease=0;	
mode=ModeSwitch();
if(mode==16 && moderelease==0){
currentsong=((currentsong+1)%	(SONGSIZE));	
moderelease=mode;		
}
else if(mode==0 && moderelease==16){
moderelease=mode;		
	
	
}	
	

}
uint32_t playpausetoggle=1;
void PausePlay(void){
uint32_t pauseplay, pauseplayrelease=0;	
pauseplay=PauseSwitch();
if(pauseplay==1 && pauseplayrelease==0){
	 playpausetoggle=!playpausetoggle;
	 if(playpausetoggle==0){
     NVIC_ST_CTRL_R &= ~0x01; 
		 TIMER2_CTL_R &= ~0x01;
	
    }
   else if(playpausetoggle==1){	 
	NVIC_ST_CTRL_R |= 0x01;
	NVIC_ST_RELOAD_R=songlist[currentsong].lead[currentnotelead].notereload;
	NVIC_ST_CURRENT_R=0;
	TIMER2_TAILR_R=songlist[currentsong].bass[currentnotebass].notereload;
	TIMER2_TAR_R=0;


	
	
	
	
	
}	
pauseplayrelease=pauseplay;		
}
else if(pauseplay==0 && pauseplayrelease==1){
	 pauseplayrelease=pauseplay;		

	 }
 }

 
 void Rewind(void){
	uint32_t rewind, rewindrelease=0;
  rewind= RewindSwitch();
  if(rewind==16 && rewindrelease==0){ 
			 NVIC_ST_RELOAD_R=songlist[currentsong].lead[0].notereload;
			NVIC_ST_CURRENT_R=0;
	TIMER2_TAILR_R=songlist[currentsong].bass[0].notereload;
	TIMER2_TAR_R=0;
	
  rewindrelease=rewind;

 }
	if(rewind==0 && rewindrelease==16){
		  rewindrelease=rewind;
	}
}
 uint32_t nosoundbass=0;
 void Timer2A_Handler(void){
	  TIMER2_ICR_R = TIMER_ICR_TATOCINT;  // acknowledge timeout
  if(currentnotelead!=previousnote){
	if(songlist[currentsong].bass[currentnotebass].notereload==0){
		nosoundbass=1;
//		NVIC_ST_RELOAD_R=10;
//	NVIC_ST_CURRENT_R=0;
	previousnote=currentnotebass;
	
	}
	else{
	    nosoundbass = 0;
	TIMER2_TAILR_R=songlist[currentsong].bass[currentnotebass].notereload;
	TIMER2_TAR_R=0;
	previousnote=currentnotebass;
	}
	}
 playbassnote(); //Plays actual note

}


void playbassnote(void){
	if(nosoundbass==1){
		DAC_Out(Wave[leadindex]+Wave[bassindex]);
	}
	else{
  DAC_Out(Wave[leadindex]+Wave[bassindex]);
	bassindex++;
  if(bassindex>=64){
  bassindex=0;

	}		
}
	
}
