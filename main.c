//#include "keyboard.h"
#include "timer.h"
#include "led.h"

#include <LPC21xx.H>

#define COUNTER_ENABLE 0x1
#define COUNTER_RESET 0x2
#define PCLK_FREQ  15000000
#define RESET_ON_MR0 1<<1
#define INTERRUPT_ON_MR0 1<<0
#define MR0_INTERRUPT    1<<0
#define STOP_ON_MR0 1<<2


int uiDelayTime =100;
int a;



int main(){
	LedInit();
	InitTimer0Match0(10000000);
	while(1){
		WaitOnTimer0Match0();
		LedStepRight();
	}
}
