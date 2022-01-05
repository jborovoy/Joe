#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <AccelStepper.h>

AccelStepper LeftBackWheel(1, 4, 7);   // (Type:driver, STEP, DIR) - ZStepper1
AccelStepper LeftFrontWheel(1, 3, 6);  // YStepper2
AccelStepper RightBackWheel(1, A0, A1);  // AStepper3
AccelStepper RightFrontWheel(1, 2, 5); // XStepper4

RF24 radio(9,10);

const byte address [6] = "00001";

struct Data_Package {
  byte leftxval;
  byte leftyval;
  byte rightxval;
  byte rightyval;
  byte speedcontrol;
};

Data_Package data;

int wheelSpeed = 1000;
  
void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
pinMode(2,OUTPUT);
pinMode(3,OUTPUT);
pinMode(4,OUTPUT);
pinMode(5,OUTPUT);
pinMode(6,OUTPUT);
pinMode(7,OUTPUT);
pinMode(A0,OUTPUT);
pinMode(A1,OUTPUT);
LeftFrontWheel.setMaxSpeed(3000);
LeftBackWheel.setMaxSpeed(3000);
RightFrontWheel.setMaxSpeed(3000);
RightBackWheel.setMaxSpeed(3000);
radio.begin();
radio.openReadingPipe (0, address);
radio.setPALevel (RF24_PA_MIN);
radio.setAutoAck(false);
radio.setDataRate(RF24_250KBPS);
radio.startListening();
}

void loop() {
  // put your main code here, to run repeatedly:
if (radio.available()){
    radio.read(&data, sizeof(Data_Package));
}
wheelSpeed = map(data.speedcontrol, 0, 255, 100, 3000);


if (data.leftxval < 100) {
    moveSidewaysLeft();
  }
else if (data.leftxval > 150) {
    moveSidewaysRight();
  }
else if (data.leftyval < 100) {
    moveForward();
  }
else if (data.leftyval > 150) {
    moveBackward();
  }
else if (data.rightxval > 150 & data.rightyval < 100) {
    moveRightForward();
  }
else if (data.rightxval < 100 & data.rightyval < 100) {
    moveLeftForward();
  }
else if (data.rightxval > 150 & data.rightyval > 150) {
    moveRightBackward();
  }
else if (data.rightxval < 100 & data.rightyval > 150) {
    moveLeftBackward();
  }
else if (data.rightxval < 100) {
    rotateLeft();
  }
else if (data.rightxval > 150) {
    rotateRight();
  }
else {
    stopMoving();
}

/*
Serial.print("left xval: ");
Serial.print(data.leftxval);
Serial.print("   left yval: ");
Serial.print(data.leftyval);
Serial.print("    right xval: ");
Serial.print(data.rightxval);
Serial.print("    right yval: ");
Serial.print(data.rightyval);
*/
Serial.print("   speed: ");
Serial.println(wheelSpeed);


LeftFrontWheel.runSpeed();
LeftBackWheel.runSpeed();
RightFrontWheel.runSpeed();
RightBackWheel.runSpeed();



}
void moveForward() {
  LeftFrontWheel.setSpeed(-wheelSpeed);
  LeftBackWheel.setSpeed(-wheelSpeed);
  RightFrontWheel.setSpeed(wheelSpeed);
  RightBackWheel.setSpeed(wheelSpeed);
}
void moveBackward() {
  LeftFrontWheel.setSpeed(wheelSpeed);
  LeftBackWheel.setSpeed(wheelSpeed);
  RightFrontWheel.setSpeed(-wheelSpeed);
  RightBackWheel.setSpeed(-wheelSpeed);
}
void moveSidewaysRight() {
  LeftFrontWheel.setSpeed(-wheelSpeed);
  LeftBackWheel.setSpeed(wheelSpeed);
  RightFrontWheel.setSpeed(-wheelSpeed);
  RightBackWheel.setSpeed(wheelSpeed);
}
void moveSidewaysLeft() {
  LeftFrontWheel.setSpeed(wheelSpeed);
  LeftBackWheel.setSpeed(-wheelSpeed);
  RightFrontWheel.setSpeed(wheelSpeed);
  RightBackWheel.setSpeed(-wheelSpeed);
}
void rotateLeft() {
  LeftFrontWheel.setSpeed(wheelSpeed);
  LeftBackWheel.setSpeed(wheelSpeed);
  RightFrontWheel.setSpeed(wheelSpeed);
  RightBackWheel.setSpeed(wheelSpeed);
}
void rotateRight() {
  LeftFrontWheel.setSpeed(-wheelSpeed);
  LeftBackWheel.setSpeed(-wheelSpeed);
  RightFrontWheel.setSpeed(-wheelSpeed);
  RightBackWheel.setSpeed(-wheelSpeed);
}
void moveRightForward() {
  LeftFrontWheel.setSpeed(-wheelSpeed);
  LeftBackWheel.setSpeed(0);
  RightFrontWheel.setSpeed(0);
  RightBackWheel.setSpeed(wheelSpeed);
}
void moveRightBackward() {
  LeftFrontWheel.setSpeed(0);
  LeftBackWheel.setSpeed(wheelSpeed);
  RightFrontWheel.setSpeed(-wheelSpeed);
  RightBackWheel.setSpeed(0);
}
void moveLeftForward() {
  LeftFrontWheel.setSpeed(0);
  LeftBackWheel.setSpeed(-wheelSpeed);
  RightFrontWheel.setSpeed(wheelSpeed);
  RightBackWheel.setSpeed(0);
}
void moveLeftBackward() {
  LeftFrontWheel.setSpeed(wheelSpeed);
  LeftBackWheel.setSpeed(0);
  RightFrontWheel.setSpeed(0);
  RightBackWheel.setSpeed(-wheelSpeed);
}
void stopMoving() {
  LeftFrontWheel.setSpeed(0);
  LeftBackWheel.setSpeed(0);
  RightFrontWheel.setSpeed(0);
  RightBackWheel.setSpeed(0);
}
