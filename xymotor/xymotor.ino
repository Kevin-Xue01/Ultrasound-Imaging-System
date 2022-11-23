#include <Stepper.h>

const int stepsPerRevolution = 2038;
const int x_max = 15;
const int y_max = 25;

Stepper XStepper = Stepper(stepsPerRevolution, 8, 10, 9, 11);
Stepper YStepper = Stepper(stepsPerRevolution, 4, 6, 5, 7);

// Takes a step in the axis ax and direction dir
// ax: if false: x axis, if true: y axis
// ax: if false: (+)dir, if true: (-)dir
void step(bool ax, bool dir) {
  if (dir) {
    if (ax) {
      YStepper.step(-stepsPerRevolution);
    } else {
      XStepper.step(-stepsPerRevolution);
    }
  } else {
    if (ax) {
      YStepper.step(stepsPerRevolution);
    } else {
      XStepper.step(stepsPerRevolution);
    }
  }
}

void printCoord(int x, int y) {
  char strBuf[50];
  sprintf(strBuf, "coords %d %d", x, y);
  Serial.println(strBuf);
}

void setup() {
  Serial.begin(9600);
  YStepper.setSpeed(15);
  XStepper.setSpeed(15);

  Serial.println("Starting in 3");
  delay(1000);
  Serial.println("Starting in 2");
  delay(1000);
  Serial.println("Starting in 1");
  delay(1000);
}

void loop() {
//    Serial.println("Stepping x axis, (+) direction");
//    step(0, 0);
//
    Serial.println("Stepping x axis, (-) direction");
    step(0, 1);
//
//    Serial.println("Stepping y axis, (+) direction");
//    step(1, 0);

//    Serial.println("Stepping y axis, (-) direction");
//    step(1, 1);



  // Before running entire trajectory,
  // reset to Initial Positions First

//    // Trajectory 1, X-Main
//    for (int j = 0; j < y_max; j++) {
//      for (int i = 0; i < x_max; i++) {
//        printCoord(j % 2 == 1 ? x_max - i - 1 : i, j);
//        step(0, j % 2 == 1);
//      }
//      step(1, 0);
//    }

  //  // Trajectory 2, Y-Main
  //  for (int i = 0; i < x_max; i++) {
  //    for (int j = 0; j < y_max; j++) {
  //      printCoord(i, i % 2 == 1? y_max - j - 1 : j);
  //      step(1, i % 2 == 1);
  //    }
  //    step(0, 0);
  //  }
}
