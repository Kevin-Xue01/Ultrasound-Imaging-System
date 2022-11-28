#include <Stepper.h>

// User variables
int x_motor_travel_percentage = 95; // percentage of x axis travel 
float x_motor_pixel_percentage = 0.8; // percentage of x_motor_total steps for 1 pixel

int y_motor_travel_percentage = 90; // percentage of x axis travel 
float y_motor_pixel_percentage = 2; // percentage of y_motor_total steps for 1 pixel
// System variables

// x motor
int x_motor_pulse_pin = 9;
int x_motor_dir_pin = 8;

int x_motor_steps_per_revolution = 5760; // check the switches on the controller

int x_motor_max_revolutions = 17; // found by manually rotating x axis lead screw


float x_motor_total_steps = (x_motor_travel_percentage / 100.0) * (float)x_motor_steps_per_revolution * (float)x_motor_max_revolutions;
long x_motor_steps_per_pixel = (long)((x_motor_pixel_percentage / 100.0) * x_motor_total_steps);
int x_motor_total_pixels = (int)(100.0 / x_motor_pixel_percentage);

//int x_motor_new_total_steps = x_motor_steps_per_pixel * x_motor_total_pixels;

// y motor
int y_motor_IN_1_pin = 4;
int y_motor_IN_2_pin = 5;
int y_motor_IN_3_pin = 6;
int y_motor_IN_4_pin = 7;

int y_motor_steps_per_revolution = 2038; // datasheet

int y_motor_max_speed = 15; // rpm

int y_motor_max_revolutions = 24; // found by manually rotating y axis lead screw

float y_motor_total_steps = (y_motor_travel_percentage / 100.0) * (float)y_motor_steps_per_revolution * (float)y_motor_max_revolutions;
long y_motor_steps_per_pixel = (long)((y_motor_pixel_percentage / 100.0) * y_motor_total_steps);
int y_motor_total_pixels = (int)(100.0 / y_motor_pixel_percentage);
//int y_motor_new_total_steps = y_motor_steps_per_pixel * y_motor_total_pixels;

Stepper YStepper = Stepper(2038, 4, 6, 5, 7);

// Takes a step in the axis ax and direction dir
// ax: if false: x axis, if true: y axis
// ax: if false: (+)dir, if true: (-)dir
void step(bool ax, bool dir) {
  if (dir) {
    if (ax) {
      YStepper.step(-y_motor_steps_per_pixel);
    } else {
      run_x_motor(x_motor_steps_per_pixel, 0);
    }
  } else {
    if (ax) {
      YStepper.step(y_motor_steps_per_pixel);
    } else {
      run_x_motor(x_motor_steps_per_pixel, 1);
    }
  }
}
//void step(bool ax, bool dir) {
//  if (dir) {
//    if (ax) {
//      YStepper.step(-y_motor_steps_per_revolution);
//    } else {
//      run_x_motor(x_motor_steps_per_revolution, 0);
//    }
//  } else {
//    if (ax) {
//      YStepper.step(y_motor_steps_per_revolution);
//    } else {
//      run_x_motor(x_motor_steps_per_revolution, 1);
//    }
//  }
//}

void run_x_motor(long steps, int dir){
  digitalWrite(x_motor_dir_pin, dir);
  for (long i = 0; i < steps; i++) {
    digitalWrite(x_motor_pulse_pin, HIGH);
    delayMicroseconds(33);
    digitalWrite(x_motor_pulse_pin, LOW);
    delayMicroseconds(33);
  }
}

// Trajectory 1, X-Main
void trajectory1() {
  for (int j = 0; j < y_motor_total_pixels; j++) {
     for (int i = 0; i < x_motor_total_pixels; i++) {
      if (j % 2 == 1) {
        step(0, j % 2 == 1);
        printCoord(x_motor_total_pixels - i - 1, j);
      } else {
        printCoord(i, j);
        step(0, j % 2 == 1);
      }
     }
     step(1, 0);
   }
}
//
//void trajectory1() {
//  for (int j = 0; j < y_motor_max_revolutions; j++) {
//     for (int i = 0; i < x_motor_max_revolutions; i++) {
//      if (j % 2 == 1) {
//        step(0, j % 2 == 1);
//        printCoord(x_motor_max_revolutions - i - 1, j);
//      } else {
//        printCoord(i, j);
//        step(0, j % 2 == 1);
//      }
//     }
//     step(1, 0);
//   }
//}

void reset() {
  for (int i = 0; i < x_motor_total_pixels; i++) {
    Serial.println("Stepping x axis, (-) direction");
    step(0, 1);
  }
  for (int j = 0; j < y_motor_total_pixels; j++) {
    Serial.println("Stepping y axis, (-) direction");
    step(1, 1);
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
  pinMode(x_motor_pulse_pin, OUTPUT);
  pinMode(x_motor_dir_pin, OUTPUT);

  Serial.println("Image_Size_X: " + String(x_motor_total_pixels));
  Serial.println("Image_Size_Y: " + String(y_motor_total_pixels));

  
//  Serial.println(String(x_motor_total_steps)); 
//  Serial.println(String(x_motor_steps_per_pixel)); 
//  Serial.println(String(x_motor_total_pixels)); 
//
//  Serial.println(String(y_motor_total_steps)); 
//  Serial.println(String(y_motor_steps_per_pixel)); 
//  Serial.println(String(y_motor_total_pixels)); 

  Serial.println("Starting in 3");
  delay(1000);
  Serial.println("Starting in 2");
  delay(1000);
  Serial.println("Starting in 1");
  delay(1000);
  

  
  // Before running entire trajectory,
  // reset to Initial Positions First
   trajectory1();
//   reset();
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
