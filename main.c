#include "led.h"
#include "keyboard.h"


void Delay(int a){ 
	int iCount;
	int time = a*11996;
	for(iCount =0 ; iCount<time; iCount++){
	};
}


int main(){	
	enum MovementState{STOP, LEFT, RIGHT, WIPER};
	enum MovementState eMovementState = RIGHT;
	unsigned char ucCounter;

	LedInit();
	while(1){
		switch(eMovementState){

			case STOP:
				if(eKeyboardRead() == BUTTON_0){
					eMovementState=LEFT;
				}
				else if(eKeyboardRead() == BUTTON_2){
					eMovementState=RIGHT;
				}
				else{
					eMovementState=STOP;
				}
				break;
			
			case RIGHT:
				if(eKeyboardRead() == BUTTON_1){
					eMovementState=STOP;
				}
				else if(eKeyboardRead()==BUTTON_3){
					eMovementState = WIPER;
					}
				else{
					LedStepRight();
					eMovementState=RIGHT;
				}
				break;
				
			case LEFT:
				if(eKeyboardRead() == BUTTON_1){
					eMovementState=STOP;
				}
				else{
					LedStepLeft();
					eMovementState=LEFT;
				}
				break;
				
			case WIPER:
				if(ucCounter == 6){
						eMovementState = LEFT;
						ucCounter =0;
				}
				else{
						LedOn(ucCounter%2);
						ucCounter++;
				}
				break;
			}
		Delay(100);
	}
}

