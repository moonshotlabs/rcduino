#include <SoftwareSerial.h>

int bluetoothTx = 3;
int bluetoothRx = 2;
SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);

// flags
const int FORWARD = 0x01;
const int FLEFT = 0x02;
const int FRIGHT = 0x03;
const int REVERSE= 0x04;
const int RLEFT = 0x05;
const int RRIGHT = 0x06;

// pinsm
const int DRIVEDIR = 11;
const int DRIVEPOW = 10;
const int TURNDIR = 9;
const int TURNPOW = 8;

void setup()
{
  //Setup usb serial connection to computer
  Serial.begin(9600);

  //Setup Bluetooth serial connection to android
  bluetooth.begin(115200);
  bluetooth.print("$$$");
  delay(100);
  bluetooth.println("U,9600,N");
  bluetooth.begin(9600);
}

void loop()
{
  clearInstructions();
  
  //Read from bluetooth and write to usb serial
  if(bluetooth.available())
  {
    byte command = bluetooth.read();
    Serial.println(command);
    handleCommand(command);
  }
  
  delay(200);

//  //Read from usb serial to bluetooth
//  if(Serial.available())
//  {
//    char toSend = (char)Serial.read();
//    bluetooth.print(toSend);
//  }
}

void handleCommand(int command) {
  switch(command) {
    case FORWARD:
      Serial.println("FORWARD!!");
      goForward();
      break;
    case FLEFT:
      turnLeft();
      goForward();
      break;
    case FRIGHT:
      turnRight();
      goForward();
      break;
    case REVERSE:
      goBackward();
      break;
    case RLEFT:
      turnLeft();
      goBackward();
      break;
    case RRIGHT:
      turnRight();
      goForward();
      break;
  }
}

void clearInstructions() {
  digitalWrite(DRIVEDIR, LOW);
  digitalWrite(DRIVEPOW, LOW);
  digitalWrite(TURNDIR, LOW);
  digitalWrite(TURNPOW, LOW);
}

void goForward() {
  digitalWrite(DRIVEDIR, LOW);
  digitalWrite(DRIVEPOW, HIGH);
}

void goBackward() {
  digitalWrite(DRIVEDIR, HIGH);
  digitalWrite(DRIVEPOW, HIGH);
}

void turnRight() {
  digitalWrite(TURNDIR, HIGH);
  digitalWrite(TURNPOW, HIGH);
}

void turnLeft() {
  digitalWrite(TURNDIR, LOW);
  digitalWrite(TURNPOW, HIGH);
}
