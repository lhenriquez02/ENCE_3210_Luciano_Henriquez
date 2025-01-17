/**
 * @file problem3lab1soln.ino
 * @brief Cycles between turning on certain LEDS according to user input.
 */

 /// Macro generation
#define GREEN 4
#define RED 5
#define BLUE 6
#define BUTTON 2
 
void setup() {
  /// Initializing the output and input pins, ensuring all LEDs are turned off at the start
  pinMode(GREEN, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(BUTTON, INPUT);
  digitalWrite(RED, LOW);
  digitalWrite(GREEN, LOW);
  digitalWrite(BLUE, LOW);
}

void loop() {
  /// Debounce delay
  delay(100);
  /// If there is every input detected, it enters this while loop, which should keep cycling until user input is detected.
  if (digitalRead(BUTTON)){
    delay(250);
    while (1){
      digitalWrite(RED, HIGH);
      delay(250);
      /// Every break in this section is there to give the user the most number of opportunities to interrupt program as soon as second input is detected.
      if (digitalRead(BUTTON)){
        break;
      }
      digitalWrite(GREEN, HIGH);
      delay(250);
      if (digitalRead(BUTTON)){
        break;
      }
      digitalWrite(BLUE, HIGH);
      delay(250);
      if (digitalRead(BUTTON)){
        break;
      }
      digitalWrite(RED, LOW);
      delay(250);
      if (digitalRead(BUTTON)){
        break;
      }
      digitalWrite(GREEN, LOW);
      delay(250);
      if (digitalRead(BUTTON)){
        break;
      }
      digitalWrite(RED, HIGH);
      delay(250);
      if (digitalRead(BUTTON)){
        break;
      }
      digitalWrite(BLUE, LOW);
    }
    
  }



}
