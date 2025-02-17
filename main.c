#include "timer_interrupts.h"
#include "led.h"
#include "keyboard.h"

enum MovementState{STOP, MOVE_LEFT, MOVE_RIGHT};
enum MovementState eMovementState = MOVE_RIGHT;

void Automat(void){

	switch(eMovementState){

		case STOP:
			if(eKeyboardRead() == BUTTON_0){
				eMovementState=MOVE_LEFT;
			}
			else if(eKeyboardRead() == BUTTON_2){
				eMovementState=MOVE_RIGHT;
			}
			else{
				eMovementState=STOP;
			}
			break;
			
		case MOVE_RIGHT:
			if(eKeyboardRead() == BUTTON_1){
				eMovementState=STOP;
			}
			else{
				LedStepRight();
				eMovementState=MOVE_RIGHT;
			}
			break;
				
		case MOVE_LEFT:
			if(eKeyboardRead() == BUTTON_1){
				eMovementState=STOP;
			}
			else{
				LedStepLeft();
				eMovementState=MOVE_LEFT;
			}
	}
}

int main (){
	unsigned int iMainLoopCtr;
	LedInit();
	Timer0Interrupts_Init(20000, &Automat);

	while(1){
		iMainLoopCtr++;
	}
}
