// A0 = Handbrake Pot
//
//
// NOTE: This sketch file is for use with Arduino Leonardo (atmega32u4) only
//
//
//
//--------------------------------------------------------------------

#include <Joystick.h>

int value1 = 0;

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID, JOYSTICK_TYPE_GAMEPAD,
                   12, 0,                  // Button Count, Hat Switch Count
                   true, true, false,     // X and Y, but no Z Axis
                   false, false, false,   // No Rx, Ry, or Rz
                   false, false,          // No rudder or throttle
                   false, false, false);  // No accelerator, brake, or steering

const int buttonPins[] = {2, 3, 4, 5, 6, 7, 8, A1, 10, 16, 14, 15};
const int brakePin = A0;
const int ledPin =  A2;

unsigned long previousMillis = 0;
int ledState = LOW; 
const long interval = 500;


void setup() {
  // Initialize Button Pins
  for (int i = 0; i < sizeof(buttonPins); i++)
  {
    pinMode(buttonPins[i], INPUT_PULLUP);
  }
  pinMode(ledPin, OUTPUT);

  // Initialize Joystick Library
  Joystick.begin();
  Joystick.setXAxisRange(0, 1024);
  Joystick.setYAxisRange(-1, 1);
  Joystick.setXAxis(20);
}


void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    // if the LED is off turn it on and vice-versa:
    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }

    // set the LED with the ledState of the variable:
    digitalWrite(ledPin, ledState);
  }


  value1 = analogRead(brakePin);
  delay(20);
  Joystick.setXAxis(value1);
  // Button Pins
  for (int i = 0; i < sizeof(buttonPins); i++)
  {
    Joystick.setButton(i, digitalRead(buttonPins[i]));
  }

  delay(30);
}

