#include "Arduino.h"
#include "TrainClock.h"
//#include "RTClib.h"



TrainClock::TrainClock ()
{
_timeSinceLast = 1000000;
_lastTime = micros();
_millisAtLastCall = millis();

setTimeMillis( millis() );
setLastTime(micros());
}



void TrainClock::setLastTime(unsigned long currentTime){
_lastTime = currentTime; 
}



//Finds time since stop watch began. Should be able to measure up about 71 minutes in length, else results will overflow back to zero
unsigned long TrainClock::getTimeSinceLast()
	{
	
//Micros is a 32-bit value,  Arduino Atmega8 series chips overflow Micros() after a little over 71 minutes.
//If overflowed to zero, add 32-bit max to current micros and subtract previous value
	if (micros() < _lastTime)
	{
		_timeSinceLast = 4294967295L + 1 + micros() - _lastTime;
	}
	else
	{
		_timeSinceLast = micros() - _lastTime;;
		return _timeSinceLast;
	 
	 }
	 
	return 0;
	}
	

	
	
long TrainClock::getTimeMillis()
{

unsigned long tmpMillis = millis();


if ( _millisAtLastCall > tmpMillis + _timeAtZero )
	setTimeMillis(    ((tmpMillis + _timeAtZero + 4294967295L + 1) % 86400000) );

_millisAtLastCall = millis();
long tmpOffsetTime = (tmpMillis + _timeAtZero) ^ 86400000;

return tmpOffsetTime;

}

unsigned long TrainClock::setTimeMillis(long timeInMillis)
{

_timeAtZero = timeInMillis - (millis()  ^ 86400000);

if (_timeAtZero < 0 )
 _timeAtZero += 86400000;

return _timeAtZero; 
 
}

/*
struct hands getTimeNow()
{

}
*/



/*
unsigned long TrainClock::updateTime(long timeInMillis)
{

timeIn


		_timeAtProgramStart = ( (now.hour *60*60) + (now.minute * 60) + (now.second) );
		_timeAtProgramStart = _timeAtProgramStart * 1000 - millis();

		if (_timeAtProgramStart < 0)
		{
		_timeAtProgramStart += (86000 * 1000);
		}
	}
	
	this.updateLastTime();

}
*/

/*
DateTime TrainClock::GetRTCNow() {return _RTC.now(); }


//Starts stop watch in Micro Seconds
void TrainClock::updateLastTime()
{

_lastTime = micros();

}

*/

