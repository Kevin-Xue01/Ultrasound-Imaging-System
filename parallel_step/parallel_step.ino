#include <Stepper.h>

// Defines the number of steps per rotation
const int stepsPerRevolution = 2038;

const int numberOfRotations = 2;

// Creates an instance of stepper class
// Pins entered in sequence IN1-IN3-IN2-IN4 for proper step sequence
Stepper myStepper = Stepper(stepsPerRevolution, 8, 10, 9, 11);
Stepper myStepper2 = Stepper(stepsPerRevolution, 4, 6, 5, 7);

void setup() {
  // Nothing to do (Stepper Library sets pins as outputs)
}

void loop() {
  myStepper.setSpeed(10);
  for (int i = 0; i < numberOfRotations * stepsPerRevolution; i++){
    myStepper.step(1);
    myStepper2.step(1);
  }

  delay(500); // adjust amount of time
  
   for (int i = 0; i < numberOfRotations * stepsPerRevolution; i++){
    myStepper.step(-1);
    myStepper2.step(-1);
  }
  
}
