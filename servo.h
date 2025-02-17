enum DetectorState{ACTIVE, INACTIVE};
enum ServoState{CALLIB, IDLE, IN_PROGRES, OFFSET};


struct Servo
{
	enum ServoState eState;
	unsigned int uiCurrentPosition;
	unsigned int uiDesiredPosition;
	//unsigned int uiOffset;
	
}; 

//void DetectorInit(void);
//enum DetectorState eReadDetector(void);
void Automat_2(void);
void ServoInit(unsigned int uiServoFrequency);
void ServoCallib(void);
void ServoGoTo(unsigned int uiPosition);
