#include <IRremote.h>

#define IR_RECEIVE_PIN 7

#define IR_BUTTON_1 12
#define IR_BUTTON_2 24
#define IR_BUTTON_3 94
#define IR_BUTTON_PLAY_PAUSE 64

const int RED_PIN = 9; // Pin voor rode LED
const int GREEN_PIN = 10; // Pin voor groene LED
const int BLUE_PIN = 11; // Pin voor blauwe LED

void setup() {
  Serial.begin(9600);
  IrReceiver.begin(IR_RECEIVE_PIN);

  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  }


void loop() {
  if (IrReceiver.decode()) {
    IrReceiver.resume();
    int command = IrReceiver.decodedIRData.command;
    switch (command) {
      case IR_BUTTON_1: {   // Knop 1 gedrukt, zet de LED rood
        setColor(255, 0, 0); // Rood
        Serial.println("Pressed on button 1");
        delay(100);
        break;
      }
      case IR_BUTTON_2: {  // Knop 2 gedrukt, zet de LED blauw
        setColor(0, 0, 255); // Blauw
        Serial.println("Pressed on button 2");
        delay(100);
        break;
      }
      case IR_BUTTON_3: {
        setColor(0, 255, 0); // Groen
        Serial.println("Pressed on button 3");
        delay(100);
        break;
      }
      case IR_BUTTON_PLAY_PAUSE: {
        Serial.println("Pressed on button play/pause");
        break;
      }
      default: {
        setColor(255, 255, 255);
        Serial.println("uitgeschakelt");
        delay(100);
      }
    }
  }
}



void setColor(int red, int green, int blue) {
  analogWrite(RED_PIN, red);
  analogWrite(GREEN_PIN, green);
  analogWrite(BLUE_PIN, blue);
}