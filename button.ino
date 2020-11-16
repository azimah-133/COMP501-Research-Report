//the right motor will be controlled by the motor A pins on the motor driver
const int AIN1 = 13;           //control pin 1 on the motor driver for the right motor
const int AIN2 = 12;            //control pin 2 on the motor driver for the right motor
const int PWMA = 11;            //speed control pin on the motor driver for the right motor

//the left motor will be controlled by the motor B pins on the motor driver
const int PWMB = 10;           //speed control pin on the motor driver for the left motor
const int BIN2 = 9;           //control pin 2 on the motor driver for the left motor
const int BIN1 = 8;           //control pin 1 on the motor driver for the left motor

//int switchPin = 7;             //switch to turn the robot on and off

int rightmovement = 4000;
int leftmovement = 2000;

int ButtonState1 = LOW;
int ButtonState2 = LOW;

void setup() {
  // put your setup code here, to run once:
  pinMode(2, INPUT);
  pinMode(3, INPUT);

  //pinMode(switchPin, INPUT_PULLUP);   //set this as a pullup to sense whether the switch is flipped

  //set the motor contro pins as outputs
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);

  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(PWMB, OUTPUT);
}

void loop() {
  ButtonState1 = digitalRead(2);
  ButtonState2 = digitalRead(3);

  // if the button is not pressed, all motors are turned off
  if (ButtonState1 == LOW) {
    digitalWrite(AIN1, LOW);                         //set pin 1 to high
    digitalWrite(AIN2, LOW);                          //set pin 2 to low
  }

  // if the button is pressed, all motors are turned off
  if (ButtonState1 == HIGH) {
    digitalWrite(AIN1, HIGH);                         //set pin 1 to high
    digitalWrite(AIN2, LOW);                          //set pin 2 to low
    analogWrite(PWMA, abs(rightmovement));
    analogWrite(PWMB, abs(rightmovement));

  }
  if (ButtonState2 == LOW) {
    digitalWrite(BIN1, LOW);                         //set pin 1 to high
    digitalWrite(BIN2, LOW);                         //set pin 2 to low
  }

  if (ButtonState2 == HIGH) {
    digitalWrite(BIN1, HIGH);                         //set pin 1 to high
    digitalWrite(BIN2, LOW);                          //set pin 2 to low
    analogWrite(PWMA, abs(leftmovement));
    analogWrite(PWMB, abs(leftmovement));
  }
}


