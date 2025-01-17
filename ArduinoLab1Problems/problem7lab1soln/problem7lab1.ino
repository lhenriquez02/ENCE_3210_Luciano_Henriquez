/**
 * @file problem7lab1.ino
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
int counter  = 0;
int* resultArray = (int*)malloc(10 * sizeof(int));

void setup() {
  /// Initializing serial monitor at 9600 baud/
  Serial.begin(9600);
  /// Initializing the pins
  pinMode(GREEN, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(BUTTON_1, INPUT);
  pinMode(BUTTON_2, INPUT);
  /// 10 iterations for each respective element operation
  for (int i = 0; i < 10; i++){
    /// Operation selector, can only break when second button is pressed, and counter cannot be 0
    while (!digitalRead(BUTTON_2) | counter == 0){
      if (digitalRead(BUTTON_1)){
        delay(250);
        counter++;
      } 
      /// LED turns on depending on the mode
      if (counter == 1){
        digitalWrite(RED, HIGH);
      }
      if (counter == 2){
        digitalWrite(RED, LOW);
        digitalWrite(GREEN, HIGH);
      }
      if (counter == 3){
        digitalWrite(GREEN, LOW);
        digitalWrite(BLUE, HIGH);
      }
      /// Modular treatment of counter, counter can only go up to 3
      if (counter > 3 | counter == 0){
        digitalWrite(RED, LOW);
        digitalWrite(GREEN, LOW);
        digitalWrite(BLUE, LOW);
        counter = 0;
      }
    }
    ///Debounce delay
    delay(250);
    /// Element operation depending on mode.
    if (counter==1){
      resultArray[i]=firstArray[i]+secondArray[i];
    }
    if (counter == 2){
      resultArray[i]=firstArray[i]-secondArray[i];
    } 
    if (counter == 3){
      resultArray[i]=firstArray[i]*secondArray[i];
    }
    counter = 0;
    }
  ///Verifying the contents of the result array
  for (int j = 0; j<10; j++){
    Serial.println(resultArray[j]);
  }
  delay(250);
  /// All lights turned on when program succeeds
  digitalWrite(RED, HIGH);
  digitalWrite(GREEN, HIGH);
  digitalWrite(BLUE, HIGH);
  /// Memory freed
  free(resultArray);
}

void loop() {
  

}
