#include <Wire.h>
#include <SPI.h>
#include <RTClib.h>
#include "TrainClock.h"


 long day = 86400000; // 86400000 milliseconds in a day
 long hour = 3600000; // 3600000 milliseconds in an hour
 long minute = 60000; // 60000 milliseconds in a minute
 long second =  1000; // 1000 milliseconds in a second
extern volatile unsigned long timer0_millis; 


TrainClock train;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
randomSeed(analogRead(0));

timer0_millis = 4294942296L;

Serial.print("timeAtZero: ");
Serial.println(train.setTimeMillis(86370000) ); //Start at Noon
Serial.println("");
Serial.println("");
Serial.println("");


}

void loop() 
{
DateTime now;

long timeNow = train.getTimeMillis();

 int days = timeNow / day ;                                //number of days
 int hours = (timeNow % day) / hour;                       //the remainder from days division (in milliseconds) divided by hours, this gives the full hours
 int minutes = ((timeNow % day) % hour) / minute ;         //and so on...
 int seconds = (((timeNow % day) % hour) % minute) / second;
  
  // put your main code here, to run repeatedly: 
 Serial.print("          Time: ");
 Serial.print(timeNow);
 Serial.print("     "); 
 Serial.print(hours);
 Serial.print(":");
 Serial.print(minutes);
 Serial.print(":");
 Serial.print(seconds);
 Serial.println("");
 Serial.print("millis: ");
 Serial.println(millis());
 Serial.println();

 delay(700);

 
 train.setLastTime();
 int randValue = random(16000);
 delay(randValue);
 Serial.print("Random Value: ");
 Serial.println(randValue/1000.0);
  Serial.print("Time Since Last: "); 
 Serial.println(train.getTimeSinceLast()/1000000.0);
 
 
 
  
  
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

