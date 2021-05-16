#include <Arduino.h>
#include <Stepper.h>

// ADC3 (PINB3) for analog input
#define SPEED_IN 3 

// Define number of steps per rotation:
const int stepsPerRevolution = 4096;
//Attiny85 connection
// PB2 -> IN 1
// PB1 -> IN 2
// PB0 -> IN 3
// PB4 -> IN 4
// For the stepper libraray to work, we need to swap the middle pair (IN2 and IN3)
// So our sequnece is 2, 1, 0, 4 > 2, 0, 1, 4
Stepper myStepper = Stepper(stepsPerRevolution, 2, 0, 1, 4);

void setup() {
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(3, INPUT);
}

void loop() {
  // read the potentiometer value, will be used to controll both speed and direction.
  int sensorReading = analogRead(SPEED_IN); 

  int motorSpeed = 0;
  int stepSign = 1;
  if (sensorReading < 512) { // reverse direction
    stepSign = -1;
    sensorReading = 512 - sensorReading;
  } else if (sensorReading >= 512) { //forward direction
    sensorReading = sensorReading - 512;
  }
  //50 found experimentally, the motor can go faster byt it's not interesting for the use case we have
  motorSpeed = map(sensorReading, 0, 512, 0, 50);

  if (motorSpeed > 0) {
    myStepper.setSpeed(motorSpeed);
    myStepper.step(stepSign * motorSpeed);
  }
}
