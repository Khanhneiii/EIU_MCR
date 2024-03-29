#include <util/delay.h>
#include	"../LED/led.h"
#include	"../INPUT/input.h"
#include	"../HANDLE/handle.h"
#include	"../TIMER/timer.h"
#include	"../ADC/adc.h"
#include	"../SPEED/speed.h"
#include	"../BEEP/beep.h"
#include	"../ENCODER/encoder.h"
#include	"../TEST/test.h"
#include	"run.h"

/************************************************************************/
/* Main program                                                         */
/************************************************************************/
signed char sensorPos, straightLine;// bien vi tri line v� bien duong thang
unsigned int RunTimer;// thoi gian chay toi da cua xe
signed int line;
//////////////////////////////////////////////////////// forward line
int speedRunForward;// t?c ?? ch?y c?a xe
int speedRun0; int angle0;// t?c ?? d?a theo g�c b? l�i
int speedRun1; int angle1;
int speedRun2; int angle2;
int speedRun3; int angle3;
int speedRun4; int angle4;
int speedRun5; int angle5;
int speedRun6; int angle6;
int speedRun7; int angle7;
int speedRun8; int angle8;

//////////////////////////////////////////////////////// turn90
signed int speedBrake90;
unsigned int timerBrake90;
signed int speed90;
signed int speedBoostAfter90;
unsigned int timerBoostAfter90;

//////////////////////////////////////////////////////// change lanes
int angleChangeLanes;
int angleTurn90;
signed int speedBrakeChangeLanes;
unsigned int timerBrakeChangeLanes;
signed int speedChangeLanes;
signed int speedTurn90 ;
signed int speedSmall90;
signed int speedBig90;
signed int speedBoostAfterChangeLanes;
unsigned int timerBoostAfterChangeLanes;
signed int speedRunForwardBeforeChangeLine;
signed int speedRunForwardBeforeTurn90;

/////////////////////////////////////Differential
const char coeffR1[50] ={
	100,	99,		98,		97,		96,		95,		94,		93,		92,		91,
	90,		89,		89,		88,		87,		86,		85,		84,		83,		82,
	81,		80,		79,		78,		77,		75,		74,		73,		72,		71,
	70,		68,		67,		66,		65,		63,		62,		61,		59,		58,
	56,		55,		53,		51,		50,		48,		46,		44,		42,		40
};
const char coeffR3[50] ={
	100,	101,	102,	103,	104,	105,	106,	107,	108,	109,
	110,	111,	111,	112,	113,	114,	115,	116,	117,	118,
	119,	120,	121,	122,	123,	125,	126,	127,	128,	129,
	130,	132,	133,	134,	135,	137,	138,	139,	141,	142,
	144,	145,	147,	149,	150,	152,	154,	156,	158,	160
};


