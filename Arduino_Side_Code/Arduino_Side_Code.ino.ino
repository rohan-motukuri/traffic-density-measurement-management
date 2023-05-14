#include <Stepper.h>
#include <Servo.h>

const int trigPin = 8;
const int echoPin = 9; 

const int servoPin = 7;

long duration;
int distance;

int tiltAngle = 0;
int tiltDir = 1;

const int stepsPerRevolution = 2038 / 10;
const int intersections = 4;

Stepper myStepper = Stepper(stepsPerRevolution, 10, 12, 11, 13);

Servo tilter;

void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  
  myStepper.setSpeed(20);
  tilter.attach(servoPin);

  Serial.begin(9600);
}

void loop() {
  // rotates the stepper motor from 0 to 360 degrees clockwise
  for (int tempInt = 0, sum = 0; tempInt < intersections; ++tempInt) {
    sum = 0;
    for (int i = 0; i < stepsPerRevolution / intersections; i++) {
      
      myStepper.step(10);
      delay(30);
      sum += calculateDistance();
        
      tilter.write(updTilt());
    }
      
      Serial.print(tempInt);
      Serial.print(',');
      Serial.println(sum);  
 }


  // rotates the stepper motor from 0 to 360 degrees counterclockwise
  
  for (int tempInt = intersections - 1, sum = 0; tempInt >= 0; --tempInt) {
    sum = 0;
    for (int i = 0; i < stepsPerRevolution / intersections; i++) {
      myStepper.step(-10);
      delay(30);
      sum += calculateDistance();

      tilter.write(updTilt());
    }
      
      Serial.print(tempInt);
      Serial.print(',');
      Serial.println(sum);
  }
}

// Function for calculating the distance measured by the Ultrasonic sensor
int calculateDistance() { 
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH); //  Reads the echoPin, returns the sound wave travel time in microseconds
  distance = duration * 0.034 / 2;
  distance = (distance > 0 ? distance : 0);
  return distance;
}

int updTilt () {
  if(tiltAngle <= 0) {
    tiltDir = 1;
  }
  
  if(tiltAngle >= 20) {
    tiltDir = -1;
  } 

  tiltAngle += tiltDir;

  return tiltAngle;
}
