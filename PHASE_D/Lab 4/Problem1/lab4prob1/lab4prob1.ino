#include <math.h>

#define BITSIZE 14

float Vref = 3;
float Vin = 0.42;
float thresh;
float quantized = 0;
float multFactor;
int count;
int bitval;
int bits[BITSIZE];
int comparisonArray[BITSIZE] = {0};

uint16_t updateRef(int arr[],int size){
  uint16_t result = 0;
  for (int i = 0; i < size; i++){
    int power = size-1-i;
    double rawfactor = pow(2,power) + 0.1;
    uint16_t factor = (uint16_t)rawfactor;
    result += ((uint16_t)arr[i])*factor;
    // Serial.println(result);
  }
  return result;
}


void setup() {
  Serial.begin(9600);
  multFactor = Vref/(pow(2,BITSIZE));

  for (count = 0; count < BITSIZE; count++) {
    comparisonArray[count] = 1;
    Vref = multFactor*updateRef(comparisonArray,BITSIZE);
    Serial.println(Vref);
    if (Vin >= Vref) {
      bitval = 1;
    } else {
      bitval = 0;
      comparisonArray[count] = 0;
    }

    bits[count] = bitval;
    quantized += 2 * Vref * bitval;
  }

}

void loop() {
    // Infinite loop
    while (1);
}
