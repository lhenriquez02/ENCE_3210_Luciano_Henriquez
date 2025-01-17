/**
 * @file problem1lab1soln.ino
 * @brief Finds twice the square of given integer, stores it for the first 512 integers in array.
 */

/**
 * @brief Finds twice square of integer
 * 
 * This function returns twice the square of integer
 * 
 * @param a Given integer.
 * @return Twice square of a
 */
unsigned long twiceSquare(int a){
  return 2*a*a;
}

/// Creating array with all zeroes
int integerArray[512]={0};

void setup() {
  Serial.begin(9600);
  /// Updates array with twice square of each number from 0 to 511
  for (int i = 0; i < 512l; i++){
    unsigned long result = twiceSquare(i);
    integerArray[i] = result;
    Serial.print(result);

  }

}

void loop() {
  // put your main code here, to run repeatedly:

}
