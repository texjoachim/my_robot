// My_robot

#include <Arduino.h>
#include <ultrasonic.h>
#include <ky033.h>
#include <flyingFishHelper.h>
#include <Servo.h>
#include <motor.h>

ultrasonicsensor US(A0, A1); // ultrasonic sensor front
Servo servo; // servo moving the ultrasonic sensor
motor motorRight(2, 3, 9);
motor motorLeft(4, 5, 10);
//ky033 IRunten(); // ir sensor facing down, to prevent falling down stairs
//flyingFish RegenSensor(6, 7); // checking if it rains
const unsigned int servoPause = 15;
int distanceFront;
int distanceRight;
int distanceLeft;

// look to the right and get distance
int lookRight() {
    int distance = 0;
    servo.write(5);
    delay(150);
    distance = US.getDistance();
    servo.write(90);
    delay(servoPause);
    return distance;
}

// look to the left and get distance
int lookLeft() {
    int distance = 0;
    servo.write(175);
    delay(150);
    distance = US.getDistance();
    servo.write(90);
    delay(servoPause);
    return distance;
}

//testing the servo
void servotest() {
    
    for (int i=1; i <= 180; i++) {
        servo.write(i);
        delay(servoPause);
    }
    for (int i=180; i >= 1; i--) {
        servo.write(i);
        delay(servoPause);
    } 
}

//testing the motors
void motortest() {
    motorRight.forward(255);
    motorLeft.forward(255);
    delay(1000);
    motorRight.stop();
    motorLeft.stop();
    delay(1000);
    motorRight.reverse(255);
    motorLeft.reverse(255);
    delay(1000);
    motorRight.stop();
    motorLeft.stop();
}

void turnRight(unsigned int speed, unsigned int turntime) {
    motorRight.reverse(speed);
    motorLeft.forward(speed);
    delay(turntime);
    motorRight.stop();
    motorLeft.stop();
}

void turnLeft(unsigned int speed, unsigned int turntime) {
    motorRight.forward(speed);
    motorLeft.reverse(speed);
    delay(turntime);
    motorRight.stop();
    motorLeft.stop();
}

void setup() {
    servo.attach(12); // that's the servo pin
    delay(servoPause);
    servo.write(90); // ultrasonic sensor facing ahead
    delay(servoPause); 
    pinMode(A2, INPUT_PULLUP);
    pinMode(A3, INPUT_PULLUP);
    pinMode(A4, INPUT_PULLUP);
    Serial.begin(9600); 
	Serial.println("My Robot");
	Serial.println("--------");
}

void loop() {

//check if the main program should run or if we are just testing things

if (digitalRead(A3) == LOW) { //A3 on GND to test the individual components
    servotest();
    servo.write(90);
    delay(servoPause);
    delay(2000);
    motortest();
    delay(2000);
    turnRight(255, 1000);
    turnLeft(255,1000);
    delay(2000);
} else if (digitalRead(A2) == LOW) { //A2 on GND to check the sensors
    // Serial.print("Rainsensor: ");
    // Serial.println(RegenSensor.analogread());
    Serial.print("Distance front: ");
    Serial.println(US.getDistance());
    delay(500);
    Serial.print("Distance right: ");
    Serial.println(lookRight());
    delay(500);
    Serial.print("Distance left: ");
    Serial.println(lookLeft());
    // Serial.print("It is ");
    // if (IRunten.isDark() == true) {
    //     Serial.println(" dark.");
    // }
    // else {
    //     Serial.println(" light.");
    // }
    //delay(500);
} else if (digitalRead(A4) == LOW) {
    servo.write(90);
    delay(servoPause);

    motorRight.forward(255);
    motorLeft.forward(255);

    if (US.getDistance() <= 15) {
        motorRight.stop();
        motorLeft.stop();
        delay(500);
        distanceRight = lookRight();
        delay(500);
        distanceLeft = lookLeft();
        delay(500);
        servo.write(90);
        delay(servoPause);

        if (distanceRight == distanceLeft) {
            motorRight.reverse(255);
            motorLeft.reverse(255);
            delay(250);
            motorRight.stop();
            motorLeft.stop();
            distanceRight = lookRight();
            distanceLeft = lookLeft();
        }

        if (distanceRight < distanceLeft) {
            turnLeft(255, 250);
        } else {
            turnRight(255, 250);
        }
    }
}
}