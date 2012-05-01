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

double speedOfTrain = 0;  
float speedDifference = 0;
int count = 0;
RTC_DS1307 RTC;
TrainClock train;
int isClockwise = 1;


//Function for Infrared LED Interrupt
void IR_Trigger() {	IR_Triggered = 1; }

void setup() 
{
	Serial.begin(9600);

	pinMode(CLOCKWISE_DETECT, INPUT); // set pin to detect whether train is moving clockwise to input
	digitalWrite(CLOCKWISE_DETECT, HIGH); // turn on pullup resistor for PIN. If High, train is moving clockwise

	Wire.begin();
	RTC.begin();

	if (! RTC.isrunning()) {
		Serial.println("RTC is NOT running!");
		// following line sets the RTC to the date & time this sketch was compiled
		RTC.adjust(DateTime(__DATE__, __TIME__));
	}
	train.setTimeMillis( (RTC.now().unixtime() % 86400 ) * 1000 );

	delay(1500);
	isClockwise = digitalRead(CLOCKWISE_DETECT);
	train.setLastTime();

	//Sets up LED pins to output
	pinMode(LED_STATUS, OUTPUT);
	pinMode(LED_SECONDS, OUTPUT);
	pinMode(LED_MINUTES, OUTPUT);
	pinMode(LED_HOURS, OUTPUT);
	//Sets Up IR Pin as input, for interrupt
	pinMode(IR_PIN, INPUT);

	//Sets up IR PIN to Interrupt Microcontroller as IR Detector pulls pin low
	attachInterrupt(0, IR_Trigger, FALLING);


	digitalWrite(LED_STATUS, HIGH);

}

void loop()
{
	if(IR_Triggered)
	{
		IR_Triggered = 0;
		
		if( train.getTimeSinceLast() > 500000)
		{
			//Speed of train is determined by dividing the 360 degrees of the track circle by the time taken.
			speedOfTrain = 360/ (train.getTimeSinceLast()/1000000.0);
			
			train.setLastTime();
			
			//If train is moving clockwise, CLOCKWISE_DETECT will be HIGH, else if counter-clockwise pin will be LOW
			if (isClockwise == 1)
			{
				train.findBlipsClockwise( /*34252000*/ train.getTimeMillis(), speedOfTrain );
				count = 0;
				digitalWrite(LED_STATUS, HIGH);   
			}
			else if (isClockwise == 0)
			{
				train.findBlipsCounterClockwise( /*34252000*/ train.getTimeMillis(), speedOfTrain );
				count = 5;

				digitalWrite(LED_STATUS, LOW);   
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

void drawHand(int hand, int value)
{
	if (hand == 0)
	digitalWrite(LED_SECONDS, value ) ;
	
	else if (hand == 1)
	digitalWrite(LED_MINUTES, value ) ;

	else if (hand == 2)
	digitalWrite(LED_HOURS, value ) ;
}