void setup()
{
	handle( 0 );
	speed( 0, 0 );
	cnt1 = 0;
	cnt4 = 0;
	RunTimer = 30000;
	sensorPos = 0;
	straightLine = 1;
	switch (get_dipsw())
	{
		case 7: // 25 %
		//////////////////////////////////////////////////////// turn90
		speedBrake90 = 0;
		timerBrake90 = 100;
		speed90 = 50;
		speedBoostAfter90 = 100;
		timerBoostAfter90 = 200;
		//////////////////////////////////////////////////////// change lanes
		angleChangeLanes = 10;
		speedBrakeChangeLanes = 0;
		timerBrakeChangeLanes= 120;
		speedChangeLanes = 50;
		speedBoostAfterChangeLanes = 100;
		timerBoostAfterChangeLanes = 200;
		/////////////////////////////////////////////////////Speed run forward line
		speedRunForward = 45;
		break;
		
		case 8: // 30 %
		//////////////////////////////////////////////////////// turn90
		speedBrake90 = 0;
		timerBrake90 = 100;
		speed90 = 50;
		speedBoostAfter90 = 100;
		timerBoostAfter90 = 200;
		//////////////////////////////////////////////////////// change lanes
		angleChangeLanes = 10;
		speedBrakeChangeLanes = 0;
		timerBrakeChangeLanes= 120;
		speedChangeLanes = 50;
		speedBoostAfterChangeLanes = 100;
		timerBoostAfterChangeLanes = 200;
		/////////////////////////////////////////////////////Speed run forward line
		speedRunForward = 50;
		break;
		
		case 9: // 40 %
		//////////////////////////////////////////////////////// turn90
		speedBrake90 = 0;
		timerBrake90 = 100;
		speed90 = 50;
		speedBoostAfter90 = 100;
		timerBoostAfter90 = 200;
		//////////////////////////////////////////////////////// change lanes
		angleChangeLanes = 10;
		speedBrakeChangeLanes = 0;
		timerBrakeChangeLanes= 120;
		speedChangeLanes = 50;
		speedBoostAfterChangeLanes = 100;
		timerBoostAfterChangeLanes = 200;
		/////////////////////////////////////////////////////Speed run forward line
		speedRunForward = 55;
		break;
		
		case 10: // 50 %
		//////////////////////////////////////////////////////// turn90
		speedBrake90 = 0;
		timerBrake90 = 60;
		speed90 = 130;
		speedBoostAfter90 = 200;
		timerBoostAfter90 = 100;
		//////////////////////////////////////////////////////// change lanes
		angleChangeLanes = 18;
		speedBrakeChangeLanes = 0;
		timerBrakeChangeLanes= 30;
		speedChangeLanes = 180;
		speedRunForward = 210;
	//	speedRunForwardBeforeChangeLine = (speedChangeLanes + speedRunForward)/2;
		speedBoostAfterChangeLanes = 200;
		timerBoostAfterChangeLanes = 100;
		break;
		
		case 11: // 60 %
		//////////////////////////////////////////////////////// turn90
		speedBrake90 = 0;
		timerBrake90 = 100;
		speed90 = 50;
		speedBoostAfter90 = 100;
		timerBoostAfter90 = 200;
		//////////////////////////////////////////////////////// change lanes
		angleChangeLanes = 10;
		speedBrakeChangeLanes = 0;
		timerBrakeChangeLanes= 120;
		speedChangeLanes = 50;
		speedBoostAfterChangeLanes = 100;
		timerBoostAfterChangeLanes = 200;
		/////////////////////////////////////////////////////Speed run forward line
		speedRunForward = 65;
		break;
		
		case 12: // 70 %
		//////////////////////////////////////////////////////// turn90
		speedBrake90 = 0;
		timerBrake90 = 100;
		speed90 = 50;
		speedBoostAfter90 = 100;
		timerBoostAfter90 = 200;
		//////////////////////////////////////////////////////// change lanes
		angleChangeLanes = 10;
		speedBrakeChangeLanes = 0;
		timerBrakeChangeLanes= 120;
		speedChangeLanes = 50;
		speedBoostAfterChangeLanes = 100;
		timerBoostAfterChangeLanes = 200;
		/////////////////////////////////////////////////////Speed run forward line
		speedRunForward = 70;
		break;
		
		case 13: // 80 %
		//////////////////////////////////////////////////////// turn90
		speedBrake90 = 0;
		timerBrake90 = 100;
		speed90 = 50;
		speedBoostAfter90 = 100;
		timerBoostAfter90 = 200;
		//////////////////////////////////////////////////////// change lanes
		angleChangeLanes = 10;
		speedBrakeChangeLanes = 0;
		timerBrakeChangeLanes= 120;
		speedChangeLanes = 50;
		speedBoostAfterChangeLanes = 100;
		timerBoostAfterChangeLanes = 200;
		/////////////////////////////////////////////////////Speed run forward line
		speedRunForward = 75;
		break;
		
		case 14: // 90 %
		//////////////////////////////////////////////////////// turn90
		speedBrake90 = 0;
		timerBrake90 = 150;
		speed90 = 100;
		speedBoostAfter90 = 100;
		timerBoostAfter90 = 200;
		//////////////////////////////////////////////////////// change lanes
		angleChangeLanes = 10;
		speedBrakeChangeLanes = 0;
		timerBrakeChangeLanes= 120;
		speedChangeLanes = 50;
		speedBoostAfterChangeLanes = 100;
		timerBoostAfterChangeLanes = 200;
		/////////////////////////////////////////////////////Speed run forward line
		speedRunForward = 80;
		break;
		
		case 15: // 100%
		//////////////////////////////////////////////////////// turn90
		speedBrake90 = -10;
		timerBrake90 = 60;
		angleTurn90 = 50;
		speedTurn90 = 120;
		speedSmall90 = 30;
		speedBig90 = 180;
		timerBoostAfter90 = 100;
		//////////////////////////////////////////////////////// change lanes
		angleChangeLanes = 22;
		speedBrakeChangeLanes = 30;
		timerBrakeChangeLanes= 50;
		speedChangeLanes = 140;
		speedRunForward = 210;
		speedRunForwardBeforeChangeLine = (speedChangeLanes + speedRunForward)/2;
		speedRunForwardBeforeTurn90 = (speed90 + speedRunForward)/2;
		speedBoostAfterChangeLanes = 220;
		timerBoostAfterChangeLanes = 100;
		break;
		
		default:
		//////////////////////////////////////////////////////// turn90
		speedBrake90 = 0;
		timerBrake90 = 0;
		speed90 = 0;
		speedBoostAfter90 = 0;
		timerBoostAfter90 = 0;
		//////////////////////////////////////////////////////// change lanes
		angleChangeLanes = 0;
		speedBrakeChangeLanes = 0;
		timerBrakeChangeLanes= 0;
		speedChangeLanes = 0;
		speedBoostAfterChangeLanes = 0;
		timerBoostAfterChangeLanes = 0;
		/////////////////////////////////////////////////////Speed run forward line
		speedRunForward = 0;
		break;
	}
	
	//////////////////////////////////////////////////////// forward curved line
	speedRun0 = speedRunForward;			angle0 = 0;		//0  -  0
	speedRun1 = speedRunForward;			angle1 = 1;		//0  -  1
	speedRun2 = speedRunForward*97/100;		angle2 = 3;		//90 -  3
	speedRun3 = speedRunForward*88/100;		angle3 = 5;		//87 -  5
	speedRun4 = speedRunForward*86/100;		angle4 = 8;		//83 -  7
	speedRun5 = speedRunForward*83/100;		angle5 = 10;	//80 -  10
	speedRun6 = speedRunForward*78/100;		angle6 = 13;	//75 -  12
	speedRun7 = speedRunForward*75/100;		angle7 = 17;	//70 -  15
}
void run(void)
{
	setup();
	unsigned char runCase = 0;
	while( 1 ) {
		switch( runCase ) {
			case 0:
			if((getGateSensor() == 1)){
				runCase = 1;
				beep_long(100);
				_delay_ms(500);
				break;
			}
			if (SW4)
			{
				runCase = 1;
				break;
			}
			break;
			case 1:
			if ((getGateSensor() == 0) || SW4)
			{
				runCase = 2;
				cnt1 = 0;
				cnt4 = 0;
				break;
			}
			break;
			case 2:
			if( cnt1 < 1 ) {
				handle(0);
				speed(0,0);
			}
			else {
				beep_long(100);
				runCase = 11;
				cnt1 = 0;
				cnt4 = 0;
			}
			break;
			case 11:
			/* time run = cnt4 */
			/*if(cnt4 > RunTimer){
				runCase = 100;
				cnt1 = 0;
				break;
			}*/
			if(checkCrossLine()) {      
				runCase = 21;
				cnt1 = 0;
				break;
			}
			else {					
				switch (checkCrossHalfLine())
				{
					case HALF_LEFT_LINE:
					cnt1 = 0;
					runCase = 12;
					break;
					
					case HALF_RIGHT_LINE:
					cnt1 = 0;
					runCase = 13;
					break;
					
					default :
					break;
				}
			}
			runForwardLine(speedRunForward);
			break;
			case 12:
			/* Check of large turning to the right completion */
			if( checkCrossLine()) {   /* Cross line check even during turning */
				runCase = 21;
				cnt1 = 0;
				break;
			}
			runCase = leftLaneChange(speedChangeLanes);
			cnt1 = 0;
			straightLine = 0;
			break;
			case 13:
			/* Check of large turning completion to the left */
			if( checkCrossLine() ) {   /* Cross line check even during large turn */
				runCase = 21;
				cnt1 = 0;
				break;
			}
			runCase = rightLaneChange(speedChangeLanes);
			cnt1 = 0;
			straightLine = 0;
			break;

			case 21:
			/* Process when first Cross line is detected */
			beep_long(100);
			runCase = turn90(speedTurn90);
			cnt1 = 0;
			straightLine = 0;
			break;
			
			case 100:
			if (cnt1<500)
			{
				speed(0,0);
			}
			else
			{
				speed(0,0);
				handle(0);
			}
			break;
			default:
			runCase = 11;
			cnt1 = 0;
			
			break;
		}
	}
}

