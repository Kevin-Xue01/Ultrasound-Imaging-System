// ---------------------------------------------------------------- //
// Arduino Ultrasoninc Sensor HC-SR04
// Re-writed by Arbi Abdul Jabbaar
// Using Arduino IDE 1.8.7
// Using HC-SR04 Module
// Tested on 17 September 2019
// ---------------------------------------------------------------- //

#define echoPin 2 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 4 //attach pin D3 Arduino to pin Trig of HC-SR04

// defines variables
#include <TimerOne.h>
long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement

const int k = 512;
int t = 25;
const unsigned int MAX_MESSAGE_LENGTH = 12;
int incomingByte = 0;
int pulses_left = 0;
void setup() {
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  Serial.begin(9600); // // Serial Communication is starting with 9600 of baudrate speed
  Serial.println("Ultrasonic Sensor HC-SR04 Test"); // print some text in Serial Monitor
  Serial.println("with Arduino UNO R3");
}
void loop() {
  // Clears the trigPin condition
  while (Serial.available() > 0)
 {
   //Create a place to hold the incoming message
   static char message[MAX_MESSAGE_LENGTH];
   static unsigned int message_pos = 0;

   //Read the next available byte in the serial receive buffer
   char inByte = Serial.read();

   //Message coming in (check not terminating character) and guard for over message size
   if ( inByte != '\n' && (message_pos < MAX_MESSAGE_LENGTH - 1) )
   {
     //Add the incoming byte to our message
     message[message_pos] = inByte;
     message_pos++;
   }
   //Full message received...
   else
   {
     //Add null character to string
     message[message_pos] = '\0';

     //Print the message (or do other things)
     Serial.println(message);

     t = atoi(message);
     Serial.println(t);

     //Reset for the next message
     message_pos = 0;
   }
 }
  Timer1.initialize(t); // period    
  Timer1.pwm(5, k);
  Timer1.pwm(6, k);
  Timer1.pwm(9, k);
  Timer1.pwm(10, k);
  Timer1.pwm(11 , k);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
}
// Include the AccelStepper Library
#include <AccelStepper.h>

// Define step constant
#define FULLSTEP 4

//// Creates an instance
//// Pins entered in sequence IN1-IN3-IN2-IN4 for proper step sequence
//AccelStepper myStepper(FULLSTEP, 8, 10, 9, 11);
//
//void setup() {
//  // set the maximum speed, acceleration factor,
//  // initial speed and the target position
//  myStepper.setMaxSpeed(1000.0);
//  myStepper.setAcceleration(50.0);
//  myStepper.setSpeed(200);
//  myStepper.moveTo(2038);
//}
//
//void loop() {
//  // Change direction once the motor reaches target position
//  if (myStepper.distanceToGo() == 0) 
//    myStepper.moveTo(-myStepper.currentPosition());
//
//  // Move the motor one step
//  myStepper.run();
//}
