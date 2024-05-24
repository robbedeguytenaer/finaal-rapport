#include <ArduinoBLE.h>

int led = 13;
const int BLE_SCAN_TIME_MS = 3000; // Scan time in milliseconds
const char* SLAVE_NAME = "SlaveDevice";
const int TOLERANCE = 1; // Tolerantie voor RSSI-waarde

const int NUM_SAMPLES = 10;
int rssiSamples[NUM_SAMPLES];
int sampleIndex = 0;

int mappedRSSI = 0;

// Functie om RSSI-waarde om te zetten naar bereik van 0 tot 100
int mapRSSI(int rssi) {
  // Pas deze waarden aan op basis van jouw specifieke situatie
  const int RSSI_MIN = -200; // Minimale RSSI-waarde
  const int RSSI_MAX = -10;  // Maximale RSSI-waarde
  return map(rssi, RSSI_MIN, RSSI_MAX, 0, 100);
}

// Functie voor het verkrijgen van het gemiddelde van de RSSI-waarden
int getAverageRSSI(int newRSSI) {
  rssiSamples[sampleIndex] = newRSSI;
  sampleIndex = (sampleIndex + 1) % NUM_SAMPLES;

  int sum = 0;
  for (int i = 0; i < NUM_SAMPLES; i++) {
    sum += rssiSamples[i];
  }
  return sum / NUM_SAMPLES;
}

void setup() {
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  while (!Serial);
  if (!BLE.begin()) {
    Serial.println("Starting BLE failed!");
    while (1);
  }
}

void loop() {

  digitalWrite(led, LOW);
  BLE.scanForName(SLAVE_NAME, BLE_SCAN_TIME_MS);
  BLEDevice peripheral = BLE.available();

  if (peripheral) {
    int rssi = peripheral.rssi();
    int avgRSSI = getAverageRSSI(rssi);
    mappedRSSI = mapRSSI(avgRSSI);
    Serial.print("Mapped RSSI from slave: ");
    Serial.println(mappedRSSI);
    if (mappedRSSI > 85) {
      Serial.println("afgetikt");
      digitalWrite(led, HIGH);
    }
  }

  delay(100);
}