char checkCrossLine()
{
	if(sensorMask(0xc3) == 0xc3) return 1;//11000011
	else return 0;
}
char checkCrossHalfLine()
{
	if (checkCrossLine() == 0){
		if (sensorMask(0xf0)==0xf0)//11110000
		return HALF_LEFT_LINE;
		else if (sensorMask(0x0f)==0x0f)//00001111
		return HALF_RIGHT_LINE;
		else
		return 0;
	}
	else return 0;
}
void brakeTheCar(int time,int speedRun)
{
	cnt2 = 0;
	while (cnt2<time)
	{
		runForwardLine90(speedRun);
	}
}
unsigned char sensorMask (unsigned char MASK)
{
	return ( sensor & MASK);
}
void handleAndSpeed (int angle,int speed1)
{
	int speed2;
	int speed3;
	handle (angle);
	if (angle<0){
		angle = -angle;
		speed2 = speed1*coeffR1[angle]/100;
		speed3 = speed1*coeffR3[angle]/100;
		speed (speed2,speed3);
	}
	else if (angle == 0 )
	{
		speed (speed1,speed1);
	}
	else {
		speed2 = speed1*coeffR1[angle]/100;
		speed3 = speed1*coeffR3[angle]/100;
		speed (speed3,speed2);
	}
}
void runForwardLine (int speedRun)
{
	switch(sensor) {
		case 0x18:// 00011000
		case 0x3c:// 00111100
		handleAndSpeed(angle0,speedRun0);
		curveFlag = 0;
		sensorPos = 0;
		straightLine = 1;
		break;
		case 0x1C:// 00011100
		case 0x08:// 00001000
		if ( sensorPos < -3)
		{
			handleAndSpeed (-30,0);
			break;
		}
		else
		handleAndSpeed(angle1,speedRun1);
		curveFlag = 0;
		sensorPos = 1;
		straightLine = 1;
		break;
		case 0x0c:// 00001100
		case 0x1e:// 00011110
		if ( sensorPos < -3)
		{
			handleAndSpeed(-30,0);
			break;
		}
		else
		handleAndSpeed(angle2,speedRun2);
		curveFlag = 0;
		sensorPos = 2;
		straightLine = 1;
		break;
		case 0x04:// 00000100
		case 0x0e:// 00001110
		if ( sensorPos < -3)
		{
			handleAndSpeed(-30,0);
			break;
		}
		else if (brakeCurve > 11)
		{
			handle(7);
			speed(-20,-20);
		}
		else
		handleAndSpeed(angle3,speedRun3);
		curveFlag = 1;
		sensorPos = 3;
		straightLine = 0;
		break;
		case 0x06:// 00000110
		if ( sensorPos < -3)
		{
			handleAndSpeed(-30,0);
			break;
		}
		else if (brakeCurve > 11)
		{
			handle(15);
			speed(-20,-20);
		}
		else
		handleAndSpeed(angle4,speedRun4);
		curveFlag = 1;
		sensorPos = 4;
		straightLine = 0;
		break;
		case 0x02:// 00000010
		case 0x07:// 00000111
		if ( sensorPos < -3)
		{
			handleAndSpeed(-30,0);
			break;
		}
		else if (brakeCurve > 11)
		{
			handle(15);
			speed(-20,-20);
		}
		else
		handleAndSpeed(angle5,speedRun5);
		curveFlag = 1;
		sensorPos = 5;
		straightLine = 0;
		break;
		case 0x03:// 00000011
		if ( sensorPos < -3)
		{
			handleAndSpeed(-30,0);
			break;
		}
		else
		handleAndSpeed(angle6,speedRun6);
		curveFlag = 1;
		sensorPos = 6;
		straightLine = 0;
		break;
		case 0x01:// 00000001
		if ( sensorPos < -3)
		{
			handleAndSpeed(-30,0);
			break;
		}
		handleAndSpeed(angle7,speedRun7);
		curveFlag = 1;   //RYGB(0,0,0,0);
		straightLine = 0;
		sensorPos = 6;
		break;
		case 0x81:// 10000001
		case 0xc1:// 11000001
		case 0x00:// 00000000
		case 0x83:// 10000011
		if ( sensorPos < -4)
		{
			handleAndSpeed(-30,0);
			break;
		}
		else if ( sensorPos > 4)
		{
			handleAndSpeed(30,0);
			break;
		}
		break;
		case 0x10:// 00010000
		case 0x38:// 00111000
		if ( sensorPos > 3)
		{
			handleAndSpeed(30,0);
			break;
		}
		else
		handleAndSpeedMicro (-angle1,speedRun1);
		curveFlag = 0;
		sensorPos = -1;
		straightLine = 1;
		break;
		case 0x30:// 00110000
		case 0x78:// 01111000
		if ( sensorPos > 3)
		{
			handleAndSpeed(30,0);
			break;
		}
		else
		handleAndSpeed(-angle2,speedRun2);
		curveFlag = 0;
		sensorPos = -2;
		straightLine = 1;
		break;
		case 0x20:// 00100000
		case 0x70:// 01110000
		if ( sensorPos > 3)
		{
			handleAndSpeed(30,0);
			break;
		}
		else if (brakeCurve > 11)
		{
			handle(-7);
			speed(-20,-20);
		}
		else
		handleAndSpeed(-angle3,speedRun3);
		curveFlag = 1;
		sensorPos = -3;
		straightLine = 0;
		break;
		case 0x60:// 01100000
		if ( sensorPos > 3)
		{
			handleAndSpeed(30,0);
			break;
		}
		else if (brakeCurve > 11)
		{
			handle(-15);
			speed(-20,-20);
		}
		else
		handleAndSpeed(-angle4,speedRun4);
		curveFlag = 1;
		sensorPos = -4;
		straightLine = 0;
		break;
		case 0x40:// 01000000
		case 0xe0:// 11100000
		if ( sensorPos > 3)
		{
			handleAndSpeed(30,0);
			break;
		}
		else if (brakeCurve > 11)
		{
			handle(-15);
			speed(0,0);
		}
		else
		handleAndSpeed(-angle5,speedRun5);
		curveFlag = 1;
		sensorPos = -5;
		straightLine = 0;
		break;
		case 0xc0:// 11000000
		if ( sensorPos > 3)
		{
			handleAndSpeed(30,0);
			break;
		}
		else
		handleAndSpeed(-angle6,speedRun6);
		curveFlag = 1;
		sensorPos = -6;
		straightLine = 0;
		break;
		case 0x80:// 10000000
		if ( sensorPos > 3)
		{
			handleAndSpeed(30,0);
			break;
		}
		else
		handleAndSpeed(-angle7,speedRun7);
		curveFlag = 1;
		sensorPos = -6;
		straightLine = 0;
		break;
		case 0x0f: break;
		case 0xf0: break;
		default:
		straightLine = 1;
		speed(0,0);
		break;
	}
}
void runForwardLine90 (int speedRun90)
{
	switch(sensor) {
		case 0x18:// 00011000
		case 0x3c:// 00111100
		handleAndSpeed(angle0,speedRun90);
		curveFlag = 0;
		sensorPos = 0;
		straightLine = 1;
		break;
		case 0x1C:// 00011100
		case 0x08:// 00001000
		if ( sensorPos < -3)
		{
			handleAndSpeed (-30,0);
			break;
		}
		else
		handleAndSpeed(angle1,speedRun90);
		curveFlag = 0;
		sensorPos = 1;
		straightLine = 1;
		break;
		case 0x0c:// 00001100
		case 0x1e:// 00011110
		if ( sensorPos < -3)
		{
			handleAndSpeed(-30,0);
			break;
		}
		else
		handleAndSpeed(angle2,speedRun90);
		curveFlag = 0;
		sensorPos = 2;
		straightLine = 1;
		break;
		case 0x04:// 00000100
		case 0x0e:// 00001110
		if ( sensorPos < -3)
		{
			handleAndSpeed(-30,0);
			break;
		}
		else if (brakeCurve > 11)
		{
			handle(7);
			speed(-20,-20);
		}
		else
		handleAndSpeed(angle3,speedRun90);
		curveFlag = 1;
		sensorPos = 3;
		straightLine = 0;
		break;
		case 0x06:// 00000110
		if ( sensorPos < -3)
		{
			handleAndSpeed(-30,0);
			break;
		}
		else if (brakeCurve > 11)
		{
			handle(15);
			speed(-20,-20);
		}
		else
		handleAndSpeed(angle4,speedRun90);
		curveFlag = 1;
		sensorPos = 4;
		straightLine = 0;
		break;
		case 0x02:// 00000010
		case 0x07:// 00000111
		if ( sensorPos < -3)
		{
			handleAndSpeed(-30,0);
			break;
		}
		else if (brakeCurve > 11)
		{
			handle(15);
			speed(-20,-20);
		}
		else
		handleAndSpeed(angle5,speedRun90);
		curveFlag = 1;
		sensorPos = 5;
		straightLine = 0;
		break;
		case 0x03:// 00000011
		if ( sensorPos < -3)
		{
			handleAndSpeed(-30,0);
			break;
		}
		else
		handleAndSpeed(angle6,speedRun90);
		curveFlag = 1;
		sensorPos = 6;
		straightLine = 0;
		break;
		case 0x01:// 00000001
		if ( sensorPos < -3)
		{
			handleAndSpeed(-30,0);
			break;
		}
		handleAndSpeed(angle7,speedRun90);
		curveFlag = 1;   //RYGB(0,0,0,0);
		straightLine = 0;
		sensorPos = 6;
		break;
		case 0x81:// 10000001
		case 0xc1:// 11000001
		case 0x00:// 00000000
		case 0x83:// 10000011
		if ( sensorPos < -4)
		{
			handleAndSpeed(-30,0);
			break;
		}
		else if ( sensorPos > 4)
		{
			handleAndSpeed(30,0);
			break;
		}
		break;
		case 0x10:// 00010000
		case 0x38:// 00111000
		if ( sensorPos > 3)
		{
			handleAndSpeed(30,0);
			break;
		}
		else
		handleAndSpeedMicro (-angle1,speedRun90);
		curveFlag = 0;
		sensorPos = -1;
		straightLine = 1;
		break;
		case 0x30:// 00110000
		case 0x78:// 01111000
		if ( sensorPos > 3)
		{
			handleAndSpeed(30,0);
			break;
		}
		else
		handleAndSpeed(-angle2,speedRun90);
		curveFlag = 0;
		sensorPos = -2;
		straightLine = 1;
		break;
		case 0x20:// 00100000
		case 0x70:// 01110000
		if ( sensorPos > 3)
		{
			handleAndSpeed(30,0);
			break;
		}
		else if (brakeCurve > 11)
		{
			handle(-7);
			speed(-20,-20);
		}
		else
		handleAndSpeed(-angle3,speedRun90);
		curveFlag = 1;
		sensorPos = -3;
		straightLine = 0;
		break;
		case 0x60:// 01100000
		if ( sensorPos > 3)
		{
			handleAndSpeed(30,0);
			break;
		}
		else if (brakeCurve > 11)
		{
			handle(-15);
			speed(-20,-20);
		}
		else
		handleAndSpeed(-angle4,speedRun90);
		curveFlag = 1;
		sensorPos = -4;
		straightLine = 0;
		break;
		case 0x40:// 01000000
		case 0xe0:// 11100000
		if ( sensorPos > 3)
		{
			handleAndSpeed(30,0);
			break;
		}
		else if (brakeCurve > 11)
		{
			handle(-15);
			speed(0,0);
		}
		else
		handleAndSpeed(-angle5,speedRun90);
		curveFlag = 1;
		sensorPos = -5;
		straightLine = 0;
		break;
		case 0xc0:// 11000000
		if ( sensorPos > 3)
		{
			handleAndSpeed(30,0);
			break;
		}
		else
		handleAndSpeed(-angle6,speedRun90);
		curveFlag = 1;
		sensorPos = -6;
		straightLine = 0;
		break;
		case 0x80:// 10000000
		if ( sensorPos > 3)
		{
			handleAndSpeed(30,0);
			break;
		}
		else
		handleAndSpeed(-angle7,speedRun90);
		curveFlag = 1;
		sensorPos = -6;
		straightLine = 0;
		break;
		case 0x0f: break;
		case 0xf0: break;
		default:
		straightLine = 1;
		speed(0,0);
		break;
	}
}

