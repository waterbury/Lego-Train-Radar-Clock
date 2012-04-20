
/*
Arduino Based Lego Train "Radar Clock"
(C) Theodore "Waterbury" Wahrburg; 2012

V.0.1.4

*/

#include <Wire.h>
#include <SPI.h>
#include <RTClib.h>
#include "TrainClock.h"


//define what pins trigger which LEDs
#define LED_STATUS  13
#define LED_SECONDS  6
#define LED_MINUTES  9
#define LED_HOURS   10

//define which pin houses IR Sensor
#define  IR_PIN      2

//define which pin detects for the direction of the train. Whether it is running clockwise, or counter-clockwise
#define CLOCKWISE_DETECT 19


//Indicates If IR Iterrupt Occured
volatile int IR_Triggered = 0;

double speedOfTrain = 0;  

 float speedDifference = 0;
 
 
int count = 0;




//Function for Infrared LED Interrupt
void IR_Trigger()
{
IR_Triggered = 1;

}

/*
void drawTimer()
{
timerTriggered = 1;
}
*/

TrainClock train;



void setup() {
  
  
  Serial.begin(9600);



train.setTimeMillis(63200);
train.setLastTime();

  //Sets up LED pins to output
  pinMode(LED_STATUS, OUTPUT);
  pinMode(LED_SECONDS, OUTPUT);
  pinMode(LED_MINUTES, OUTPUT);
  pinMode(LED_HOURS, OUTPUT);
  //Sets Up IR Pin as input, for interrupt
  pinMode(IR_PIN, INPUT);
  
  pinMode(CLOCKWISE_DETECT, INPUT); // set pin to detect whether train is moving clockwise to input
  digitalWrite(CLOCKWISE_DETECT, HIGH); // turn on pullup resistor for PIN. If High, train is moving clockwise

  //Sets up IR PIN to Interrupt Microcontroller as IR Detector pulls pin low
  attachInterrupt(0, IR_Trigger, FALLING);
  
  
        digitalWrite(LED_STATUS, HIGH);
  
  //Initialize Timer1
//  Timer1.initialize(500000);
  //Timer1.attachInterrupt(drawTimer);
/*  
  Timer1.disablePwm(LED_HOURS);
  Timer1.disablePwm(LED_MINUTES);
  Timer1.disablePwm(LED_SECONDS);
  Timer1.disablePwm(LED_STATUS);
*/
}

void loop()
  {
    
    if(IR_Triggered)
    {
      //Detaches IR Interrupt
      //detachInterrupt(0);
      IR_Triggered = 0;
      digitalWrite(LED_STATUS, LOW);
      
      if( train.getTimeSinceLast() > 1500000)
      {
        
    //    printTime();
        
        
        //Speed of train is determined by dividing the 360 degrees of the track circle by the time taken.
        speedOfTrain = 90;//360/ (train.getTimeSinceLast()/1000000.0);
        Serial.print("speedOfTrain: ");
        Serial.println(speedOfTrain);
        
        train.setLastTime();
        digitalWrite(LED_STATUS, HIGH);   
        //If train is moving clockwise, CLOCKWISE_DETECT will be HIGH, else if counter-clockwise pin will be LOW
        if ( digitalRead(CLOCKWISE_DETECT) == HIGH)
        {
       //   digitalWrite(LED_HOURS,1);
          train.findBlipsClockwise( 30 /*train.getTimeMillis()*/, speedOfTrain );
        //  digitalWrite(LED_MINUTES,1);
        }
        else
        {
        }
      

      count = 0;

      }
     }
     
     if (count<6)
       if ( int(speedOfTrain * (train.getTimeSinceLast() /1000000) )  >= (train.getBlipArray(count,0) )  )
        {
          Serial.print("count: ");
          Serial.println (count);
          Serial.println ( int(speedOfTrain * (train.getTimeSinceLast() /1000000) ) );
          
          
          if ( train.getBlipArray(count,0) <=360)
          {
            Serial.print("Blip : ");
            Serial.print(train.getBlipArray(count,0));
            Serial.print(" Type: ");
             Serial.print(train.getBlipArray(count,1));
            Serial.print(" switch: ");           
             Serial.println(train.getBlipArray(count,2));
             Serial.println("-----------------");

            
          if (train.getBlipArray(count,1) == 0)
          digitalWrite(LED_SECONDS, train.getBlipArray(count,2) ) ;
          
          else if (train.getBlipArray(count,1) == 1)
          digitalWrite(LED_MINUTES, train.getBlipArray(count,2) ) ;

          else if (train.getBlipArray(count,1) == 2)
          digitalWrite(LED_HOURS, train.getBlipArray(count,2) ) ;
          }
          
         count++; 
        }  
  //   Serial.print(train.getTimeSinceLast() );   
    // Serial.print(": ");   
     //Serial.println(  train.getBlipArray(0,0));
    
  }


/*

void printTime(void){
  
 long day = 86400000; // 86400000 milliseconds in a day
 long hour = 3600000; // 3600000 milliseconds in an hour
 long minute = 60000; // 60000 milliseconds in a minute
 long second =  1000; // 1000 milliseconds in a second

  
  
 long timeNow = train.getTimeMillis();

 int days = timeNow / day ;                                //number of days
 int hours = (timeNow % day) / hour;                       //the remainder from days division (in milliseconds) divided by hours, this gives the full hours
 int minutes = ((timeNow % day) % hour) / minute ;         //and so on...
 int seconds = (((timeNow % day) % hour) % minute) / second;
  
  // put your main code here, to run repeatedly: 
 Serial.print("          Time: H:");
 Serial.print(hours);
 Serial.print(" M:");
 Serial.print(minutes);
 Serial.print(" S:");
 Serial.print(seconds);
 Serial.print(" Millis:");

 Serial.println(millis());


// delay(700);
 
  
  
}
*/



