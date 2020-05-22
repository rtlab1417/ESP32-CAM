/*
  Test arduino function
  bit and bytes

  ## Rotate bit data right to left ##
  bit0 --> 1 --> 2 --> 3 --> ....---> bit 15

  The concept: Given data, x
  1. read x and check MSB -->
  2. shift x to left by one bit
  3. compare 
            if MSB == 1, then add 1 to x
            if MSB == 0, do nothing
  Note:
  1. For 16-bits, apply unsigned int. Do not use signed int
  2. For 8-bits, apply byte

*/

// unsigned only.
// key in the pattern in HEX
//unsigned int pattern = 0x3333; 
//byte pattern = 0x3333; 
//uint16_t pattern = 0x3333; 
int16_t pattern = 0x3333; 

int pins[] = {12,13,15,14};

// number of LEDs
// for-loop number
int numofpins= sizeof(pins)/sizeof(pins[0]);


// the setup function runs once when you press reset or power the board
void setup() {
    Serial.begin(115200); // baudrate set in device manager
  
  // initialize digital pin LED_BUILTIN as an output.
    pinMode(12,OUTPUT);
    pinMode(13,OUTPUT);
    pinMode(14,OUTPUT);
    pinMode(15,OUTPUT);
}


// the loop function runs over and over again forever
void loop() {
    int mytime = random(50, 500);   // Running light rotate much lively. Can be a fix number

// Serial monitoring. To read slowly and at ease, increase delay()     
    //Serial.print("Delay time ==  ");
    //Serial.println(mytime);   // delay time
    Serial.print("pattern == 0x ");
    Serial.println(pattern, HEX);   // data in HEX
    Serial.print("pattern == B  ");
    Serial.println(pattern, BIN);   // data in BIN
    //Serial.print("pattern AND 0x8000 == ");
    //Serial.println((pattern & 0x8000 > 0));
  
// update the pattern to the outputs. Only to declare pinouts.
   for (int i = 0; i < numofpins; i++) {
      bool mybool = bitRead(pattern, i);
      //Serial.print(i);
      //Serial.print("  ");
      //Serial.println(mybool);
      digitalWrite(pins[i],mybool);
    }
    
// rotate the pattern
    if ((pattern & 0x8000) > 0) {     // Bit test MSB. If MSB == 1, shift data then +1
      pattern = pattern << 1;         // Shift 1 bit left --> meaning shift in 0
      pattern++;                      // Add 1 at LSB
    } else {                          // Else
      pattern = pattern << 1;         // Shift 1 bit left. Then do nothing else.
    }
    
    delay(2000);
    //delay(mytime);   // During debugging, key in a bigger and fix number.
}
