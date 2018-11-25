// DHT22 Temp/Humidity Sensor connected to Makerfocus D1 mini
// Reads temp and humidity every 5 seconds and prints them to Serial

#include "ESP8266WiFi.h"
#include "ESP8266HTTPClient.h"
#include "DHT.h"

#define DHTPIN 5 // mapped to D1 on the Makerfocus D1 mini

//SSID of your network
const char ssid[] = "SSID";
const char pass[] = "PASSWORD";

const char* host = "192.168.178.48";

float humidity, temperature;

unsigned long previousMillis = 0;
const long interval = 2000;

DHT dht(DHTPIN, DHT22);

void setup()
{
  pinMode(DHTPIN, INPUT_PULLUP);
  Serial.begin(9600);
  delay(10);
  Serial.print("DHT init ... ");
  dht.begin();
  Serial.println("successful!");

  // Connect to Wi-Fi network
  Serial.print("Connecting to WiFi ");
  Serial.print(ssid);
  Serial.println(" ... ");

  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("succesful!");
}

void logToServer() {
  Serial.print("Connecting to ");
  Serial.print(host);

  // Use WiFiClient class to create TCP connections
  WiFiClient client;

  const int httpPort = 1985;

  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  } else {
    Serial.println(" ... connection made");
  }

  if(WiFi.status() == WL_CONNECTED){   //Check WiFi connection status

    HTTPClient http;    //Declare object of class HTTPClient

    http.begin("http://192.168.178.48:1985/log");      //Specify request destination
    http.header("POST / HTTP/1.1");
    http.header("Host: 192.168.178.48");
    http.header("Accept: */*");
    http.addHeader("Content-Type", "application/json");
    int httpCode = http.POST("{\"temperature\": \"" + String(temperature) + "\", \"humidity\": \"" + String(humidity) + "\", \"deviceId\": \"arbeitszimmer\"}");
    String payload = http.getString();                                        
    Serial.println(httpCode);   //Print HTTP return code
    Serial.println(payload);    //Print request response payload
    http.end();  //Close connection

  }else{

    Serial.println("Error in WiFi connection");   

  }
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

  logToServer();

  delay(60000);
}
