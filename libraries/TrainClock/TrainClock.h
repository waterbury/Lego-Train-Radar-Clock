/*Train Clock Library
(C)2012 Theodore "Waterbury" Wahrburg

*/

#include "Arduino.h"
#include <RTClib.h>

#ifndef TrainClock_h
#define TrainClock_h


class TrainClock
{
	public:
	
	int blipArray[6][2];
	
	TrainClock();
		//unsigned long updateTimeRTC();
		
			
		unsigned long getTimeSinceLast();
		void setLastTime();
		
		unsigned long setTimeMillis(long);
		long getTimeMillis();
		
		int* findBlipsClockwise(long currentTime);
		
		void bubbleSortArray (void);
	//	struct hands getHandTimes();
	//	unsigned long getTimesMillis();
		
		
		
		
	private:
	unsigned long _timeSinceLast;
	unsigned long _lastTime;
	unsigned long _millisAtLastCall;
	unsigned long _timeAtZero;
	//RTC_DS1307 _RTC;
	
	
};


#endif