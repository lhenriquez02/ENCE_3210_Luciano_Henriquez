/**
 * @file exerciselab3.ino
 * @brief Performs 3 different tasks
 */
/// Generates macros
#define BUTTON 2
#define GREEN 4
#define RED 5

///Timer values
#define TIMER0_VALUE 125
#define TIMER1_VALUE 6250
///Initializes some variables that will be affected by peripherals
volatile int counter = 0;
volatile int timer = 0;

void setup() {
  ///Serial monitor intialized at 9600 baud
  Serial.begin(9600);
  ///initializes the pina
  pinMode(BUTTON, INPUT);
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  ///Creates interrupts my manually adjusting registers
  noInterrupts();
  TCCR1A = 0;
  TCCR1B = 0;
  OCR1A = TIMER1_VALUE;
  TCCR1B |= (1<<WGM12);
  TCCR1B |= (1<<CS12);
  TIMSK1 |= (1<<OCIE1A);
  ///Using a second timer for the green blinking
  TCCR0A = 0; /// Zeroes the TCCR0A and TCCRoB registers
  TCCR0B = 0;
  OCR0A = TIMER0_VALUE; /// sets the reset threshold to 125
  TCCR0A |= (1<<WGM01); /// Puts timer0 in CTC mode
  TCCR0B |= (1<<CS02); /// sets the prescalar to 1/1024
  TCCR0B |= (1<<CS00);
  TIMSK0 |= (1<<OCIE0A); /// Creates interrupt
  interrupts();

}

void loop() {
  ///Main task, prints test to serial monitor every 3 seconds
  if (timer%3 == 0){
    Serial.println("test");
    ///Loop to prevent a large number of strings being printed, since timer stays at 0 for one second
    while (true){
      if (timer%3 != 0){
        break;
      }
    }
  }
  


}

///Isr function to control red led
ISR(TIMER1_COMPA_vect){
  if (digitalRead(BUTTON)){
    digitalWrite(RED, HIGH);
  } else{
    digitalWrite(RED, LOW);
  }
  digitalWrite(GREEN, LOW); 
}
///ISR function to control the green led and the string output
ISR(TIMER0_COMPA_vect){
  counter++;
  /// 125*125 = 16M/1024. So when counter goes up by 125, 1 second will have passed
  if (counter == 125){
    digitalWrite(GREEN, HIGH);
    timer++;
    if (timer == 100){
      timer = 0;
    }
    counter  = 0;
  }
}



