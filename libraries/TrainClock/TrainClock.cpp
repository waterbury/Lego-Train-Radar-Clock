#include "Arduino.h"
#include "TrainClock.h"

#include <Wire.h>
#include "RTClib.h"


TrainClock::TrainClock()
{
_timeSinceLast = 1000;
_lastTime = micros();

updateTimeRTC();

}

unsigned long TrainClock::updateTimeRTC()
{

	if(_RTC.IsRunning())
	{
		DateTime now = _RTC.now();

		_timeAtProgramStart = ( (now.hour *60*60) + (now.minute * 60) + (now.second) );
		_timeAtProgramStart = _timeAtProgramStart * 1000 - millis();

		if (_timeAtProgramStart < 0)
		{
		_timeAtProgramStart += (86000 * 1000);
		}
	}
	
	this.updateLastTime();

}

DateTime TrainClock::GetRTCNow() {return _RTC.now(); }


//Starts stop watch in Micro Seconds
void TrainClock::updateLastTime()
{

_lastTime = micros();

}

//Finds time since stop watch began. Should be able to measure up about 71 minutes in length, else results will overflow back to zero
unsigned long TrainClock::getTimeSinceLast()
	{
	
//Micros is a 32-bit value,  Arduino Atmega8 series chips overflow Micros() after a little over 71 minutes.
//If overflowed to zero, add 32-bit max to current micros and subtract previous value
	if (micros() < _lastTime)
	{
		timeSinceLast = 4294967296 + micros() - _lastTime;
	}
	else
	{
		timeSinceLast = micros() - _lastTime;;
		return timeSinceLast;
	 
	 }
	 
	return 0;
	}
	
unsigned long getTimeMillis()
{




}

struct hands getTimeNow()
{




}