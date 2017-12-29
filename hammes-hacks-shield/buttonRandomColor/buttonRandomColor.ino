// Purople is made by turning on the red and blue leds together.
const int BLUE = 3; 
const int GREEN =  5;
const int RED = 6;
const int GND = 2; 
const int BUTTON = 4;
int brightness;
double change;
int changedColor = 0;

int maxBlue, maxRed, maxGreen;

#include<LiquidCrystal.h>

void setup() {
  //this tells the arduino that the pins are outputs (not analog or digital inputs)
  pinMode (GND, OUTPUT);
  pinMode (BLUE, OUTPUT);
  pinMode (GREEN, OUTPUT);
  pinMode (RED, OUTPUT);

  pinMode (BUTTON, INPUT_PULLUP);

  //this tells the arduino what state (high or 1, low or 0) to put the pins in
  digitalWrite(GND, 0); //in the red example this was "LOW" and not 0
  analogWrite(BLUE, 0);
  analogWrite(GREEN, 0);
  analogWrite(RED, 0);

  brightness = 0;
  change = 0;
}

void loop() {
  delay(5);

  change = change + 0.01;
      
  analogWrite(BLUE, abs(sin(change)) * maxBlue);
  analogWrite(GREEN, abs(sin(change * 1.41)) * maxGreen);
  analogWrite(RED, abs(sin(change * 1.73)) * maxRed);
  
  if (digitalRead(BUTTON) == LOW && changedColor == 0) {
    maxBlue = random(30);
    maxGreen = random(30);
    maxRed = random(30);

    changedColor = 1;
  }
  
  if (digitalRead(BUTTON) == HIGH) {
    changedColor = 0;
  }
}
