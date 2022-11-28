#include <TimerOne.h>
//#include <PWM.h>

#define echoPin 2 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 3 //attach pin D3 Arduino to pin Trig of HC-SR04

// DEFINE VARIABLES
long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement
const int interrupt_pin = 3;

const int k = 512;
int t = 25;
const unsigned int MAX_MESSAGE_LENGTH = 12;
int incomingByte = 0;
int pulses_left = 0;
int32_t frequency = 40000;

unsigned char val = 0x00;


#define CIRCLE_SIZE 1
uint16_t circleData[CIRCLE_SIZE] = {0};
uint16_t circlePointer = 0;
uint32_t circleSum = 0;

void updateRollingAverage(uint16_t value)
{
  circleSum = circleSum - circleData[circlePointer] + value;
  circleData[circlePointer] = value;
  circlePointer++;
  if (circlePointer == CIRCLE_SIZE) circlePointer = 0;
}

uint16_t rollingAverage()
{
  return circleSum / CIRCLE_SIZE;
}

void setup() {
  TCNT2 = 0;
  TCCR2A = (1<<COM2B1) + (1<<WGM21) + (1<<WGM20);
  TCCR2B = (1<<CS21) + (1<<CS20) + (1<<WGM22);
  
  TIMSK2 = (1 << OCIE2B);
  OCR2A = 50;
  OCR2B = 25;
  DDRD |= (1<<PD3);
  DDRD |= B11110111;
  DDRB |= B11111111;
  DDRD |= PIN6;
  sei();
  
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  Serial.begin(9600); // // Serial Communication is starting with 9600 of baudrate speed
  Serial.println("Ultrasonic Sensor HC-SR04 Test"); // print some text in Serial Monitor
  Serial.println("with Arduino UNO R3");
}

void printDist(int distance) {
  char strBuf[50];
  sprintf(strBuf, "distance %d", distance);
  Serial.println(strBuf);
}

ISR(TIMER2_COMPB_vect) {
  val = val ^ 0XFF;

  PORTB = val;

}

void loop() {
  delay(5);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH); // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW); // Reads the echoPin, returns the sound wave travel time in microseconds

  // Calculate and display the distance
  distance = pulseIn(echoPin, HIGH) * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  if (distance > 255) {
    distance = 255;
  }
  printDist(distance);

  //  updateRollingAverage(pulseIn(echoPin, HIGH));
}
