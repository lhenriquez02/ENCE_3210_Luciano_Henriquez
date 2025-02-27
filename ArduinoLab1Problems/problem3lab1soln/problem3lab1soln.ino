/**
 * @file problem3lab1soln.ino
 * @brief takes an array, finds the second highest element, and returns to the next memory location.
 */
 
 #include <stdlib.h>
 #include <time.h>

/// Any array works here, this is a test array.
int testArray[50] = {0};

/**
 * @brief Finds the second highest element in a given integer array
 * 
 * This function takes an integer array and its size as inputs, and returns its second largest element,
 * 
 * @param initialArray Given integer array.
 * @param size size of the array.
 * @return Second largest element.
 */
int findSecondMax(int initialArray[], int size){
  /// Initializes empty array that will store the largest two elements of subarray [0::i] at any given time
  int topTwo[2] = {0};
  /// Updates the array that stores the two largest elements at any given time
  for (int i = 0; i < size; i++ ){
    /// Condition to update first element. If the ith number in the array is larger than the first element, the first element gets bumped to the right, with the ith element taking its place.
    if (initialArray[i]>topTwo[0]){
      topTwo[1] = topTwo[0];
      topTwo[0] = initialArray[i];
    } else{
      /// Array only need be updated if the ith element is larger than 2nd element.
      if (initialArray[i]>topTwo[1]){
        topTwo[1] = initialArray[i];
      }
    }
  }
  /// Return the second element of the array, which is the second largest element of the input array.
  return topTwo[1];
}

void setup() {
  /// Initializes the serial monitor at 9600 baud.
  Serial.begin(9600); 
  /// Fills array with 50 pseudorandom numbers. 
  srand(time(NULL));
  int random_number = 0;
  for (int i = 0; i < 50;i++){
    random_number = rand();
    testArray[i] = random_number;
    /// Serial.println(testArray[i]);

  }

  /// declaring a pointer that points to first element of given array
  int* ptr = testArray;
  /// Finds the size of the array using sizeof function
  int arraySize  = sizeof(testArray) / sizeof(int);
  /// Moves pointer to the memory location right after the array
  ptr = ptr+arraySize;
  /// Declares a variable which will be stored at memory location
  int secondMax = findSecondMax(testArray, arraySize);
  /// Prints to serial monitor to verify correctness
  Serial.println(secondMax);
  /// Stores the second largest element to the memory location after array.
  *ptr = secondMax;
  
  }

void loop() {
  // put your main code here, to run repeatedly:

}