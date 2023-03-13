#include <Stepper.h>

int light_detector_pin = 12;
int stepCount = 0;          // number of steps the motor has taken
int light_detector_value = 0;

const int stepsPerRevolution = 64;  // change this to fit the number of steps per revolution

// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);

void setup() {
  // initialize the serial port:
  Serial.begin(9600);
  pinMode(light_detector_pin, INPUT);
}

void loop() {
  light_detector_value = digitalRead(light_detector_pin);
  Serial.print("light detector value:");
  Serial.println(light_detector_value);

  if (light_detector_value == HIGH) {
    myStepper.step(1);
    Serial.print("steps:");
    Serial.println(stepCount);
    stepCount++;
  }
}
