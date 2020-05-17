/*
 * Running light - Alternative ON/OFF bits
 * Output: GPIO - 12, 13, 14, 15
 * increasing number...
 * use iteration loop
 */

int pattern = 0xAAC5; //B1010101010100101;
int inv_pattern = ~pattern;
int pins[] = {12, 13, 15, 14};

// number of LEDs
int numofpins= sizeof(pins)/sizeof(pins[0]);


void setup()
{
  Serial.begin(115200);
  pinMode(12,OUTPUT);
  pinMode(13,OUTPUT);
  pinMode(14,OUTPUT);
  pinMode(15,OUTPUT);

}

// the loop function runs over and over again forever
void loop() {

    // loop from LSB to MSB of 16bits
    // from 0 to 15

    // pattern
    Serial.println("pattern");
    Serial.print("numofpins = ");
    Serial.print(numofpins);
    Serial.println();
    
    // write pattern to outputs
    for (int i = 0; i < numofpins; i++) {
      bool mybool = bitRead(pattern, i);
      Serial.print(i);
      Serial.print("  ");
      Serial.println(mybool);
      digitalWrite(pins[i],mybool);
    }
    
    delay(1000);                       // wait for a second
    // invert pattern
    Serial.println("Invert pattern");

    //write invert pattern to outputs
    for (int i = 0; i < numofpins; i++) {
      bool mybool = bitRead(inv_pattern, i);
      Serial.print(i);
      Serial.print("  ");
      Serial.println(mybool);
      digitalWrite(pins[i],mybool);
    }
    
    delay(1000);                       // wait for a second

}
