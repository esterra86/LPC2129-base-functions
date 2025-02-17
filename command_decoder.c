#include "command_decoder.h"
#include "string.h"

#define MAX_KEYWORD_STRING_LTH	10
#define MAX_TOKEN_NR 3
#define MAX_KEYWORD_NR 2
#define NULL 0

typedef struct Keyword
{
	enum KeywordCode eCode;
	char cString[MAX_KEYWORD_STRING_LTH + 1];
} Keyword;

Keyword asKeywordList[MAX_KEYWORD_NR] =
{
	{SERVO_CALLIB,"callib"},	
	{SERVO_GOTO,"goto"},
};

unsigned char ucTokenNr; 
Token asToken[MAX_TOKEN_NR]; 

unsigned char ucFindTokensInString (char *pcString){
	
	enum CharState{TOKEN, DELIMETER};
	enum CharState eCharState = DELIMETER;
	
	unsigned char ucCharCounter;
	unsigned char ucCurrentChar;
	ucTokenNr = 0;
	
	for(ucCharCounter=0;;ucCharCounter++){
		
		ucCurrentChar=pcString[ucCharCounter];
		
		switch(eCharState){
			
			case DELIMETER:
				if(ucCurrentChar== ' '){
					eCharState=DELIMETER;
				}
				else if(ucCurrentChar==NULL){
					return ucTokenNr;
				}
				else{
					asToken[ucTokenNr].uValue.pcString = pcString + ucCharCounter;
					eCharState=TOKEN;
					ucTokenNr++;
				}
				break;
			
			case TOKEN:
				if(ucTokenNr == MAX_KEYWORD_NR){
					return ucTokenNr;
				}
				else if(ucCurrentChar == NULL){
					return ucTokenNr;
				}
				else if(ucCurrentChar== ' '){
					eCharState=DELIMETER;
				}
				else{
					eCharState=TOKEN;
				}		
				break;
		}
	}
}	


enum Result eStringToKeyword(char pcStr[], KeywordCode *peKeywordCode){	// *peKeywordCode wskazuje na wartosc w struct Token na member uValue(union TokenValue->KeywordCode)
	
	unsigned char ucKeywordCounter;
	
	for(ucKeywordCounter=0; ucKeywordCounter<MAX_KEYWORD_NR; ucKeywordCounter++){
			
		if(EQUAL == eCompareString(pcStr, asKeywordList[ucKeywordCounter].cString)){
			*peKeywordCode= asKeywordList[ucKeywordCounter].eCode;
			return OK;
		}
	}
	return ERROR;
}



void DecodeTokens(void){
		
	unsigned char ucTokenCounter;
	Token *psCurrentToken;
	
	unsigned int uiTokenValue;
	KeywordCode eTokenCode;
		
	for(ucTokenCounter=0; ucTokenCounter < ucTokenNr; ucTokenCounter++){
		psCurrentToken = &asToken[ucTokenCounter];
		
		if(eStringToKeyword(psCurrentToken->uValue.pcString, &eTokenCode)== OK){
			psCurrentToken->eType=KEYWORD;
			psCurrentToken->uValue.eKeyword=eTokenCode;
		}
		else if(eHexStringToUInt(psCurrentToken->uValue.pcString, &uiTokenValue) == OK){
			psCurrentToken->eType=NUMBER;
			psCurrentToken->uValue.uiNumber=uiTokenValue;
		}
		else{
			psCurrentToken->eType=STRING;
		}
	}
}
void DecodeMsg(char *pcString){
	ucFindTokensInString(pcString);
	ReplaceCharactersInString(pcString,' ', NULL);
	DecodeTokens();
}


