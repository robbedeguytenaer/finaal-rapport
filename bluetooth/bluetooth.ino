#include <ArduinoBLE.h>

#define BLE_DEVICE_NAME "Nano33IoT"
#define SCAN_DURATION 5 // Duur van het scannen in seconden

BLEService distanceService("19B10000-E8F2-537E-4F6C-D104768A1214"); // Uw service UUID hier
BLECharacteristic distanceCharacteristic("19B10001-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite, 4); // Uw karakteristieke UUID hier

int previousRSSI = 0;

void setup() {
  Serial.begin(9600);

  if (!BLE.begin()) {
    Serial.println("Starting BLE failed!");
    while (1);
  }

  BLE.setLocalName(BLE_DEVICE_NAME);
  BLE.setAdvertisedService(distanceService);

  distanceService.addCharacteristic(distanceCharacteristic);
  BLE.addService(distanceService);

  BLE.advertise();

  Serial.println("BLE Peripheral device started, waiting for connections...");
}

void loop() {
  BLEDevice central = BLE.central();

  if (central) {
    Serial.print("Connected to central: ");
    Serial.println(central.address());

    while (central.connected()) {
      int rssi = central.rssi();

      if (rssi != previousRSSI) {
        Serial.print("RSSI: ");
        Serial.println(rssi);

        // Convert RSSI to distance (just a simple approximation)
        float distance = calculateDistance(rssi);

        Serial.print("Estimated distance: ");
        Serial.print(distance);
        Serial.println(" meters");

        // Stuur de afstand via BLE naar de centrale
        distanceCharacteristic.writeValue((byte*)&distance, sizeof(distance));

        previousRSSI = rssi;
      }

      delay(1000);
    }

    Serial.println("Disconnected");
  }
}

float calculateDistance(int rssi) {
  // Afstand berekeningslogica kan worden aangepast op basis van empirische gegevens
  // Hier is een eenvoudige benadering die een afstand in meters geeft
  // op basis van de RSSI-waarde (vereist kalibratie voor nauwkeurige resultaten)
  float distance = exp((abs(rssi) - 59) / (10 * 2.0));

  return distance;
}
