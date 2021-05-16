#include <Arduino.h>
#include <Stepper.h>

// #define SPEED_IN  A0; //uno
#define SPEED_IN 3 //attiny


// Define number of steps per rotation:
// const int stepsPerRevolution = 2048;
const int stepsPerRevolution = 4096;
// Wiring:
// Pin 8 to IN1 on the ULN2003 driver
// Pin 9 to IN2 on the ULN2003 driver
// Pin 10 to IN3 on the ULN2003 driver
// Pin 11 to IN4 on the ULN2003 driver
// Create stepper object called 'myStepper', note the pin order:

//From 
//
//The pin connections need to be 4 pins connected
// to Motor Driver In1, In2, In3, In4  and then the pins entered
// here in the sequence 1-3-2-4 for proper sequencingStepper small_stepper(STEPS, 0, 2, 1, 3);
//Stepper stepper(STEPS, 8, 9, 10, 11);       // For other Arduino
// Note that with the 28BYJ-48 you have to wire it "wrong" for it to turn backwards.
// When pins defined 0, 2, 1, 3 actually wire it 0, 1, 2, 3
//my setup: in1 -> 8, in2 -> 9, in3 -> 10, in4 -> 11; fixed sequence is 8,10,9,11
//arduino
// Stepper myStepper = Stepper(stepsPerRevolution, 8, 10, 9, 11);
//attiny 2, 1, 0, 4 -> 2, 0, 1, 4
Stepper myStepper = Stepper(stepsPerRevolution, 2, 0, 1, 4);



int stepCount = 0;  // number of steps the motor has taken

void setup() {
  // nothing to do inside the setup
  // Serial.begin(9600);
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(3, INPUT);
}

void loop() {
  // read the sensor value:
  int sensorReading = analogRead(SPEED_IN);
  // map it to a range from 0 to 100:
  int motorSpeed = 0;
  int stepSign = 1;
  if (sensorReading < 512) {
    stepSign = -1;
    sensorReading = 512 - sensorReading;
  } else if (sensorReading >= 512) {
    sensorReading = sensorReading - 512;
  }
  motorSpeed = map(sensorReading, 0, 512, 0, 50);
  // Serial.print(sensorReading); Serial");
  // Serial.println(motorSpeed * stepSign);

  if (motorSpeed > 0) {
    // myStepper.setSpeed(motorSpeed);
    myStepper.setSpeed(motorSpeed);
    myStepper.step(stepSign * motorSpeed);
    // myStepper.step(stepSign * stepsPerRevolution / 100);
  }

}
