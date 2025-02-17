#include "servo.h"
//#include "keyboard.h"
#include "uart.h"
#include "command_decoder.h"

#define TERMINATOR 0xD


int main (){ 
	UART_InitWithInt(9600);
	ServoInit(50);
	while(1){
		if(eReceiver_GetStatus()==READY){
			Receiver_GetStringCopy(BufferCopy);
			DecodeMsg(BufferCopy);
		}
		
		switch(asToken[0].uValue.eKeyword){
			case SERVO_CALLIB:
				ServoCallib();
				break;
			case SERVO_GOTO:
				ServoGoTo(asToken[1].uValue.uiNumber);
				break;
			default:;
		}
	}	
}
