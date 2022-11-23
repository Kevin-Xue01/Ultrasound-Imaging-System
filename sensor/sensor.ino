#define echoPin 2 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 4 //attach pin D3 Arduino to pin Trig of HC-SR04

#define PIN5 (1<< 5)
#define PIN6 (1<< 6)
#define PIN7 (1<< 7)

// defines variables
#include <TimerOne.h>
//#include <PWM.h>
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

void setup() {
  TCNT2 = 0;
  TCCR2A = (1<<COM2B1) + (1<<WGM21) + (1<<WGM20);
  TCCR2B = (1<<CS21) + (1<<CS20) + (1<<WGM22);
  
  TIMSK2 = (1 << OCIE2B);
  OCR2A = 5;
  OCR2B = 2;
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

ISR(TIMER2_COMPB_vect) {
  val = val ^ 0XFF;

  PORTB = val;

}
void loop() {
  // Clears the trigPin condition
//   while (Serial.available() > 0)
//   {
//    //Create a place to hold the incoming message
//    static char message[MAX_MESSAGE_LENGTH];
//    static unsigned int message_pos = 0;

//    //Read the next available byte in the serial receive buffer
//    char inByte = Serial.read();

//    //Message coming in (check not terminating character) and guard for over message size
//    if ( inByte != '\n' && (message_pos < MAX_MESSAGE_LENGTH - 1) )
//    {
//      //Add the incoming byte to our message
//      message[message_pos] = inByte;
//      message_pos++;
//    }
//    //Full message received...
//    else
//    {
//      //Add null character to string
//      message[message_pos] = '\0';

//      //Print the message (or do other things)
//      Serial.println(message);

//      t = atoi(message);
//      Serial.println(t);

//      //Reset for the next message
//      message_pos = 0;
//    }
//  }
  
//   Timer1.initialize(t); // period 
  
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

