/*Train Clock Library
(C)2012 Theodore "Waterbury" Wahrburg

*/

#include "Arduino.h"

#ifndef TrainClock_h
#define TrainClock_h


class TrainClock
{
	public:
	
	
		unsigned long updateTimeRTC();
		
		void updateLastTime();
		unsigned long getTimeSinceLast();
		
		struct hands getHandTimes();
		unsigned long getTimesMillis();
		
		
		
		
	private:
	unsigned long _timeSinceLast;
	unsigned long _lastTime;
	




};


#endif