//Libraries
#include <DHT.h>

//Constants
#define DHTPIN 7        //DHT 1 data pin on arduino pin 7
#define DHTPIN2 6       //DHT 2 data pin on arduino pin 6
#define DHTTYPE DHT22   //DHT 22 is being used (dht pin 1 is 5V dht pin 4 is GND, dht pin 2 is data pin)
DHT dht(DHTPIN, DHTTYPE);
DHT dht2(DHTPIN2, DHTTYPE);

//Variables
float hum, hum2;  //Stores humidity value
float temp, temp2; //Stores temperature value

void setup() {
  Serial.begin(9600);
  dht.begin();
  dht2.begin();
}

void loop() {
  delay(2000);
  //Read data and store it to variables hum and temp
  hum  = dht.readHumidity();
  temp = dht.readTemperature();
  hum2  = dht2.readHumidity();
  temp2 = dht2.readTemperature();
  //Print temp and humidity values to serial monitor
  Serial.print("Humidity: ");
  Serial.print(hum);
  Serial.print("/");
  Serial.print(hum2);
  Serial.print(" %, Temp: ");
  Serial.print(temp);
  Serial.print("/");
  Serial.print(temp2);
  Serial.println(" Celsius");
  delay(10000); //Delay 2 sec.
}
