#include <LPC21xx.H>


#define LED0_bm 0x10000 				
#define LED1_bm 0x20000					
#define LED2_bm 0x40000
#define LED3_bm 0x80000					


#define S0_bm 0x10
#define S1_bm 0x40
#define S2_bm 0x20
#define S3_bm 0x80

enum KeyboardState {BUTTON_0, BUTTON_1, BUTTON_2, BUTTON_3,RELEASED};
enum Direction {LEFT, RIGHT};

void Delay(int a){ //
	int iCount;
	int time = a*11996;
	for(iCount =0 ; iCount<time; iCount++){
	};
}

int freq(int a){
float time_cycle_in_milis = 1000/a;
return time_cycle_in_milis; }

void move(int a){					
	int i;
	for(i=0; i<=a;i++){
		IO1SET = LED0_bm<<i;	
		Delay(freq(100));
		IO1CLR = LED0_bm<<i;
		};
}

void LedInit(void){	//
	IO1DIR |= LED0_bm|LED1_bm|LED2_bm|LED3_bm;   
	IO1SET =LED0_bm;
}

void KeyboardInit(void){//
	IO0DIR &= ~(S0_bm|S1_bm|S2_bm|S3_bm);
	}

void LedOn(unsigned char ucLedIndeks){//

	IO1CLR=LED0_bm|LED1_bm|LED2_bm|LED3_bm; 
  switch(ucLedIndeks){
	 case 0:
		 IO1SET = LED0_bm;
		 break;
	 case 1:
		 IO1SET = LED1_bm;
		 break;
	 case 2:
		 IO1SET = LED2_bm;
		 break;
	 case 3:
		 IO1SET = LED3_bm;
		 break;
		case 4:
		 break;}
} 

enum KeyboardState eKeyboardRead(void){//
																
	if((IO0PIN&S0_bm)== 0){									 		
		return BUTTON_0;}
	else if((IO0PIN&S1_bm)==0){ 								
		return BUTTON_1;}
	else if((IO0PIN&S2_bm) == 0){								
		return BUTTON_2;}
	else if((IO0PIN&S3_bm) ==0){							
		return BUTTON_3;}
	else {
		return RELEASED;}}


		
//23
void LedStep(enum Direction eDirection){//
	static unsigned int uiLed;
	switch(eDirection){
		case LEFT:
			uiLed +=1;
			break;
		case RIGHT:
			uiLed -=1;
			break;
	}
	LedOn(uiLed%4);
}

//25
void LedStepLeft(void){//
	LedStep(LEFT);
}

void LedStepRight(void){//
	LedStep(RIGHT);
}

int main(){
	LedInit();
	KeyboardInit();
	while(1){
		Delay(50);
		switch(eKeyboardRead()){
			case BUTTON_1:
				LedStepRight();
				break;
			case BUTTON_2:
				LedStepLeft();
			  break;
			default:;
		}
	}
}

