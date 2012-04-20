/*Train Clock Library
(C)2012 Theodore "Waterbury" Wahrburg

*/

#include "Arduino.h"
#include <RTClib.h>

#ifndef TrainClock_h
#define TrainClock_h


//6 degrees per sec
const int SPEED_OF_SECS = 6;
//6 degrees per 60 secs (1 minute) (6/60 = .01 degree per sec)
const float SPEED_OF_MINS = 0.1;
//hours move 30 degrees per 3600 secs (1 hour) (30/3600 = 0.00833333.. degree per sec)
const double SPEED_OF_HOURS = 0.0083333;

const int DRAWLENGTH = 30;
const int OFFSET = int(DRAWLENGTH / 2);


class TrainClock
{
	public:
	

	
	TrainClock();
		//unsigned long updateTimeRTC();
		
			
		unsigned long getTimeSinceLast();
		void setLastTime();
		
		unsigned long setTimeMillis(long);
		long getTimeMillis();
		
		void findBlipsCounterClockwise(unsigned long, unsigned long);
		void findBlipsClockwise(unsigned long, double);
		
		void bubbleSortArray (void);
		int getBlipArray(int,int);
	//	struct hands getHandTimes();
	//	unsigned long getTimesMillis();
		
		
		
		
	private:
	unsigned long _timeSinceLast;
	unsigned long _lastTime;
	unsigned long _millisAtLastCall;
	unsigned long _timeAtZero;
	int blipArray[6][3];// = {0};
	//RTC_DS1307 _RTC;
	
	
};


#endif