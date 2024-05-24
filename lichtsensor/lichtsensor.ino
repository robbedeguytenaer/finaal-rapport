#define s0 4        //Module pinnen bekabeling
#define s1 5
#define s2 6
#define s3 7
#define out 8

// Pin definities voor RGB LED
const int LED_RED = 9;
const int LED_GREEN = 10;
const int LED_BLUE = 11;

int Red = 0, Blue = 0, Green = 0;  // RGB-waarden

void setup()
{
  pinMode(s0, OUTPUT);    // Pin modi instellen
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(out, INPUT);

  pinMode(LED_RED, OUTPUT);    // Configureer LED pinnen voor uitvoer
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);

  Serial.begin(9600);   // Initialiseer de seriële monitor met baudrate 9600

  digitalWrite(s0, HIGH); // S0/S1 op HIGH/HIGH betekent dat de uitvoerfrequentie wordt geschaald naar 100% (aanbevolen)
  digitalWrite(s1, HIGH); // Laag/Laag betekent uit; Hoog/Laag betekent 20%; Laag/Hoog betekent 2%
}

void loop()
{
  GetColors();    // Voer de functie GetColors uit om de waarden van elk RGB-kleur te verkrijgen

  // Bepaal welke kleur het meest wordt gedetecteerd en pas de RGB LED dienovereenkomstig aan
  if (Red <= 10 && Green <= 10 && Blue <= 10)
  {
    // Als de waarden laag zijn, is het waarschijnlijk wit (alle kleuren zijn aanwezig)
    Serial.println("White");
    analogWrite(LED_RED, 255);
    analogWrite(LED_GREEN, 255);
    analogWrite(LED_BLUE, 255);
  }
  else if (Red < Blue && Red <= Green)
  {
    // Als de rode waarde het laagst is en kleiner is dan 23, is het waarschijnlijk rood
    Serial.println("Red");
    analogWrite(LED_RED, 255);
    analogWrite(LED_GREEN, 0);
    analogWrite(LED_BLUE, 0);
  }
  else if (Blue < Green && Blue < Red) // Drempelwaarde voor blauw verlaagd naar 15
  {
    // Als de blauwe waarde het laagst is, is het waarschijnlijk blauw (handschoenkleur)
    Serial.println("Blue");
    analogWrite(LED_RED, 0);
    analogWrite(LED_GREEN, 0);
    analogWrite(LED_BLUE, 255);
  }
  else if (Green < Red && Green < Blue)
  {
    // Als de groene waarde het laagst is en het verschil tussen groen en blauw acceptabel is, is het waarschijnlijk groen
    Serial.println("Green");
    analogWrite(LED_RED, 0);
    analogWrite(LED_GREEN, 255);
    analogWrite(LED_BLUE, 0);
  }
  else
  {
    // Als de kleur niet wordt herkend, schakel de LED uit
    Serial.println("Unknown");
    analogWrite(LED_RED, 0);
    analogWrite(LED_GREEN, 0);
    analogWrite(LED_BLUE, 0);
  }

  delay(500);  // 2s vertraging, je kunt dit aanpassen als je wilt
}

void GetColors()
{
  // Selecteer de set fotodiodes die wordt gebruikt voor het meten van de kleur
  digitalWrite(s2, LOW);  // Rode set
  digitalWrite(s3, LOW);
  Red = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);  // Meet de duur van het LOW signaal
  delay(20);
  digitalWrite(s3, HIGH);  // Blauwe set
  Blue = pulseIn(out, digitalRead(out) == HIGH ? LOW  : HIGH);
  delay(20);
  digitalWrite(s2, HIGH);  // Groene set
  Green = pulseIn(out,  digitalRead(out) == HIGH ? LOW : HIGH);
  delay(20);
}
