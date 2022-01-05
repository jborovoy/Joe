#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7,8);

const byte address [6] = "00001";

struct Data_Package {
  byte leftxval;
  byte leftyval;
  byte rightxval;
  byte rightyval;
  byte speedcontrol;
};

Data_Package data;

void setup() {
  // put your setup code here, to run once:
pinMode(A0, INPUT);
pinMode(A1, INPUT);
pinMode(A2, INPUT);
pinMode(A3, INPUT);
pinMode(A4, INPUT);
Serial.begin(9600);
radio.begin();
radio.openWritingPipe (address);
radio.setAutoAck(false);
radio.setDataRate(RF24_250KBPS);
radio.setPALevel (RF24_PA_MIN);
radio.stopListening();
}

void loop() {
  // put your main code here, to run repeatedly:
data.leftxval = map(analogRead(A0), 0, 1023, 0, 255);
data.leftyval = map(analogRead(A1), 0, 1023, 0, 255);
data.rightxval = map(analogRead(A3), 0, 1023, 0, 255);
data.rightyval = map(analogRead(A4), 0, 1023, 0, 255);
data.speedcontrol = map(analogRead(A2), 0, 1023, 0, 255); 
Serial.print("left xval: ");
Serial.print(data.leftxval);
Serial.print("   left yval: ");
Serial.print(data.leftyval);
Serial.print("    right xval: ");
Serial.print(data.rightxval);
Serial.print("    right yval: ");
Serial.print(data.rightyval);
Serial.print("   speed: ");
Serial.println(data.speedcontrol);

radio.write(&data, sizeof(Data_Package));
}
