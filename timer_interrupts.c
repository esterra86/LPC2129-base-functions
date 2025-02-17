#include <LPC21xx.H>
#include "timer_interrupts.h"

// TIMER
#define mCOUNTER_ENABLE 0x00000001
#define mCOUNTER_RESET  0x00000002

// CompareMatch
#define mINTERRUPT_ON_MR0 0x00000001
#define mRESET_ON_MR0     0x00000002
#define mMR0_INTERRUPT    0x00000001

// VIC (Vector Interrupt Controller) VICIntEnable
#define VIC_TIMER0_CHANNEL_NR 4

// VICVectCntlx Vector Control Registers
#define mIRQ_SLOT_ENABLE 0x00000020


//Pointer to function
void (*ptrTimer0InterruptFunction)();


//(Interrupt Service Routine) of Timer 0 interrupt
__irq void Timer0IRQHandler(){

	T0IR=mMR0_INTERRUPT; 	
	ptrTimer0InterruptFunction();		
	VICVectAddr=0x00; 
}

void Timer0Interrupts_Init(unsigned int uiPeriod,void (*ptrInterruptFunction)()){ 

        // interrupts

	VICIntEnable |= (0x1 << VIC_TIMER0_CHANNEL_NR);           
	VICVectCntl1  = mIRQ_SLOT_ENABLE | VIC_TIMER0_CHANNEL_NR;  // Enable Slot 0 and assign it to Timer 0 interrupt channel
	VICVectAddr1  =(unsigned long)Timer0IRQHandler; 	   // Set to Slot 0 Address of Interrupt Service Routine 
	ptrTimer0InterruptFunction = ptrInterruptFunction;

        // match module

	T0MR0 = 15 * uiPeriod;                 	      
	T0MCR |= (mINTERRUPT_ON_MR0 | mRESET_ON_MR0);

        // timer

	T0TCR |=  mCOUNTER_ENABLE; // start 

}