int turn90(int speedRun)
{
	int runCase2 = 19;
	cnt1 = 0;
	cnt2 = 0;
	RGB(1,0,1);
	int LineCheck = 0;
	while (1){
		switch (runCase2)
		{
			case 19:
			brakeTheCar(timerBrake90,speedBrake90);
			runForwardLine90(speedRun); // speedRun ---> speedRunForwardBeforeTurn90
			runCase2 = 23;
			break;
			case 23:
			if(cnt1 > 5000){
				return 100;
				break;
			}
			LineCheck = checkCrossHalfLine();
			if (LineCheck)
			{
				switch (LineCheck)
				{
					case 2: //LEFT
					line = 2;
					handle (-30); // -45 --> -30
					//speed(0,0);
					brakeTheCar(timerBrake90,speedBrake90); // speed() --> brake the car()
					beep_long(100);
					runCase2 = 24;
					cnt1 = 0;
					break;
					
					case 1: //RIGHT
					line = 1;
					handle(30);
					//speed(0,0);
					brakeTheCar(timerBrake90,speedBrake90); // speed() --> brake the car()
					beep_long(100);
					runCase2 = 24;
					cnt1 = 0;
					break;
					default : break;
				}
			}
			else runForwardLine90(speedRun);
			break;
			
			case 24:
			switch( line ) {
				case 2:
				handle(-30); 
				speed(speedSmall90,speedBig90); // speedRun --> speedBoostAfter90
				if(sensorMask(0xff) == 0x00){
					runCase2 = 31;
				}
				cnt1 = 0;
				break;
				
				case 1:
				handle(30); // 45 --> 50
				speed(speedBig90,speedSmall90); // speedRun --> speedBoostAfter90
				if(sensorMask(0xff) == 0x00){
					runCase2 = 41;
				}
				cnt1 = 0;
				break;
				default:
				break;
			}
			break;
			
			case 31:
			RGB(1,0,0);
			handle (-30);  // -45 --> -50
			speed(speedSmall90,speedBig90); // speedRun --> speedBoostAfter90 ---> doi lai
			while (sensorMask(0x10) == 0x00 ) // 0x3c --> 0x10
			{
				speed(speedSmall90,speedBig90);
			}
			cnt1 = 0;
			runCase2 = 46;
			break;
			
			/*else if ((sensorMask (0x02) != 0))
			{
				cnt1 = 0;
				runCase2 = 32;
				break;
			}
			break;
			
			case 32:
			handle (-30);
			speed (0,speedBoostAfter90);
			if (sensorMask(0x0f) == 0x01) {
				runCase2 = 33;
				break;
			}
			else if ()
			break;
			
			case 33:
			handle (-30);
			speed (0,speedRun);
			if (sensorMask(0xf0) == 0x00)
			{
				runCase2 = 34;
				break;
			}
			break;
			case 34:
			handle (15);//35
			speed (0,speedRun);
			if (sensorMask(0x3c)!=0x00)
			{
				cnt1 = 0;
				cnt2 = 0;
				runCase2 = 35;
			}
			break;
			case 35:
			RGB(1,0,1);
			handle (30);
			speed (0,speedRun);
			if (sensorMask(0x3c)!=0x00)
			{
				cnt1 = 0;
				cnt2 = 0;
				runCase2 = 46;
			}
			break;*/
			
			//case 36:
			//cnt3 = 0;
			//while(cnt2 < 200)
			//{
			//	runForwardLine90(speedRun);
			//}
			//cnt3 = 0;
			//return 11;
			//break;
			
			case 41:
			RGB(1,0,0);
			handle(30); //45 --> 50
			speed (speedBig90,speedSmall90); // speedRun --> speedBoostAfter90 ---> doi lai
			while (sensorMask (0x08) == 0x00)
			{
				speed(speedBig90,speedSmall90);
			}
			cnt1 = 0;
			runCase2 = 45;
			break;
			
			/*if ((sensorMask (0xc0) == 0xc0))
			{
				cnt1 = 0;
				runCase2 = 42;
				break;
			}
			break;
			case 42:
			RGB(0,1,0);
			handle (45);
			speed (speedRun,0);
			if ((sensorMask(0xf0) == 0x80))
			{
				runCase2 = 43;
				break;
			}
			break;
			case 43:
			RGB(0,0,1);
			handle (45);
			speed (speedRun,0);
			if ((sensorMask(0xf0) == 0x00))
			{
				runCase2 = 44;
				break;
			}
			break;
			case 44:
			RGB(1,0,1);
			handle (-15);
			speed (speedRun,0);
			if (sensorMask(0x3c)!=0x00)
			{
				cnt1 = 0;
				cnt2 = 0;
				runCase2 = 45;
			}
			break;*/
			
			case 45:
			RGB(1,0,1);
			handle (30);
			speed (speedRun,0);
			if (sensorMask(0x3c)!=0x00)
			{
				cnt1 = 0;
				cnt2 = 0;
				runCase2 = 46;
			}
			break;
			
			case 46:
			RGB(1,1,1);
			cnt2 = 0;
			beep_long(300);
			while(cnt2 < 200)
			{
				runForwardLine90(speedRunForwardBeforeTurn90);
			}
			cnt2 = 0;
			while(cnt2 < timerBoostAfter90)
			{
				runForwardLine90(speedBoostAfter90);
			}
			cnt3 = 0;;
			return 11;
			break;
			default:
			return 11;
			break;
		}
	}
}

