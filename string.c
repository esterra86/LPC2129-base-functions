#include "string.h"
#define NULL 0

enum CompResult eCompareString(char pcStr1[], char pcStr2[]){
	unsigned int uiLicznik;
	for(uiLicznik =0;pcStr1[uiLicznik]== pcStr2[uiLicznik];uiLicznik++){
		if(pcStr1[uiLicznik] == NULL){
			return  EQUAL;
			}
	}
	return DIFFRENT;
}
enum Result eHexStringToUInt(char pcStr[],unsigned int *puiValue){
	
	unsigned char ucCharCounter;
	unsigned char ucChar;
	unsigned char ucCurrentValue;
	
	*puiValue =0;
	
	if((pcStr[0]!='0' || pcStr[1]!='x')||pcStr[2]==NULL){
		return ERROR;
	}
	
	for(ucCharCounter=0;(ucCharCounter<=4);ucCharCounter++){
		ucChar = pcStr[2+ucCharCounter];
		
		if((ucCharCounter==4)&&(ucChar!=NULL)){
			return ERROR;
		}
		else if(('A'<=ucChar)&&(ucChar<='F')){
			ucCurrentValue = 0x40^ucChar + 9;
		}
		else if(('1'<=ucChar)&&(ucChar<='9')){
			ucCurrentValue = 0x30^ucChar;
		}
		else if(ucChar == NULL){
			break;
		}
		else{
			return ERROR;
		}
		*puiValue = (*puiValue<<4)+ucCurrentValue;
	}
	return OK;
}

void ReplaceCharactersInString(char pcString[], char cOldChar, char cNewChar){
	unsigned int uiLicznik;
	for(uiLicznik=0;pcString[uiLicznik]!= NULL;uiLicznik++){
		if(pcString[uiLicznik]==cOldChar){
			pcString[uiLicznik] = cNewChar;
		}
	}
}
