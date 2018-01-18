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
int lookright() {
    int distance = 0;
    servo.write(10);
    delay(150);
    distance = US.getDistance();
    servo.write(90);
    delay(servoPause);
    return distance;
}

// look to the left and get distance
int lookleft() {
    int distance = 0;
    servo.write(170);
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
}

void setup() {
    /* pinMode(2, OUTPUT);
    pinMode(3, OUTPUT);
    pinMode(9, OUTPUT);

    pinMode(5, OUTPUT);
    pinMode(4, OUTPUT);
    pinMode(10, OUTPUT); */
    
    servo.attach(12); // that's the servo pin
    delay(servoPause);
    servo.write(90); // ultrasonic sensor facing ahead
    delay(servoPause); 
    Serial.begin(9600); 
	Serial.println("My Robot");
	Serial.println("--------");
}

void loop() {
    // Serial.print("Rainsensor: ");
    // Serial.println(RegenSensor.analogread());
    /* Serial.print("Distance front: ");
    Serial.println(US.getDistance());
    delay(500);
    Serial.print("Distance right: ");
    Serial.println(lookright());
    delay(500);
    Serial.print("Distance left: ");
    Serial.println(lookleft()); */
    // Serial.print("It is ");
    // if (IRunten.isDark() == true) {
    //     Serial.println(" dark.");
    // }
    // else {
    //     Serial.println(" light.");
    // }
    //delay(500);


    /* 
    digitalWrite(2, HIGH);
    digitalWrite(3, LOW);
    analogWrite(9, 255);
    delay(1000);
    analogWrite(9,0);
    digitalWrite(2, LOW);
    digitalWrite(3, HIGH);
    analogWrite(9, 255);
    delay(1000);
    analogWrite(9,0);
    delay(3000);

    digitalWrite(4, HIGH);
    digitalWrite(5, LOW);
    analogWrite(10, 255);
    delay(1000);
    analogWrite(10,0);
    digitalWrite(4, LOW);
    digitalWrite(5, HIGH);
    analogWrite(10, 255);
    delay(1000);
    analogWrite(10,0);
    delay(3000); */

    servotest();
    servo.write(90);
    delay(servoPause);
    motortest();

}