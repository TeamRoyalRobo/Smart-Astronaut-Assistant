// FINAL WORKING

#include <Servo.h>
#include <SoftwareSerial.h>

#define RxD 10
#define TxD 11

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position


SoftwareSerial BTSerial(RxD, TxD);

//L298
//Motor A
const int motorPin1  = 5;  // Pin 14 of L293
const int motorPin2  = 6;  // Pin 10 of L293
//Motor B
const int motorPin3  = 9; // Pin  7 of L293
const int motorPin4  = 8;  // Pin  2 of L293

// Ultrasonic
const int trigPin = 7;
const int echoPin = 6;

void setup(){
  BTSerial.begin(38400);
  Serial.begin(9600);
  myservo.attach(7);  // attaches the servo on pin 9 to the servo object
//  BTSerial.print("AT\r\n");
  Serial.println("Welcome to Smart Astronaut Assistant!");

  //Set pins as outputs
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);
}
// time to distance ultrasonic
long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}
void moveForward() {
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin4, LOW);
  Serial.write("Moving Forward...\r\n");
}
void moveBackward() {
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, HIGH);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, HIGH);
  Serial.write("Moving Backward...\r\n");
}
void turnRight() {
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, HIGH);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin4, LOW);
  Serial.write("Turning right...\r\n");
}
void turnLeft() {
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, HIGH);
  Serial.write("Turning left...\r\n");
}
void stopHere() {
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, LOW);
  Serial.write("Stopped...\r\n");
}

void loop(){

// Controlling with bluetooth
  if (BTSerial.available()){
    char cmd = BTSerial.read();
    if (cmd == 'u'){
      moveForward();
    }
    else if (cmd == 'd'){
      moveBackward();
    }
    else if (cmd == 'l'){
      turnLeft();
    }
    else if (cmd == 'r'){
      turnRight();
    }
    else if (cmd == 'e'){
      Serial.write("Moving left...");
    }
    else if (cmd == 'i'){
      Serial.write("Moving right...");
    }
    else if (cmd == 's'){
      stopHere();
    }
    
  }

  //  Rotating Servo

    for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
    for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }

  // Ultrasonic
  // establish variables for duration of the ping, 
  // and the distance result in inches and centimeters:
  long duration, cm;

  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(trigPin, OUTPUT);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);

  // convert the time into a distance
  cm = microsecondsToCentimeters(duration);
  if (cm <= 10) {
    stopHere();
  }

//  if (Serial.available()){
//    char cmd = Serial.read();
//    BTSerial.write(cmd);
//  }
  
}
