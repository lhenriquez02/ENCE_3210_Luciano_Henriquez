/**
 * @file problem4lab2.ino
 * @brief Creates new array by operating on elements of existing aray
 */
#define BUTTON_1 2
/// Initializing the given array and the result array y. Initailizes a counter.
int x[10] = {1,2,3,4,5,6,7,8,9,10};
volatile int y[10] = {0};
volatile int counter = 0;

void setup() {
  /// Initializes serial monitor and creates ISR
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(BUTTON_1), isrButton, RISING);
  /// Does nothing until a button is pressed. 
  while (true){
    if (counter != 0){
      break;
    }
  }
  /// each element of the array y is returned to serial monitor.
  for (int i = 0; i<10; i++){
    Serial.println(y[i]);
  }

}

void loop() {
  

}
/**
 * @brief Amends the contents of array y by operating on elements of array x
 * @return void
 */
void isrButton(){
  for (int i = 0; i < 10; i++){
    y[i] = 2*x[i]-x[i-1];
  }
  counter++;
}