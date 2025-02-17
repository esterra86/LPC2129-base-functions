#include <LPC210X.H>
#include "uart.h"
/************ UART ************/
//PIN CONNECT BLOCK
#define P01_RX_UART0 0x4

// U0LCR Line Control Register
#define mDIVISOR_LATCH_ACCES_BIT                   0x00000080
#define m8BIT_UART_WORD_LENGTH                     0x00000003

// UxIER Interrupt Enable Register
#define mRX_DATA_AVALIABLE_INTERRUPT_ENABLE        0x00000001
#define mTHRE_INTERRUPT_ENABLE                     0x00000002

// UxIIR Pending Interrupt Identification Register
#define mINTERRUPT_PENDING_IDETIFICATION_BITFIELD  0x0000000F
#define mTHRE_INTERRUPT_PENDING                    0x00000002
#define mRX_DATA_AVALIABLE_INTERRUPT_PENDING       0x00000004

/************ Interrupts **********/
// VIC (Vector Interrupt Controller) channels
#define VIC_UART0_CHANNEL_NR  6
#define VIC_UART1_CHANNEL_NR  7

// VICVectCntlx Vector Control Registers
#define mIRQ_SLOT_ENABLE                           0x00000020

//odbiornik i dekodowanie
#define RECEIVE_SIZE 12
#define TERMINATOR 0xD
#define NULL 0

struct ReceiverBuffer{
	char cData[RECEIVE_SIZE]; // - przehcowywanie odbieranego Bancucha zankowego
	unsigned char ucCharCtr;	//- do iteracji po lancuhu znakowym
	enum eReceiverStatus eStatus; //status bufora
};

//Zmienne globalne 
char cOdebranyZnak;
struct ReceiverBuffer ReceiverBuffer;
char BufferCopy[RECEIVE_SIZE];

__irq void UART0_Interrupt (void) {
  
   
   unsigned int uiCopyOfU0IIR=U0IIR;

   if      ((uiCopyOfU0IIR & mINTERRUPT_PENDING_IDETIFICATION_BITFIELD) == mRX_DATA_AVALIABLE_INTERRUPT_PENDING)
   {
      cOdebranyZnak = U0RBR;
		 Receiver_PutCharacterToBuffer(cOdebranyZnak);
		 
   } 
   
   if ((uiCopyOfU0IIR & mINTERRUPT_PENDING_IDETIFICATION_BITFIELD) == mTHRE_INTERRUPT_PENDING)
   {
      // narazie nic nie wysylamy
   }
	
   VICVectAddr = 0; 
}


void UART_InitWithInt(unsigned int uiBaudRate){

   // UART0
   PINSEL0 = PINSEL0 | P01_RX_UART0;                                     // ustawic pina na odbiornik uart0
   U0LCR  |= m8BIT_UART_WORD_LENGTH | mDIVISOR_LATCH_ACCES_BIT; // dlugosc slowa, DLAB = 1
   U0DLL   = ((15000000)/(16*uiBaudRate));                      // predkosc transmisji
   U0LCR  &= (~mDIVISOR_LATCH_ACCES_BIT);                       // DLAB = 0
   U0IER  |= mRX_DATA_AVALIABLE_INTERRUPT_ENABLE;               // ??? co tu robinmy

   // INT
   VICVectAddr2  = (unsigned long) UART0_Interrupt;             // set interrupt service routine address
   VICVectCntl2  = mIRQ_SLOT_ENABLE | VIC_UART0_CHANNEL_NR;     // use it for UART 0 Interrupt
   VICIntEnable |= (0x1 << VIC_UART0_CHANNEL_NR);               // Enable UART 0 Interrupt Channel
	 
}

void Receiver_PutCharacterToBuffer(char cCharacter){
	
	if ((cCharacter==TERMINATOR)&&(ReceiverBuffer.eStatus!=OVERFLOW)){
		ReceiverBuffer.cData[ReceiverBuffer.ucCharCtr]= NULL;
		ReceiverBuffer.eStatus=READY;
		ReceiverBuffer.ucCharCtr=0;
	}
	else if((ReceiverBuffer.ucCharCtr+1)>=RECEIVE_SIZE){
		ReceiverBuffer.eStatus=OVERFLOW;
	}
	else{
		ReceiverBuffer.cData[ReceiverBuffer.ucCharCtr]=cCharacter;
		ReceiverBuffer.ucCharCtr++;
	}
}

enum eReceiverStatus eReceiver_GetStatus(void){
	return ReceiverBuffer.eStatus;
}

void Receiver_GetStringCopy(char *ucDestination){
	for(ReceiverBuffer.ucCharCtr=0;ReceiverBuffer.cData[ReceiverBuffer.ucCharCtr]!=NULL;ReceiverBuffer.ucCharCtr++){
		ucDestination[ReceiverBuffer.ucCharCtr]=ReceiverBuffer.cData[ReceiverBuffer.ucCharCtr];
	}
	ucDestination[ReceiverBuffer.ucCharCtr]=NULL;
	ReceiverBuffer.ucCharCtr=0;
	ReceiverBuffer.eStatus=EMPTY;
}
