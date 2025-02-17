#include <LPC21xx.H>

#define COUNTER_ENABLE 0x1
#define COUNTER_RESET 0x2
#define PCLK_FREQ  15000000
#define RESET_ON_MR0 1<<1
#define INTERRUPT_ON_MR0 1<<0
#define MR0_INTERRUPT    1<<0

void InitTimer0(void){
	T0TCR = COUNTER_ENABLE; //counter enbale
}

void WaitOnTimer0_PR(unsigned int uiTime){
	
	T0TCR |=COUNTER_RESET;
	T0PR = 14; 
	T0TCR &= ~COUNTER_RESET; 
	//uiTime *=(PCLK_FREQ/1000000);
	
	while(T0TC <= uiTime){
	}		
}

void WaitOnTimer0(unsigned int uiTime){
	
	T0TCR |=COUNTER_RESET; 
	uiTime *=(PCLK_FREQ/1000000);
	T0TCR &= ~COUNTER_RESET; 
	
	while(T0TC <= uiTime){
	}		
}

void InitTimer0Match0(unsigned int uiDelayTime){
	T0TCR = COUNTER_ENABLE|COUNTER_RESET;
	T0MR0= uiDelayTime*15;
	T0TCR &= ~COUNTER_RESET; 
	
}

void WaitOnTimer0Match0(){
	T0MCR = INTERRUPT_ON_MR0|RESET_ON_MR0; //USTAWEINIE FLAGI PRZERWANIA
	while(T0IR != MR0_INTERRUPT){;}
	T0IR = MR0_INTERRUPT; //WZYZEROWANIE FLAGI PRZERWANIA

}
