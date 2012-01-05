/*
Arduino Based Lego Train "Radar Clock"
(C) Theodore "Waterbury" Wahrburg; 2012

V.0.1.1

*/

//define what pins trigger which LEDs
#define LED_STATUS   13
#define LED_SECONDS   6
#define LED_MINUTES   9
#define LED_HOURS    10

//define which pin houses IR Sensor
#define IR_PIN        2

//define which pin detects for the direction of the train. Whether it is running clockwise, or counter-clockwise
#define CLOCKWISE_DETECT 19     


//Indicates If IR Iterrupt Occured
volatile int IR_Triggered = 0;

volatile long startTime = 0;
volatile long timeSinceLastIR =0;
 float intersection = 0;
 float speedDifference = 0;
 
 
int count = 0;

//Function for Infrared LED Interrupt
void IR_Trigger()
{
IR_Triggered = 1;
digitalWrite(LED_STATUS, HIGH);  
}  

void setup() {
  
  
  
  //Sets up Serial Port; Inform Console
  Serial.begin(9600);
  Serial.println("Arduino Based Lego Train \"Radar Clock\"");
  Serial.println("(C) Theodore \"Waterbury\" Wahrburg; 2012");
 
  //Sets up LED pins to output
  pinMode(LED_STATUS, OUTPUT);
  pinMode(LED_SECONDS, OUTPUT);
  pinMode(LED_MINUTES, OUTPUT);
  pinMode(LED_HOURS, OUTPUT);
  //Sets Up IR Pin as input, for interrupt
  pinMode(IR_PIN, INPUT);
  
  //Sets up IR PIN to Interrupt Microcontroller as IR Detector pulls pin low
  attachInterrupt(0, IR_Trigger, FALLING);
  
  pinMode(CLOCKWISE_DETECT, INPUT);           // set pin to detect whether train is moving clockwise to input
  digitalWrite(CLOCKWISE_DETECT, HIGH);       // turn on pullup resistor for PIN. If High, train is moving clockwise
  

}

void loop() 
  {
    //temp test
    int seconds = 30;
    int speedOfTrain = 0;
    
    if(IR_Triggered)
    {
      //Detaches IR Interrupt
      detachInterrupt(0);
      IR_Triggered = 0;
      digitalWrite(LED_STATUS, LOW);  
      
      timeSinceLastIR = micros() - startTime;
      startTime = micros();
      
      //If train is moving clockwise, CLOCKWISE_DETECT will be HIGH, else if counter-clockwise pin will be LOW
      if ( digitalRead(CLOCKWISE_DETECT) == HIGH)
      {
      //Speed of train is determined by dividing the 360 degrees of the track circle by the time taken. 
      speedOfTrain = float( 360/ (timeSinceLastIR) );
      //It takes each hand of the clock 1 second to move 6 degrees around the clock. Subtract this to find relative speed of both "objects." Dividing by 1 million to turn micros to seconds..  
      speedDifference =  (speedOfTrain/1000000.0) - 6;
      //Find Where hands of clock will be in relation to start point. Divide this distance by relative speed to find intersecion.
      intersectionSeconds = ((seconds * 6.0) / speedDifference) * speedOfTrain;
      intersectionMinutes = ((minutes * 6.0) / speedDifference) * speedOfTrain;
      intersectionSeconds = ((hours * 6.0)   / speedDifference) * speedOfTrain;
      //Perform Modulus operation of the Intersect by 360. Ex. If value is 366, modulus would be 6. Draw 1 second hand in first loop.
      intersectionSeconds = intersectionSeconds % 360;
      intersectionMinutes = intersectionMinutes % 360;
      intersectionHours   = intersectionHours % 360;
      }
      else
      {
      
        
      }
      
      DrawCoord(intersectionHours, intersectionMinutes, intersectionSeconds, int timeToDisplay)
      
       /*TEST
      delay( int(timeSinceLastIR / 2.0 / 1000) );
      digitalWrite(LED_SECONDS, HIGH);
      //TEST*/

      
      Serial.print(count++);
      Serial.print(" -- Time Between Last 2 IR Senses: ");
      Serial.println( float(timeSinceLastIR/1000000.0) );
      
      Serial.print("Speed is: ");
      Serial.print(speedOfTrain);
      Serial.println(" Degrees per second");
      
      
      Serial.print("Speed Distance is: ");
      Serial.print(speedDifference);
      Serial.println(" Degrees per second");
      
      Serial.print("Intersection will be at: ");
      Serial.print(intersection);
      Serial.println(" Degrees");    
      
      

      
      
      //Reattaches IR Interrupt
      delay(30);
      attachInterrupt(0, IR_Trigger, FALLING);
      
      digitalWrite(LED_STATUS, LOW);  
      delay(30);
     
       digitalWrite(LED_SECONDS, LOW);
      
    }
    
  //Test Code
  //DrawCoord(361,360,0,60);  
  //delay(500);    
  }
  
//Function Which draws points from 0-360 degrees as viewed clockwize. i.e., 90 Degrees Represents 3 O'Clock on Track
//HourDeg will illuminate LED that is reserved for Hours, ditto with Minutes and Seconds
//timeToDisplay indicates in milliseconds how long to illuminate LED.
void DrawCoord(int hourDeg, int minuteDeg, int secondDeg, int timeToDisplay)
{

//variables to indicate if degree values are valid
int writeHour   = 0;  
int writeMinute = 0;
int writeSecond = 0;


//Checks if degree values are valid  
if(hourDeg >= 0 && hourDeg <= 360)
 writeHour = 1;
if(minuteDeg >= 0 && minuteDeg <= 360)
 writeMinute = 1;
if(secondDeg >= 0 && secondDeg <= 360)
 writeSecond = 1;
 
if (writeSecond)
  digitalWrite(LED_SECONDS, HIGH);  
if (writeMinute)
  digitalWrite(LED_MINUTES, HIGH); 
if (writeHour)
  digitalWrite(LED_HOURS, HIGH);

delay(timeToDisplay);  
  
digitalWrite(LED_SECONDS, LOW);
digitalWrite(LED_MINUTES, LOW);
digitalWrite(LED_HOURS, LOW);
        
  
  
}
