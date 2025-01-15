#include <math.h>

double cosineArray[361] = {0};

double takeCosine(int a){
  //convert degree to radian
  double radian = a*M_PI/180;
  double cosineValue = cos(radian);
  return cosineValue;
}

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < 361; i++){
    double input  = takeCosine(i);
    cosineArray[i] = takeCosine(i);
    Serial.println(input, 2);
  }
}

void loop() {

}
