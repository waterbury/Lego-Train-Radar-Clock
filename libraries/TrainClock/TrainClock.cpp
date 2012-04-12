#include "Arduino.h"
#include "TrainClock.h"
#include "RTClib.h"



TrainClock::TrainClock ()
{
_timeSinceLast = 1000000;
setLastTime();
_millisAtLastCall = millis();

setTimeMillis( millis() );

}



void TrainClock::setLastTime(){
_lastTime = micros(); 
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
	
	 
	 }
	 
	return _timeSinceLast;
	}
	

	
	
long TrainClock::getTimeMillis()
{

unsigned long long tmpMillis = millis();


if ( _millisAtLastCall > tmpMillis ) //+ _timeAtZero )
	setTimeMillis(    ( (tmpMillis + _timeAtZero + 4294967295LL + 1) % 86400000) );

_millisAtLastCall = millis();
long tmpOffsetTime = (tmpMillis + _timeAtZero) % 86400000;

return tmpOffsetTime;

}

unsigned long TrainClock::setTimeMillis(long timeInMillis)
{

timeInMillis = timeInMillis % 86400000;

_timeAtZero = timeInMillis - (millis()  % 86400000L);

if (_timeAtZero < 0 )
 _timeAtZero += 86400000;

return _timeAtZero; 
 
}

void findBlipsClockwise(long currentTimeMillis)
{


}

void TrainClock::bubbleSortArray (void)
{

	for(int x=0; x<6; x++)
	{
		for(int y=0; y<5; y++)
		{
		    //if degrees is larger than next..
			if(blipArray[y][0]>blipArray[y+1][0])
			{
			    //log next degree and hand value
				int tempDegrees = blipArray[y+1][0];
				int tempHand = blipArray[y+1][1];
				//set next degree value to current LARGER degree value, while moving hand value
				blipArray[y+1][0] = blipArray[y][0];
				blipArray[y+1][1] = blipArray[y][1];
				//set previous next degrees value to current
				blipArray[y][0] = tempDegrees;
				blipArray[y][1] = tempHand;

			}
		}
	}

}

