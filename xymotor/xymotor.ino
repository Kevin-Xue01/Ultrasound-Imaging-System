#include <Stepper.h>

//const int stepsPerRevolution = 2038;
//const int x_max = 15;
//const int y_max = 25;

const int x_stepsPerRevolution = 100;
const int y_stepsPerRevolution = 100;
const int x_max = 301;
const int y_max = 301;

Stepper XStepper = Stepper(2038, 8, 10, 9, 11);
Stepper YStepper = Stepper(2038, 4, 6, 5, 7);

// Takes a step in the axis ax and direction dir
// ax: if false: x axis, if true: y axis
// ax: if false: (+)dir, if true: (-)dir
void step(bool ax, bool dir) {
  if (dir) {
    if (ax) {
      YStepper.step(-y_stepsPerRevolution);
    } else {
      XStepper.step(-x_stepsPerRevolution);
    }
  } else {
    if (ax) {
      YStepper.step(y_stepsPerRevolution);
    } else {
      XStepper.step(x_stepsPerRevolution);
    }
  }
}

// Trajectory 1, X-Main
void trajectory1() {
  for (int j = 0; j < y_max; j++) {
     for (int i = 0; i < x_max; i++) {
      if (j % 2 == 1) {
        step(0, j % 2 == 1);
        printCoord(x_max - i - 1, j);
      } else {
        printCoord(i, j);
        step(0, j % 2 == 1);
      }
       
     }
     step(1, 0);
   }
}

// Trajectory 2, Y-Main
void trajectory2() {
  for (int i = 0; i < x_max; i++) {
    for (int j = 0; j < y_max; j++) {
      printCoord(i, i % 2 == 1? y_max - j - 1 : j);
      step(1, i % 2 == 1);
    }
    step(0, 0);
  }
}

void reset() {
  for (int i = 0; i < x_max; i++) {
    Serial.println("Stepping x axis, (-) direction");
    step(0, 1);
  }
  for (int j = 0; j < y_max; j++) {
    Serial.println("Stepping y axis, (-) direction");
    step(1, 1);
  }
}

void xLine() {
  for (int i = 0; i < x_max; i++) {
    Serial.println("Stepping x axis, (+) direction");
    step(0, 0);
  }
}

void yLine() {
  for (int j = 0; j < y_max; j++) {
    Serial.println("Stepping y axis, (+) direction");
    step(1, 0);
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

  
  // Before running entire trajectory,
  // reset to Initial Positions First
   trajectory1();
   reset();
}



void loop() {
//    Serial.println("Stepping x axis, (+) direction");
//    step(0, 0);

//    Serial.println("Stpping x axis, (-) direction");
//    step(0, 1);
//
//    Serial.println("Stepping y axis, (+) direction");
//    step(1, 0);

//    Serial.println("Stepping y axis, (-) direction");
//    step(1, 1);



}
