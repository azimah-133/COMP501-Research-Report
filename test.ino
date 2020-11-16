/**
 * COMP501 Computing Tech in Society 2019 S1
 * 
 * Autonomous Car Project
 * 
 * This program code is of a 4-wheel drive motor with a distance sensor.
 * When the switch is off, the car is still.
 * When the switch in on, the car drives forward and drives backward when it encounters an obstacle.
 * 
 * @author Azimah Ali
 * @version 1.6.12
 */

#include <NewPing.h>

// distance variables
NewPing sonar(5,6); // sensor pins
const int trigPin = 6;
const int echoPin = 5;

// Motor A pins
int PWMA = 11; // speed control pin - enables motor A - right yellow
int AIN1 = 13; // control pin 1 - moves foward - right
int AIN2 = 12; // control pin 2 - moves backward - right

//Motor B pins (enabledB = enable motor, pinB2 = forward, pinB2 = backward)
int PWMB = 10; // speed control pin - enables motor B - left yellow
int BIN1 = 8; // control pin 1 - moves forward - left
int BIN2 = 9; // control pin 2 - moves backward - left

int switchPin = 7; // switch used to turn the robot on and off
float distance = 0; // variable to store the distance measured by the distance sensor

//robot behaviour variables
int backupTime = 200; // amount of time that the robot will back up when it senses an object
int turnTime = 300; // amount that the robot will turn once it has backed up

void setup()
{
  pinMode(trigPin, OUTPUT); // the pin will send ultrasonic pulses out from the distance sensor
  pinMode(echoPin, INPUT); // the pin will sense when the pulses reflect back to the distance sensor

  pinMode(switchPin, INPUT_PULLUP); // set as a pullup resistor to flip the switch

  // set motor control pins as outputs
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);

  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(PWMB, OUTPUT);

  Serial.begin(9600); // begin serial communication with the computer
  Serial.print("Run forest run!");  // test the serial connection
}

void loop()
{
  // Detect distance from the distance sensor
  distance = getDistance();

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" in");              // print  units

  if (digitalRead(switchPin) == LOW) { // if the on switch is flipped

    // if an object is detected
    if (distance < 10) { 
      //back up and turn
      Serial.print(" ");
      Serial.print("BACK!");

      // stop for a moment
      rightMotor(0);
      leftMotor(0);
      delay(200);

      // back up
      rightMotor(-255);
      leftMotor(-255);
      delay(backupTime);

      // turn to the right
      rightMotor(-255);
      leftMotor(255);
      delay(turnTime);

   // if no obstacle is detected drive forward
    } else {                         
      Serial.print(" ");
      Serial.print("Moving...");
      rightMotor(255);
      leftMotor(255);
    }
  
  // if the switch is off then stop
  } else {                        
    // stop the motors
    rightMotor(0);
    leftMotor(0);
  }
 delay(50); // delays 50 milliseconds between readings
}

void rightMotor(int motorSpeed) // function for driving the right motor
{
  if (motorSpeed > 0) // postive speed when motor drives forward
  {
    digitalWrite(AIN1, HIGH); // set pin 1 to high
    digitalWrite(AIN2, LOW); // set pin 2 to low
  }
  else if (motorSpeed < 0) // negatve speed when motor drives backward
  {
    digitalWrite(AIN1, LOW); // set pin 1 to low
    digitalWrite(AIN2, HIGH); // set pin 2 to high
  }
  // if the motor should stop
  else  
  {
    digitalWrite(AIN1, LOW); // set pin 1 to low
    digitalWrite(AIN2, LOW); // set pin 2 to low
  }
  analogWrite(PWMA, abs(motorSpeed)); // motor direction is set, drive it at the entered speed
}

// function for driving the left motor
void leftMotor(int motorSpeed)                        
{
  if (motorSpeed > 0) // postive speed when motor should drive forward
  {
    digitalWrite(BIN1, HIGH); // set pin 1 to high
    digitalWrite(BIN2, LOW);  // set pin 2 to low
  }
  else if (motorSpeed < 0) // negative speed when motor drive backward
  {
    digitalWrite(BIN1, LOW);                          // set pin 1 to low
    digitalWrite(BIN2, HIGH);                         // set pin 2 to high
  }
  else                                                // if  motor stops
  {
    digitalWrite(BIN1, LOW);                          // set pin 1 to low
    digitalWrite(BIN2, LOW);                          // set pin 2 to low
  }
  analogWrite(PWMB, abs(motorSpeed));                 // motor direction is set, drive it at the entered speed
}

// Return distance measured by the HC-SR04 distance sensor
float getDistance()
{
  float echoTime; // variable stores the time it takes for a ping to bounce off an object
  float calcualtedDistance; // variable stores the distance calculated from the echo time

  // send out an ultrasonic pulse that is 10ms long
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  echoTime = pulseIn(echoPin, HIGH); // use the pulsein command to see how long it takes for the pulse to bounce back to the sensor

  calcualtedDistance = echoTime / 148.0; // calculate the distance of the object that reflected the pulse (half the bounce time multiplied by the speed of sound)

  return calcualtedDistance; // send back distance that was calculated
}

