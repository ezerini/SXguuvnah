
// Hold A Button + decent blink circuit for indicators

// PROGRESS
// trying to add a cancel blinking function by setting a bool for blinking being true
// get rid of the delay function from the end blinker circuit

int leftPin = 3;                  // the pin number for input (for me a push button)
int leftLEDpin = 7;               // the pin number of the left indicator LED
int leftButtonState;              // current state of the button
long left_millis_held;            // How long the left button was held (milliseconds)
long leftSecsHeld;                // How long the button was held (seconds)
long prev_leftSecsHeld;           // How long the button was held in the previous check
byte prev_leftButtonState = HIGH; // Records the state of the previous left button state
unsigned long firstTime;          // how long since the button was first pressed 

void setup() {
  Serial.begin(9600);         // Use serial for debugging
  pinMode(leftLEDpin, OUTPUT);
//  digitalWrite(leftPin, HIGH);  // Turn on 20k pullup resistors to simplify switch input
}

void loop() {
  leftButtonState = digitalRead(leftPin);

  // if the button state changes to pressed, remember the start time 
  if (leftButtonState == HIGH && prev_leftButtonState == LOW && (millis() - firstTime) > 200) {
    firstTime = millis();
  }

  left_millis_held = (millis() - firstTime);
  leftSecsHeld = left_millis_held / 1000;

  // This if statement is a basic debouncing tool, the button must be pushed for at least
  // 50 milliseconds in a row for it to be considered as a push.
  if (left_millis_held > 50) {

    if (leftButtonState == HIGH && leftSecsHeld > prev_leftSecsHeld) {
      ledblink(1,500,leftLEDpin); // Each second the button is held blink the indicator led
    }

    // check if the button was released since we last checked
    if (leftButtonState == LOW && prev_leftButtonState == HIGH) {
      // HERE YOU WOULD ADD VARIOUS ACTIONS AND TIMES FOR YOUR OWN CODE
      // ===============================================================================

      // Button pressed for less than 1 second, blink LED 4 times
      if (leftSecsHeld <= 0) {
        ledblink(4,500,leftLEDpin);
      }

      // If the button was held for 3-6 seconds blink LED 20 times
      if (leftSecsHeld >= 1 && leftSecsHeld < 3) {
        ledblink(20,500,leftLEDpin); 
      }

      // if any button pressed during blinking, stop blinking
      if (leftSecsHeld <= 1); {
        ledblink(0,0,leftLEDpin); 
      }
        
      
      // ===============================================================================
    }
  }

  prev_leftButtonState = leftButtonState;
  prev_leftSecsHeld = leftSecsHeld;
}

// Just a simple helper function to blink an led in various patterns
void ledblink(int times, int lengthms, int pinnum){
  for (int x=0; x<times;x++) {
    digitalWrite(pinnum, HIGH);
    delay (lengthms);
    digitalWrite(pinnum, LOW);
    delay(lengthms);
      }
}
