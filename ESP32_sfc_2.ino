/*
 * Planning a format for writing sequential program for arduino
 * 
 * Use the concept of Sequential Function Chart (SFC)
 * State - Sx   
 * Transition - Tx
 */

uint16_t state = 0x0000; // upon start-up, all states are zero

// Assigned output pins
// to indicate the state outputs
int pins[] = {12,13,15,14};

// assigned as transition trigger
// example: a pushbutton
const int  buttonPin = 2;    

// trial ==> Rising edge detection ==> from StateChangeDetection
int transition = 0;         // current state of the button
int lasttransition = 0;     // previous state of the button

// number of outputs
// for-loop number
int numofpins= sizeof(pins)/sizeof(pins[0]);

void setup() {
Serial.begin(115200); // baudrate set in device manager
Serial.println(state, HEX);

// initialize the button pin as a input:
pinMode(buttonPin, INPUT);
    
// initialize digital pins as outputs
// pins[] = {12,13,14,15}
for (int i = 0; i < numofpins; i++) {
  pinMode(pins[i],OUTPUT);
}
    
// State 0 ==> Initialization - all outputs zero
for (int i = 0; i < numofpins; i++) {
  digitalWrite(pins[i],0);
}

state = 0x0001; // raise S1
Serial.println(state, HEX);

// list current states
// just for monitoring.
// ignore if possible
// liststate();

}

void loop() {

// Button rising edge detection
// Adopted from StateChangeDetection.ino
// assume as a sensor input
    transition = digitalRead(buttonPin);
  
// *************** Transition rung - start ******************
// compare the transition to its previous state
// for neatiness, refer to function
    risingedge();
  
// *************** Transition rung - end    ******************

// *************** States and outputs - start *****************

    // Update state to designed outputs
    // if S1 true, do the action
    // action ==> 0011
    // int pins[] = {12,13,15,14};
    if (bitRead(state, 0)== 1){
      // actions
      digitalWrite(pins[0],bitRead(state, 0));
      digitalWrite(pins[1],bitRead(state, 0));
      digitalWrite(pins[2],0);
      digitalWrite(pins[3],0);
    }

    // if S2 true, do the action
    // action ==> 0110
    if (bitRead(state, 1)== 1){
      digitalWrite(pins[0],0);
      digitalWrite(pins[1],bitRead(state, 1));
      digitalWrite(pins[2],bitRead(state, 1));
      digitalWrite(pins[3],0);
    }

    // if S3 true, do the action
    // action ==> 1100
    if (bitRead(state, 2)== 1){
      digitalWrite(pins[0],0);
      digitalWrite(pins[1],0);
      digitalWrite(pins[2],bitRead(state, 2));
      digitalWrite(pins[3],bitRead(state, 2));
    }

    // if S4 true, do the action
    // action ==> 1001
    if (bitRead(state, 3)== 1){
      digitalWrite(pins[0],bitRead(state, 3));
      digitalWrite(pins[1],0);
      digitalWrite(pins[2],0);
      digitalWrite(pins[3],bitRead(state, 3));
    }

}


// ***************** functions *************************
// detect rising edge of a transition trigger
void risingedge(){
  
  if (transition != lasttransition) {
    
// Transition
// At each state, change state if transition is triggered
// rising edge only
    // S1 ON and T2 triggered  ==> transition to S2
    if (bitRead(state, 0)== 1 && transition == HIGH ) {
      state = state << 1;   // state shift
      Serial.println(state, HEX);
      goto endloop;  // jump out of the rest of if-statement
    }
    //S2 ON and T3 triggered ==> transition to S3
    if (bitRead(state, 1)== 1 && transition == HIGH ) {
      state = state << 1;   // state shift
      Serial.println(state, HEX);
      goto endloop;  // jump out of the rest of if-statement
    }

    //S3 ON and T4 triggered ==> transition to S4
    // loop state to S1
    if (bitRead(state, 2)== 1 && transition == HIGH ) {
      state = state << 1;   // state shift
      Serial.println(state, HEX);
      goto endloop;  // jump out of the rest of if-statement
    }

    //S4 ON and T5 triggered ==> loop to S1
    if (bitRead(state, 3)== 1 && transition == HIGH ) {
      state = 0x0001;
      Serial.println(state, HEX);
      goto endloop;  // jump out of the rest of if-statement
    }
  endloop:
    
  // Delay a little bit to avoid bouncing
  delay(50);
  }
  
lasttransition = transition;
  
}

// for debugging purpose.
// can be ignored once done.
void liststate(){
for (int i = 0; i < 16; i++) {
  bool mybool = bitRead(state, i);
  //Serial.print("State ");
  //Serial.print(i);
  //Serial.print("  == ");
  //Serial.println(mybool);
  //digitalWrite(pins[i],mybool);
}
//Serial.println("***************************");
}
