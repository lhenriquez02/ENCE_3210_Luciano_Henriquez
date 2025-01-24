/**
 * @file problem3lab2.ino
 * @brief Does operations on two arrays
 */
/// Defining macros
#define GREEN 4
#define RED 5
#define BLUE 6
#define BUTTON_1 2
#define BUTTON_2 3
/// iniitalizing the arrays. Creating a dynamically allocated array using malloc.
int firstArray[10] = {1,2,3,4,5,6,7,8,9,10};
int secondArray[10] = {1,2,3,4,5,6,7,8,9,10};
int* resultArray = (int*)malloc(10 * sizeof(int));
volatile int modeSelector = 0;
volatile int confirm = 0;
/// Initializing delay
volatile unsigned long savedTime = 0;
const unsigned long givenDelay = 250;


void setup() {
  ///Initialization
  Serial.begin(9600);
  pinMode(GREEN, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(BUTTON_1, INPUT);
  pinMode(BUTTON_2, INPUT);
  attachInterrupt(digitalPinToInterrupt(BUTTON_1), isrButton1, RISING);
  attachInterrupt(digitalPinToInterrupt(BUTTON_2), isrButton2, RISING);
  /// Main body to calculate each element of the array. Each element in new array should be created via unique selecting of operation on elements of exisitng two arrays
  for (int i = 0; i < 10; i++){
    /// Resets some important variables
    confirm = 0;
    modeSelector = 0;
    digitalWrite(GREEN, LOW);
    digitalWrite(BLUE, LOW);
    /// Allows user to select mode using ISR, turns on respective light for each operation. Only breaks when the second button is pressed
    while (true){
      if (modeSelector == 0){
        digitalWrite(BLUE, LOW);
        digitalWrite(GREEN, LOW);
        digitalWrite(RED, HIGH);
      } else if (modeSelector == 1){
        digitalWrite(GREEN, HIGH);
        digitalWrite(RED, LOW);
        digitalWrite(BLUE, LOW);
      } else if (modeSelector == 2){
        digitalWrite(GREEN, LOW);
        digitalWrite(BLUE, HIGH);
        digitalWrite(RED, LOW);
      } 
      /// variable confirm only changes when second ISR occurs.
      if (confirm != 0){
        break;
      }
    }
    /// COnditions for selecting operation
    if (modeSelector == 0){
      resultArray[i] = firstArray[i]+secondArray[i];
    } else if (modeSelector == 1){
      resultArray[i] = firstArray[i]-secondArray[i];
    } else{
      resultArray[i] = firstArray[i]*secondArray[i];
    }
    delay(500);
  }
  digitalWrite(GREEN, LOW);
  digitalWrite(RED, LOW);
  digitalWrite(BLUE, LOW);
  free(resultArray);
}



void loop() {
  // put your main code here, to run repeatedly:

}
/**
 * @brief Changes modeSelector to appropriate mode
 * @return void
 */
void isrButton1(){
  unsigned long time = millis();
  if (time-savedTime > givenDelay){
    if (modeSelector == 2){
      modeSelector = 0;
    } else{
      modeSelector++;
    }
  }
  savedTime = time;
}
/**
 * @brief Changes confirm to exit while loop
 * @return void
 */
void isrButton2(){
  confirm++;
}
