/*Train Clock Library
(C)2012 Theodore "Waterbury" Wahrburg

*/

#include "Arduino.h"

#ifndef TrainClock_h
#define TrainClock_h


class TrainClock
{
	public:
	TrainClock();
		//unsigned long updateTimeRTC();
		
			
		unsigned long getTimeSinceLast();
		void setLastTime(unsigned long);
		
		unsigned long setTimeMillis(long);
		long getTimeMillis();
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