#define RECEIVE_SIZE 12

__irq void UART0_Interrupt (void);
void UART_InitWithInt(unsigned int uiBaudRate);
extern char cOdebranyZnak;
extern char BufferCopy[RECEIVE_SIZE];
//do odbironika
//#define RECEIVE_SIZE 5
enum eReceiverStatus {EMPTY, READY, OVERFLOW};
struct ReceiverBuffer;

void Receiver_PutCharacterToBuffer(char cCharacter); //-wstawianie znakow do bufora odbiornika
enum eReceiverStatus eReceiver_GetStatus(void);//- odczyt stanu bufora
//-EMPTY- nie odebrano jeszcze caleo lancucha
//-READY- odebrano kompletny lancuch znakowy
//-OVERFLOW- odebrano weicej znakow niz zmiesci sie w buforze
void Receiver_GetStringCopy(char *ucDestination);//-odczyt stringa z buforu
