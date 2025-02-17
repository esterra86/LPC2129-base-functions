#define MAX_TOKEN_NR 3
#define MAX_KEYWORD_NR 2

typedef enum TokenType {KEYWORD, NUMBER, STRING} TokenType;
typedef enum KeywordCode{NONE,SERVO_CALLIB, SERVO_GOTO} KeywordCode;



typedef union TokenValue{
	KeywordCode eKeyword; 
	unsigned int uiNumber;	
	char *	pcString;	
} TokenValue;


typedef struct Token{
	TokenType eType;	//typ tokenu
	TokenValue uValue; //wartosc tokenu
} Token;

typedef struct Keyword Keyword;

extern Token asToken[MAX_TOKEN_NR]; 


unsigned char ucFindTokensInString (char *pcString);
enum Result eStringToKeyword(char pcStr[], KeywordCode *peKeywordCode);
void DecodeTokens(void);
void DecodeMsg(char *pcString);
