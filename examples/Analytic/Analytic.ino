/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */
 
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led = 13;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);   
   Serial.begin(9600);
 attachInterrupt(0, interrupt, CHANGE); 
}

// the loop routine runs over and over again forever:
void loop() {
      
}
boolean toggle = HIGH;
void interrupt()
{
digitalWrite(led, toggle);
toggle = !toggle;

static unsigned long lastTime = 0;
	unsigned long now = micros();
	unsigned int length = now - lastTime;
	lastTime = now;
 if(length>3000)
    Serial.println(length);
}
