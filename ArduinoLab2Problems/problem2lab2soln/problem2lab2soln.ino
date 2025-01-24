/**
 * @file problem2lab2.ino
 * @brief Cycles LEDs whenever requested
 */
#define BUTTONONE 3
#define LED_GREEN 4
#define LED_RED 5
#define LED_BLUE 6

///Creating a boolean that will be modified by ISR

volatile bool restart = false;
///Main body
void setup() {
  /// Initializing LEDs and the button, as well as the ISR
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  pinMode(BUTTONONE, INPUT);
  attachInterrupt(digitalPinToInterrupt(BUTTONONE), isr_buttonone, RISING);
  ///Loop to prevent any activity until requested by button press
  while (true){
    if (restart){
      break;
    }
  }
}

void loop() {
  /// Sets restart to false and initializes all LEDs to low state
  restart = false;
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_BLUE, LOW);
  /// While loop that governs the cycling. As long as interrupt service routine is not triggered, Leds will cycle in prescribed manner.
  while (true){
    digitalWrite(LED_RED, HIGH);
    delay(500);
    /// ISR changes the value of restart. If it is triggered, the loop begins again. This is true no matter where in the cycle this occurs
    if (restart){
      break;
    }
    digitalWrite(LED_GREEN, HIGH);
    delay(500);
    if (restart){
      break;
    }
    digitalWrite(LED_BLUE, HIGH);
    delay(500);
    if (restart){
      break;
    }
    digitalWrite(LED_RED, LOW);
    delay(500);
    if (restart){
      break;
    }
    digitalWrite(LED_GREEN, LOW);
    delay(500);
    if (restart){
      break;
    }
    digitalWrite(LED_RED, HIGH);
    delay(500);
    if (restart){
      break;
    }
    digitalWrite(LED_BLUE, LOW);
    if (restart){
      break;
    }
  }

}

/**
 * @brief Changes boolean value to true if button is pressed.
 * @return void
 */
void isr_buttonone(){
  restart = true;
}
