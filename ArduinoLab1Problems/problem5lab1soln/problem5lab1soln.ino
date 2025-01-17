/**
 * @file problem5lab1soln.ino
 * @brief Detects if a pattern is present in given array
 */

///Macro generation
#define GREEN 4
#define RED 5
/// test array generation, with comparison array
char testArray[11] = {'a','b','c','d','e','c','d','f','c','d','f'};
char comparisonArray[3] = {'c','d','f'};
/**
 * @brief Turns on green light if pattern is found in array, Red if not. Returns the number of occurrences of pattern
 * 
 * This function turns on green light if pattern is found in given array, red if not. Return the number of occurrences of pattern
 * 
 * @param arr Given integer array.
 * @param comparatorArray Array storing the pattern.
 * @param size size of arr.
 * @return Number of occurrence of given array.
 */
int patternDetect(char arr[], char comparatorArray[], int size){
  int counter = 0;
  /// Scans in sets of three for pattern in array
  for (int i = 0; i < size; i++){
    if (arr[i-1] == comparatorArray[0] && arr[i] == comparatorArray[1] && arr[i+1] == comparatorArray[2]){
      digitalWrite(GREEN, HIGH);
      counter++;
    }
  }
  if (counter == 0){
    digitalWrite(RED, HIGH);
  }
  return counter;
}

void setup() {
  Serial.begin(9600);
  /// finding size of array
  int arraySize = sizeof(testArray) / sizeof(char);
  pinMode(GREEN, OUTPUT);
  pinMode(RED, OUTPUT);
  digitalWrite(GREEN, LOW);
  digitalWrite(RED, LOW);
  int counter = patternDetect(testArray, comparisonArray, arraySize);
  Serial.println(counter);
}

void loop() {
  // put your main code here, to run repeatedly:

}
