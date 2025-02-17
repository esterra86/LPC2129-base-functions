#include <LPC21xx.H>
#include "servo.h"
#include "timer_interrupts.h"
#include "led.h"


#define DETEKTOR_OUTPUT (1<<10)

struct Servo sServo;


void DetectorInit(void){
	IO0DIR &= ~DETEKTOR_OUTPUT;}

enum DetectorState eReadDetector(void){
	if((~IO0PIN) & DETEKTOR_OUTPUT){
		return ACTIVE;}
	else{
		return INACTIVE;
	}
}

void Automat_2(void){
	switch(sServo.eState){
		case CALLIB:
			if(eReadDetector() == ACTIVE){
				sServo.uiCurrentPosition=0;
				sServo.uiDesiredPosition=0;
				sServo.eState = IDLE;
			}
			else if(eReadDetector() == INACTIVE){
				LedStepLeft();
				sServo.eState= CALLIB;
			}
			break;
			
		case OFFSET:
			if(sServo.uiCurrentPosition==12){
				sServo.uiCurrentPosition=0;
				sServo.eState=IDLE;
			}
			else{
				LedStepRight();
				sServo.uiCurrentPosition++;
				sServo.eState=OFFSET;
			}
			break;
			
		case IDLE:
			if(sServo.uiCurrentPosition != sServo.uiDesiredPosition){
				sServo.eState = IN_PROGRES;
			}
			else{
				sServo.eState = IDLE;
			}
			break;
			
		case IN_PROGRES:
			if(sServo.uiCurrentPosition<sServo.uiDesiredPosition){
				LedStepRight();
				sServo.uiCurrentPosition = (sServo.uiCurrentPosition+1)%48 ;
				sServo.eState=IN_PROGRES;
			}
			else if(sServo.uiCurrentPosition>sServo.uiDesiredPosition){
				LedStepLeft();
				sServo.uiCurrentPosition = (sServo.uiCurrentPosition-1)%48 ;
				sServo.eState=IN_PROGRES;
			}
			else{
				sServo.eState=IDLE;
			}
			break;
			
	}
}

void ServoInit(unsigned int uiServoFrequency){
	sServo.eState =CALLIB;
	LedInit();
	Timer0Interrupts_Init(1000000*1/uiServoFrequency, &Automat_2);
	while(sServo.eState == CALLIB){};
	}

void ServoCallib(void){
	sServo.eState = CALLIB;
}

void ServoGoTo(unsigned int uiPosition){
	
	sServo.uiDesiredPosition = uiPosition;
	sServo.eState=IN_PROGRES;
	while(sServo.eState == IN_PROGRES){};
}
