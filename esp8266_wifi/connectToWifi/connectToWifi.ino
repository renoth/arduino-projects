#include <SoftwareSerial.h>
SoftwareSerial esp8266(2, 3);
String Data = "";

//hints at https://arduino.stackexchange.com/questions/18575/send-at-commands-to-esp8266-from-arduino-uno-via-a-softwareserial-port

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  Serial.println("Started");

  // set the data rate for the SoftwareSerial port
  esp8266.begin(9600);

  connect_wifi("AT\r\n", 1000);
  connect_wifi("AT+CWMODE=1\r\n", 1000);
  connect_wifi("AT+CWQAP\r\n", 1000);
  connect_wifi("AT+RST\r\n", 5000);
  Serial.println("Connecting to test Wireless network");
  connect_wifi("AT+CWJAP=\"AndroidAP\",\"lagodigarda\"\r\n", 10000);
}

void loop() {
  // put your main code here, to run repeatedly:

}

void connect_wifi(String cmd, int t)
{
  int i = 0;
  while (1)
  {
    Serial.println(cmd);
    esp8266.write("AT\r\n");

    while (esp8266.available())
    {
      char character = esp8266.read(); // Receive a single character from the software serial port
      Data.concat(character); // Add the received character to the receive buffer
    }

    Serial.print("Received: ");
    Serial.println(Data);

    if (Data.indexOf("OK") > 0) {
      i = 8;
    }

    Data = "";

    delay(t);
    if (i > 1)
      break;
    i++;
  }

  if (i == 8)
  {
    Serial.println("OK");
  }
  else
  {
    Serial.println("Error");
  }
}
