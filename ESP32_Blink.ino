/*
  ESP 32 Blink
  Adopted from Arduino - classical blink
  Turns on an LED on for one second, then off for one second, repeatedly.
  The ESP32 has an internal blue LED at GPIO04 
*/

int LED1 = 12;
// int LED1 = 4;  // built-in LED. very blight. Can be used as cameta flash light

void setup() 
{
  pinMode(LED1, OUTPUT);
}

void loop() 
{
  digitalWrite(LED1, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(LED1, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second
}
