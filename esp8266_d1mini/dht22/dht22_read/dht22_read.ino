// DHT22 Temp/Humidity Sensor connected to Makerfocus D1 mini
// Reads temp and humidity every 5 seconds and prints them to Serial
#include "DHT.h"

#define DHTPIN 5 // mapped to D1 on the Makerfocus D1 mini

float humidity, temperature;

DHT dht(DHTPIN, DHT22);

void setup()
{
  pinMode(DHTPIN, INPUT_PULLUP);
  Serial.begin(9600);
  delay(10);
  Serial.print("DHT init ... ");
  dht.begin();
  Serial.println("successful!");
}

void loop () {
  int chk = dht.read(DHTPIN);

  humidity = dht.readHumidity();
  temperature = dht.readTemperature();

  // Check if any reads failed and exit early (to try again).
  if (isnan(humidity) || isnan(temperature)) {
    Serial.print("Error reading DHT Sensor: Return code: ");
    Serial.println(chk);
    return;
  }

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" *C ");

  delay(5000);
}
