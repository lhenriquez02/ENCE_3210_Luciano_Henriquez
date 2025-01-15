/**
 * @file problem4lab1.ino
 * @brief Reads an array of characters. If, during the scan, the program detects an R, G, or B, it turns 
 * on a red, green, or blue light, respectively
 */

#define RED 10
#define GREEN 11
#define BLUE 12

/// Test array with 10 elements
char testArray[10] = {'R','Z','G','D','B','R','G','K','L','B'};

void setup() {
  /// Initializes serial monitor at 9600 baud.
  Serial.begin(9600);
  /// Gets array size
  int arraySize = sizeof(testArray) / sizeof(char);
  /// Initializes the counters
  int redCounter = 0;
  int greenCounter = 0;
  int blueCounter = 0;
  /// Initializes certain digital IO ports as outputs to turn on LED.
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  /// Loop that searches through the array.
  for (int i = 0; i < arraySize; i++){
    /// Condition to turn red LED on
    if (testArray[i] == 'R'){
      digitalWrite(RED, HIGH);
      delay(200);
      digitalWrite(RED, LOW);
      redCounter++;
    }
    /// Condition to turn green LED on
    if (testArray[i] == 'G'){
      digitalWrite(GREEN, HIGH);
      delay(200);
      digitalWrite(GREEN, LOW);
      greenCounter++;
    }
    /// Condition to turn blue LED on
    if (testArray[i] == 'B'){
      digitalWrite(BLUE, HIGH);
      delay(200);
      digitalWrite(BLUE, LOW);
      blueCounter++;
    } else {
      /// Delay so that each letter takes the same amount of time to be scanned.
      delay(200);
    }

  }
  /// Prints results to serial monitor
  Serial.print("The number of Rs is: ");
  Serial.println(redCounter);
  Serial.print("The number of Gs is: ");
  Serial.println(greenCounter);
  Serial.print("The number of Bs is: ");
  Serial.println(blueCounter);

  

}

void loop() {
  // put your main code here, to run repeatedly:

}
