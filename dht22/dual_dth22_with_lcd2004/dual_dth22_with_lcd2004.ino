//Libraries
#include <Wire.h>
#include <DHT.h>
#include <LiquidCrystal_I2C.h>

//Constants
#define DHTPIN 7        //DHT 1 data pin on arduino pin 7
#define DHTPIN2 6       //DHT 2 data pin on arduino pin 6
#define DHTTYPE DHT22   //DHT 22 is being used (dht pin 1 is 5V dht pin 4 is GND, dht pin 2 is data pin)
DHT dht(DHTPIN, DHTTYPE);
DHT dht2(DHTPIN2, DHTTYPE);

//Libraries
#define I2C_ADDR  0x27
#define En_pin    2
#define Rw_pin    1
#define Rs_pin    0
#define D4_pin    4
#define D5_pin    5
#define D6_pin    6
#define D7_pin    7
#define BACKLIGHT_PIN   3

LiquidCrystal_I2C lcd(I2C_ADDR, En_pin, Rw_pin, Rs_pin,
                      D4_pin, D5_pin, D6_pin, D7_pin);

//Variables
float hum, hum2;  //Stores humidity value
float temp, temp2; //Stores temperature value

void setup() {
  Serial.begin(9600);
  dht.begin();
  dht2.begin();

  lcd.begin (20, 4);

  // Switch on the backlight
  lcd.setBacklightPin(BACKLIGHT_PIN, POSITIVE);
  lcd.setBacklight(HIGH);

  // Position cursor and write some text
  lcd.home();
  lcd.print("Hallo!");
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

  lcd.home();
  lcd.clear();
  lcd.print("Sensor 1:");
  lcd.setCursor(0, 1);
  lcd.print(temp);
  lcd.setCursor(6, 1);
  lcd.print("C");
  lcd.setCursor(8, 1);
  lcd.print(hum);
  lcd.setCursor(14, 1);
  lcd.print("% relF");

  lcd.setCursor(0, 2);
  lcd.print("Sensor 2:");
  lcd.setCursor(0, 3);
  lcd.print(temp2);
  lcd.setCursor(6, 3);
  lcd.print("C");
  lcd.setCursor(8, 3);
  lcd.print(hum2);
  lcd.setCursor(14, 3);
  lcd.print("% relF");

  delay(10000); //Delay 2 sec.
}
