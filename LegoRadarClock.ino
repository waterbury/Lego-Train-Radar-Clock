/*
Arduino Based Lego Train "Radar Clock"
(C) Theodore "Waterbury" Wahrburg; 2012

V.0.0.5

*/

//define what pins trigger which LEDs
#define LED_STATUS   13
#define LED_SECONDS   6
#define LED_MINUTES   9
#define LED_HOURS    10

//define which pin houses IR Sensor
#define IR_PIN        2



//Function for Infrared LED Interrupt
void IR_Trigger()
{
  
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
 
    
    
  //Test Code
  DrawCoord(361,360,0,60);  
  
  delay(500);    
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
