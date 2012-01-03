/*
Arduino Based Lego Train "Radar Clock"
(C) Theodore "Waterbury" Wahrburg; 2012

V.0.0.6

*/

//define what pins trigger which LEDs
#define LED_STATUS   13
#define LED_SECONDS   6
#define LED_MINUTES   9
#define LED_HOURS    10

//define which pin houses IR Sensor
#define IR_PIN        2


//Indicates If IR Iterrupt Occured
volatile int IR_Triggered = 0;

volatile long startTime = 0;
volatile long timeSinceLastIR =0;

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
  

}

void loop() 
  {

 
    if(IR_Triggered)
    {
      //Detaches IR Interrupt
      detachInterrupt(0);
      IR_Triggered = 0;
      
      timeSinceLastIR = micros() - startTime;
      startTime = micros();
      
      Serial.print(count++);
      Serial.print(" -- Time Between Last 2 IR Senses:");
      Serial.println( float(timeSinceLastIR/1000000.0) );
      
      
      
      //Reattaches IR Interrupt
      delay(30);
      attachInterrupt(0, IR_Trigger, FALLING);
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