int leftLaneChange (int speedRun){
	beep_long(100);
	int runCase3 = 50;
	cnt1 = 0;
	while (1)
	{
		if (checkCrossLine())
		{
			cnt1 = 0;
			return 21;
		}
		switch (runCase3)
		{
			case 50:
			if (cnt1 < 20)
			{
				brakeTheCar(timerBrakeChangeLanes,speedBrakeChangeLanes); 
				runCase3 = 51;
				break;
			}
			//handleAndSpeed(-angle3,speedRun3);
			runForwardLine90(speedRunForwardBeforeChangeLine);
			break;
			case 51:
			if (sensorMask (MASK4_4) == 0x00){
				handleAndSpeed (-angleChangeLanes,speedRun); // ( 30 , 150 )
				runCase3 = 56;
				cnt1 = 0;
				break;
			}
			else
			{
				runForwardLine90(speedRun);
			}
			if (cnt1>3000)
			{
				cnt1 = 0;
				return 11;
			}
			break;
			case 56:
			if (sensorMask(0x60)!=0) //01100000
			{
				cnt1 = 0;
				handleAndSpeed(angleChangeLanes,speedRun); // 190
				runCase3 = 57;
			}
			else 
			break;
			case 57:
			cnt2 = 0;
			if (sensorMask(MASK0_4)!=0)
			{
				cnt1 = 0;
				brakeTheCar(timerBrakeChangeLanes,speedBrakeChangeLanes); 
				runCase3 = 58;
				break;
			}
			break;
			case 58:
			while(cnt2 < 200)
			{
				runForwardLine90(speedRun);
			}
			cnt2 = 0;
			runCase3 = 59;
			break;
			case 59:
			while(cnt2 < timerBoostAfterChangeLanes)
			{
				runForwardLine90(speedBoostAfterChangeLanes);
			}
			return 11;
			break;
			default:
			return 11;

		}
	}
}
int rightLaneChange(int speedRun)
{
	beep_long(100);
	int runCase4 = 60;
	int cnt1  = 0;
	while (1)
	{
		if (checkCrossLine())
		{
			cnt1 = 0;
			return 21;
		}
		switch (runCase4)
		{
			case 60:
			if (cnt1 < 50)
			{
				brakeTheCar(timerBrakeChangeLanes,speedBrakeChangeLanes);
				runCase4 = 61;
				break;
			}
			//handleAndSpeed(angle3,speedRun3); // moi them
			runForwardLine90(speedRunForwardBeforeChangeLine);
			break;
			case 61:
			if (sensorMask (MASK4_4) == 0x00){
				handleAndSpeed (angleChangeLanes,speedRun);
				runCase4 = 66;
				cnt1 = 0;
				beep_long(100);
				break;
			}
			else
			{
				runForwardLine90(speedRun);
			}
			if (cnt1>3000)
			{
				cnt1 = 0;
				
				return 11;
			}
			break;
			case 66:
			if (sensorMask(0x06)!=0) //00000110
			{
				cnt1 = 0;
				handleAndSpeed(-angleChangeLanes,speedRun);
				runCase4 = 67;
			}
			break;
			case 67:
			cnt2 = 0;
			if (sensorMask(MASK4_0)!=0)
			{
				cnt1 = 0;
				brakeTheCar(timerBrakeChangeLanes,speedBrakeChangeLanes);
				runCase4 = 68;
				break;
			}
			break;
			case 68:
			while(cnt2 < 200)
			{
				runForwardLine90(speedRun);
			}
			runCase4 = 69;
			cnt2 = 0;
			break;
			case 69:
			while(cnt2 < timerBoostAfterChangeLanes)
			{
				runForwardLine90(speedBoostAfterChangeLanes);
			}
			return 11;
			break;
			default:
			return 11;

		}
	}
}
void runForwardLineLeft(int speedRun){
	unsigned char temp;
	temp = sensorMask(MASK4_4);
	switch(temp) {
		case 0x01:// 00000001
		handleAndSpeed (2,speedRun);
		break;
		case 0x03://00000011
		case 0x02://00000010
		handleAndSpeed (0,speedRun);
		break;
		case 0x07://00000111
		handleAndSpeed (-1,speedRun);
		break;
		case 0x06://00000110
		case 0x04:
		handleAndSpeed (-3,speedRun);
		break;
		case 0x0e://00001110
		handleAndSpeed (-3,speedRun);
		break;
		case 0x1e://00011110
		handleAndSpeed (-5,speedRun);
		break;
		case 0x1c://00011100
		case 0x0c:
		handleAndSpeed (-5,speedRun);
		break;
		case 0x38://00111000
		case 0x18://00011000
		case 0x10://00010000
		handleAndSpeed (-7,speedRun);
		break;
		case 0x70://00000111
		handleAndSpeed (-7,speedRun);
		break;
	}
}
void runForwardLineRight(int speedRun){
	unsigned char temp;
	temp = sensorMask(MASK4_4);
	switch(temp) {
		case 0x80://
		handleAndSpeed (-1,speedRun);
		break;
		case 0xc0://
		handleAndSpeed (0,speedRun);
		break;
		case 0x40://
		case 0xe0://
		case 0x60://
		handleAndSpeed (2,speedRun);
		break;
		case 0x70://
		case 0x20://
		case 0x78://
		handleAndSpeed (3,speedRun);
		break;
		case 0x38://
		case 0x10:
		case 0x30:
		case 0x1c://
		case 0x18:
		case 0x08:
		handleAndSpeed (5,speedRun);
		break;
		case 0x0e://
		case 0x0c://
		case 0x04:
		handleAndSpeed (10,speedRun);
		break;
	}
}
void handleAndSpeedMicro (int angle,int speed1)
{
	int speed2;
	int speed3;
	handleMicro(angle);
	if (angle<0){
		angle = -angle;
		speed2 = speed1*coeffR1[angle/10]/100;
		speed3 = speed1*coeffR3[angle/10]/100;
		speed (speed2,speed3);
	}
	else if (angle == 0 )
	{
		speed (speed1,speed1);
	}
	else {
		speed2 = speed1*coeffR1[angle/10]/100;
		speed3 = speed1*coeffR3[angle/10]/100;
		speed (speed3,speed2);
	}
}

/************************************************************************/
/* end of file                                                          */
/************************************************************************/
