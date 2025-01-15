int arraytest[11] = {0,2,3,2,5,6,2,1,2,3,4};
void setup() {
  Serial.begin(9600);
  int *ptr = arraytest;
  ptr = ptr + 50;
  int fmax = 0;
  int smax = 0;
  for (int i = 0; i <= 10; i++){
    if (arraytest[i] >= arraytest[i+1] && arraytest[i] >= arraytest[i-1]){
      fmax++;
    }
    if (fmax == 2){
      smax = arraytest[i];
      fmax = -50;
    }
  }
  *ptr = smax;


}

void loop() {
  // put your main code here, to run repeatedly:

}
