#include "symbols.h"

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


#define TIMER1_VALUE 62500
#define BATTERYVOLTAGE A0
#define PANELVOLTAGE A1
#define mosfetBattery 12
#define mosfetPanel 11
#define chargeBatteryPin 10

typedef enum {
  BATTERY,
  PANEL,
  CHARGING
} chargeStatus;

chargeStatus currentStatus = BATTERY;
chargeStatus *current = &currentStatus;


double readBatteryVoltage(){
  return 5*analogRead(BATTERYVOLTAGE)/1023;
}

double readPanelVoltage(){
  return 5*analogRead(PANELVOLTAGE)/1023;
}

void pickPowerSource(chargeStatus *choice){
  double batteryVoltage = readBatteryVoltage();
  double panelVoltage = readBatteryVoltage();
  // double batteryVoltage = 3;
  // double panelVoltage = 4;
  switch(*choice){
    case BATTERY:
      digitalWrite(mosfetPanel, LOW);
      digitalWrite(mosfetBattery, HIGH);
      if (panelVoltage >= 2.5 && batteryVoltage > panelVoltage){
        *choice = PANEL;
      } else if (batteryVoltage < panelVoltage){
        *choice = CHARGING;
      }
      break;
    case PANEL:
      digitalWrite(mosfetBattery, LOW);
      digitalWrite(mosfetPanel, HIGH);
      if (panelVoltage < 2.5 && batteryVoltage > panelVoltage){
        *choice = BATTERY;
      } else if (batteryVoltage<panelVoltage){
        *choice = CHARGING;
      }
      break;
    case CHARGING:
      digitalWrite(mosfetBattery, LOW);
      digitalWrite(mosfetPanel, HIGH);
      digitalWrite(chargeBatteryPin, HIGH);
      if (batteryVoltage > 4.9 && panelVoltage>=2.5){
        *choice = PANEL;
      } else if (batteryVoltage > 4.9 && panelVoltage<2.5){
        *choice = BATTERY;
      }


      break;

  }
}

void chargeAnimation(int i){
    display.clearDisplay();
    display.setCursor(8,10);
    display.drawBitmap(0,0,images[i], SCREEN_WIDTH, SCREEN_HEIGHT, WHITE);
    display.print("CHARGING");
    display.display();
    delay(100);
}

void drawOLED(chargeStatus *choice){
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(8,10);
  if (*choice==BATTERY){
    display.drawBitmap(0,0,images[1], SCREEN_WIDTH, SCREEN_HEIGHT, WHITE);
    display.print("BATTERY");
  } else if (*choice == PANEL){
    display.drawBitmap(0,0,images[0], SCREEN_WIDTH, SCREEN_HEIGHT, WHITE);
    display.print("SOLAR PANEL");
  } else {
    chargeAnimation(4);
    chargeAnimation(3);
    chargeAnimation(2);
    chargeAnimation(1);
    delay(300);

    
  }

}





void setup() {
  Serial.begin(9600);
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(2000);
  // Clear the buffer
  display.clearDisplay();

  pinMode(BATTERYVOLTAGE, INPUT);
  pinMode(PANELVOLTAGE, INPUT);
  pinMode(chargeBatteryPin, OUTPUT);
  pinMode(mosfetBattery, OUTPUT);
  pinMode(mosfetPanel, OUTPUT);



}

void loop() {
  display.clearDisplay();
  pickPowerSource(current);
  drawOLED(current);
  display.display();

  

}


