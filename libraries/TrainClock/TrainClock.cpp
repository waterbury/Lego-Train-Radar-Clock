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

void findBlipsClockwise(long currentTime,unsigned long speedOfTrain)
{
// find hours by dividing by seconds in hour. In order to make 12 hour time, must mod by 12..
double hoursDeg = currentTime / 3600.0 % 12;

// truncate hours by 1 to get decimal seconds, then multiply by 60 to get minutes
double minutesDeg = hours % 1 * 60; 

//truncate minutes by 1 to get decimal seconds, then multiply by 60 to get whole number. Truncate that value to get rational number
int secondsDeg = int(minutes % 1 * 60);

//ex.
//83678 secs = 
//11.243888888888888888888888888889 hours
//14.63333333333333333333333333334 minutes
//(38).0000000000000000000000000004 seconds

hourDeg *= 30; // multiply 12 hour hours by 30 to get degree around clock
minutesDeg *= 6; // multiply minutes by 6 to get degree around clock
secondsDeg *= 6; // multiply seconds by 6 to get degree around clock


//speedOfTrain is degrees per second train is moving

//speedOfSecs is speed secondhand is moving per sec, ditto for speedOfMins, SpeedOfHours

//6 degrees per sec
int speedOfSecs = 6;
//6 degrees per 60 secs (1 minute) (6/60 = .01 degree per sec)
float speedOfMins = 0.1;
//hours move 30 degrees per 3600 secs (1 hour) (30/3600 = 0.00833333.. degree per sec)
double speedOfHours = 0.0083333;

// (D)istance = (R)ate * (T)ime
// Distance(Time hand was at 0) = ( speedOfTrain + speedOf[hand]) * Time
// Time = (speedOfTrain + speedOf[hand]) / (hand position at 0)
// Train will intersect in time found. 
// If train is moving 180 degrees a sec and time is .5 sec, hand will intersect @ 90 degrees
// intersection[Hand] = speedOfTrain * Time


int intersectionSeconds = speedOfTrain * ( (speedOfTrain + speedOfSecs) / secondsDeg);
int intersectionMinutes = speedOfTrain * ( (speedOfTrain + speedOfMins) / minutesDeg);
int intersectionHours   = speedOfTrain * ( (speedOfTrain + speedOfHours) / hoursDeg);


      //Perform Modulus operation of the Intersect by 360. Ex. If value is 366, modulus would be 6. Draw 1 second hand in first loop.
      intersectionSeconds = intersectionSeconds % 360;
      intersectionMinutes = intersectionMinutes % 360;
      intersectionHours = intersectionHours % 360;

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

