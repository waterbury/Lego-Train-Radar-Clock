/*
Arduino Based Lego Train "Radar Clock"
(C) Theodore "Waterbury" Wahrburg; 2012

V.0.1.4

*/

//#define DS1307_CTRL_ID 0x68 

#include <Wire.h>
#include <SPI.h>
#include <RTClib.h>
//#include <DS1307RTC.h>
#include "TrainClock.h"


//define what pins trigger which LEDs
#define LED_STATUS  13
#define LED_SECONDS  6
#define LED_MINUTES  9
#define LED_HOURS   10
//define which pin houses IR Sensor
#define  IR_PIN      2
//define which pin detects for the direction of the train. Whether it is running clockwise, or counter-clockwise
#define CLOCKWISE_DETECT 12


//Indicates If IR Iterrupt Occured
volatile int IR_Triggered = 0;

//speedOfTrain specifies speed train is moving in degrees per second. There are 360 degrees to train track ring.
double speedOfTrain = 0;  


int count = 0;
int isClockwise = 1;//will be 1 if train car is moving clockwise, will be pulled low if train is moving counter-clockwise

RTC_DS1307 RTC;// Object for RTC time keeping, as provided by Adafruit fork of <rtclib.h>
TrainClock train;//Train object, keeps stop watch for time taken around track, and keeps global time indefinetly.

//Function for Infrared LED Interrupt
void IR_Trigger() {	IR_Triggered = 1; }//If IR Sensor is triggered, Set IR_Triggered HIGH, and exit.

void setup() 
{
	Serial.begin(9600);

	pinMode(CLOCKWISE_DETECT, INPUT); // set pin to detect whether train is moving clockwise to input
	digitalWrite(CLOCKWISE_DETECT, HIGH); // turn on pullup resistor for PIN. If High, train is moving clockwise
	
	//Sets up LED pins to output
	pinMode(LED_STATUS, OUTPUT);
	pinMode(LED_SECONDS, OUTPUT);
	pinMode(LED_MINUTES, OUTPUT);
	pinMode(LED_HOURS, OUTPUT);
	//Sets Up IR Pin as input, for interrupt
	pinMode(IR_PIN, INPUT);

	//Sets up IR PIN to Interrupt Microcontroller as IR Detector pulls pin low
	attachInterrupt(0, IR_Trigger, FALLING);
	
	//check direction Train is moving. Delay this process by 1.5s to ensure train voltages have stablized
	delay(1500);
	isClockwise = digitalRead(CLOCKWISE_DETECT);//1=Train moving clockwise, 0 = Train moving CounterClockwise
	
	if(CLOCKWISE_DETECT == 1)
	count =0;
	else
	count =6;

	//------------------- RTC Reference Code as provided by Adafruit RTClib.h example	
	//If no RTC is present, sets RTC object to current uptime of Arduino
	Wire.begin();
	RTC.begin();

	if (! RTC.isrunning()) {
		Serial.println("RTC is NOT running!");
		// following line sets the RTC to the date & time this sketch was compiled
		RTC.adjust(DateTime(__DATE__, __TIME__));
	}
	//---------------------------------------------------------------------------------
	
	//Takes standard unixtime, mods it by 86400 to get daily time in seconds, then multiplies by 1000 to get millis
	//, then sets train's global time
	train.setTimeMillis( (RTC.now().unixtime() % 86400 ) * 1000 );
	//Sets first start of clockwatch as NOW
	train.setLastTime();

}

void loop()
{
	//If IR Sensor was triggered..
	if(IR_Triggered)
	{
		//Acknowlege, and remove flag
		IR_Triggered = 0;
		
		//To reduce False positives as train moves by IR LED, only except interrupts over 500 millis apart
		if( train.getTimeSinceLast() > 500000)
		{
			//Speed of train is determined by dividing the 360 degrees of the track circle by the time taken.
			//Then divdide by 1,000,000 to get speed in secs
			speedOfTrain = 360/ (train.getTimeSinceLast()/1000000.0);
			//Reset start of stopwatch to NOW
			train.setLastTime();
			
			//If train is moving clockwise, CLOCKWISE_DETECT will be HIGH, else if counter-clockwise pin will be LOW
			if (isClockwise == 1)
			{
				for (;count<6;count++)
				if(train.getBlipArray(count,0) <=360)
				drawHand(train.getBlipArray(count,1), train.getBlipArray(count,2) );
				
				train.findBlipsClockwise( train.getTimeMillis(), speedOfTrain );
				count = 0;
				
				//digitalWrite(LED_STATUS, HIGH);   
			}
			else if (isClockwise == 0)
			{
				for (;count>=0; count--)
				if(train.getBlipArray(count,0) >=0)
				drawHand(train.getBlipArray(count,1), train.getBlipArray(count,2) );
				
				train.findBlipsCounterClockwise( train.getTimeMillis(), speedOfTrain );
				count = 5;

				//digitalWrite(LED_STATUS, LOW);   
			}
		}
	}
	
	
	if (isClockwise)
	{
		if (count<6)
		if ( int(speedOfTrain / 1000000.0 * (train.getTimeSinceLast() ) )  >= (train.getBlipArray(count,0) )  )
		{
			if ( train.getBlipArray(count,0) <=360)
			drawHand(train.getBlipArray(count,1), train.getBlipArray(count,2) );
			
			count++; 
		}
	}
	else
	{
		if (count >= 0)
		if ( (360 - int(speedOfTrain/1000000.0*(train.getTimeSinceLast())) )   <= (train.getBlipArray(count,0) )  )
		{
			if ( train.getBlipArray(count,0) >=0)
			drawHand(train.getBlipArray(count,1), train.getBlipArray(count,2) );
			
			count = count - 1;
		}
	}
}

//Draws Hand Type. 0 = 
void drawHand(int hand, int value)
{
	if (value != 1 && value != 0)
	value = 0;

	if (hand == 0)
	digitalWrite(LED_SECONDS, value ) ;
	
	else if (hand == 1)
	digitalWrite(LED_MINUTES, value ) ;

	else if (hand == 2)
	digitalWrite(LED_HOURS, value ) ;
}






