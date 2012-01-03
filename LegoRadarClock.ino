/*
Arduino Based Lego Train "Radar Clock"
(C) Theodore "Waterbury" Wahrburg; 2012

V.0.0.3

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
