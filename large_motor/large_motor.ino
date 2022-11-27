#include <AccelStepper.h>

int x_motor_pulse_pin = 8;
int x_motor_dir_pin = 9;

int x_motor_max_speed = 2000;
int x_motor_steps_per_revolution = 200; // check the switches on the controller
int x_motor_max_revolutions = 17; 


AccelStepper stepper(1, x_motor_pulse_pin, x_motor_dir_pin);

void setup() {
  Serial.begin(9600); // // Serial Communication is starting with 9600 of baudrate speed
  Serial.println("Starting in 3");
  delay(1000);
  Serial.println("Starting in 2");
  delay(1000);
  Serial.println("Starting in 1");
  delay(1000);
  
  stepper.setMaxSpeed(max_speed);
  
}


void loop() {
  digitalWrite(dir_pin, LOW); // HIGH is toward motor, LOW is away
  Timer1.pwm(pulse_pin, 512);
  delayMicroseconds(50000);
  Timer1.disablePwm(pulse_pin);
  while(true){
    
  }
}
