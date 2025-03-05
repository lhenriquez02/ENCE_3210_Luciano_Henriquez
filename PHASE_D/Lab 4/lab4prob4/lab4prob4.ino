/**
 * @file lab4prob4.ino
 * @brief Code for a fan embedded system, which monitors temperature in Fahrenheit (0-102.3 degrees simulated using potentiometer) and adjusts fan speed (LED intensity)
 */


/// Initialization of values
#define TIMER0_VALUE 255
#define TEMP_SENSOR A0
#define ONOFF_BUTTON 2
#define SENSITIVITY 3
#define FAN 9

volatile float gTotal = 0;
volatile int gCounter = 0;
volatile float currentTemp = 0;
volatile int overflowCounter = 0;
const unsigned long givenDelay = 50;
volatile unsigned long savedTime1 = 0;
volatile unsigned long savedTime2 = 0;
volatile bool onOffState = 0;
volatile int gSensitivity = 0;


float getTemperature(){
  /**
 * @brief Gets the temperature using ADC module
 *
 * This function takes no inputs, and returns the temperature of the room, which is being simulated by a potentiometer.
 *
 * @param None
 * @return Temperature in range from 0-102.3 degrees F
 */

  volatile float result = analogRead(TEMP_SENSOR);
  return result / 10;
}

float averageTemp(float temp){
  /**
 * @brief takes the average temperature
 * 
 * This function takes the sum of 100 temperatures as input, and returns the average of this sum
 * 
 * @param temp Sum of 100 temperatures
 * @return The average temperature
 */
  return temp / 100;
}

void fanSpeed(float currentTemp, int val){
/**
 * @brief Sets the fan speed
 * 
 * This function takes the current temperature of the room as input as well as the sensitivity mode selected by the user, and returns what the fan speed should be.
 * 
 * @param currentTemp Temperature of the room
 * @param val Selected multiplier which determines intensity, the multiplier is determined by the mode selected by user in sensitivitySelector function.
 * @return Desired fan speed having taken parameters into account
 */
  int intensity = (int)((currentTemp/(102.30))*val);
  analogWrite(FAN, intensity);
}

int sensitivitySelector(){ 
/**
 * @brief Selects the sensitivity mode.
 * 
 * This function relies on button ISR to determine the sensitivity mode.
 * 
 * @param None
 * @return Multiplier value which is inputted in fanSpeed function
 */
  if (gSensitivity == 0){
    return 50;
  } else if (gSensitivity == 1){
    return 150;
  } else{
    return 255;
  }

}

void setup() {
  /// Initialize serial monitor
  Serial.begin(9600);
  /// Attach interrupts for two buttons located at pins 2 and 3
  attachInterrupt(digitalPinToInterrupt(ONOFF_BUTTON), ISR_ONOFF, RISING);
  attachInterrupt(digitalPinToInterrupt(SENSITIVITY), ISR_SENSITIVITY, RISING);

  /// Sets up the timer.
  noInterrupts(); // Disable interrupts during setup
  TCCR1A = (1 << COM1A1) | (1 << WGM10);  // Non-inverting mode and  8-bit PWM
  TCCR1B = (1 << WGM12) | (1 << CS12);    // Sets prescaler to 256 and sets to Fast PWM mode
  OCR1A = TIMER0_VALUE;  // Set the TOP value for 245 ~ 250 Hz PWM
  ///Sets up the 50 ms timer that will take 100 samples every 5 seconds.
  TCCR0A = 0;
  TCCR0B = 0;
  OCR0A = TIMER0_VALUE;  // 50ms interval
  TCCR0A = (1 << WGM01);  // Set CTC mode
  TCCR0B = (1 << CS02) | (1 << CS00);  // Prescaler 1024
  TIMSK0 |= (1 << OCIE0A);  // Enable Timer0 Compare Match A interrupt
  interrupts(); // Enable interrupts

}

void loop() {
  /// If on, then proceed, otherwise, turn fan off
  if (onOffState){
    fanSpeed(currentTemp,sensitivitySelector());
  }else{
    analogWrite(FAN, 0);
  }
}

ISR(TIMER0_COMPA_vect){
  /// Overflow set to 3, because 3*16ms is almost 50 ms, so it should sample at roughly 100 temperature values per 5 seconds.
  if (overflowCounter == 3){
    if (gCounter == 100){
      currentTemp = averageTemp(gTotal); ///set the global variable currentTemp to the average after 5 seconds
      /// Reset all parameters.
      gTotal = 0;
      gCounter = 0;
    }
    /// Otherwise just add another temperature to the total
    float temp = getTemperature();
    // Serial.print(gCounter);
    // Serial.println(gTotal);
    gTotal += temp;
    gCounter++;
    overflowCounter = 0;
  }
  overflowCounter++;
}

void ISR_ONOFF(){
  /// Debounce procedure
  unsigned long time1 = millis();
  if (time1 - savedTime1 > givenDelay){
    onOffState = !onOffState; // Switch on off state if button is pressed
  }
  savedTime1 = time1;
}

void ISR_SENSITIVITY(){
  ///Debounce procedure
  unsigned long time2 = millis();
  if (time2-savedTime2 > givenDelay){
    if (gSensitivity == 2){
      gSensitivity = 0; // make the sensitivity value an integer mod 3
    } else{
      gSensitivity++; // if the sensitivity value is not 2, increase.
    }
  }
}