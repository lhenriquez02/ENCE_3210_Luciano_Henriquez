#define BUTTONONE 2
#define BUTTONTWO 3
#define LED_GREEN 4
#define LED_RED 5
#define LED_BLUE 6

volatile unsigned long savedTime = 0;
const unsigned long givenDelay = 250;


int buttonOneCounter = 0;
int buttonTwoCounter = 0; 
void setup() {
  Serial.begin(9600);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(BUTTONONE, INPUT);
  pinMode(BUTTONTWO, INPUT);

  attachInterrupt(digitalPinToInterrupt(BUTTONONE), isr_buttonone, RISING);
  attachInterrupt(digitalPinToInterrupt(BUTTONTWO), isr_buttontwo, RISING);

}

void loop() {
  if (buttonOneCounter > buttonTwoCounter){
    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_BLUE, LOW);
    digitalWrite(LED_GREEN, HIGH);
    
    
  } else if (buttonTwoCounter > buttonOneCounter){
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_BLUE, LOW);
    digitalWrite(LED_RED, HIGH);
    
  }
  else{
    digitalWrite(LED_GREEN,LOW);
    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_BLUE, HIGH);
  }
  

}

void isr_buttonone(){
  unsigned long time = millis();
  if (time - savedTime > givenDelay){
    buttonOneCounter++;
    Serial.print("Number of times pressing first button: ");
    Serial.println(buttonOneCounter);
    Serial.print("Number of times pressing second button: ");
    Serial.println(buttonTwoCounter);
  }
  savedTime = time;
}

void isr_buttontwo(){
  unsigned long time = millis();
  if (time - savedTime > givenDelay){
    buttonTwoCounter++;
    Serial.print("Number of times pressing first button: ");
    Serial.println(buttonOneCounter);
    Serial.print("Number of times pressing second button: ");
    Serial.println(buttonTwoCounter);
  }
  savedTime = time;
  
}