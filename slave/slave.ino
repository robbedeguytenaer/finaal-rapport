#include <ArduinoBLE.h>

const char* DEVICE_NAME = "SlaveDevice";

void setup() {
  Serial.begin(9600);
  while (!Serial);
  if (!BLE.begin()) {
    Serial.println("Starting BLE failed!");
    while (1);
  }
  BLE.setLocalName(DEVICE_NAME);
  BLE.advertise();
}

void loop() {
  delay(100);
}
