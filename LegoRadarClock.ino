/*
Arduino Based Lego Train "Radar Clock"
(C) Theodore "Waterbury" Wahrburg; 2012

V.0.0.4

*/

//define what pins trigger which LEDs
#define LED_STATUS   13
#define LED_SECONDS   6
#define LED_MINUTES   9
#define LED_HOURS    10


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

}

void loop() 
  {
 
    
  }
  
//Function Which draws points from 0-360 degrees as viewed clockwize. i.e., 90 Degrees Represents 3 O'Clock on Track
//HourDeg will illuminate LED that is reserved for Hours, ditto with Minutes and Seconds
void DrawCoord(int hourDeg, int minuteDeg, int secondDeg)
{
  
}
