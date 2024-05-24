// Pinconfiguratie
const int trigPin = 9; // Pin voor het trigger-signaal van de ultrasone sensor
const int echoPin = 10; // Pin voor het echo-signaal van de ultrasone sensor
const int ledPin = 13; // Pin voor de LED

// Variabelen
long duration;
int distance;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // Stuur ultrasone puls om afstand te meten
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Meet de duur van het echo-signaal om de afstand te berekenen
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  // Toon de gemeten afstand op de seriële monitor
  Serial.print("Afstand: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Controleer of de afstand minder is dan 5 cm en schakel de LED in
  if (distance < 5) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }

  // Wacht een korte tijd voordat de volgende meting wordt uitgevoerd
  delay(500);
}
