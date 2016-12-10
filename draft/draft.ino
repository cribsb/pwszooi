#include <NewPing.h>

#define leftCenterSensor   3
#define leftNearSensor     4
#define leftFarSensor      5
#define rightCenterSensor  2
#define rightNearSensor    1
#define rightFarSensor     0
#define middleSensorPin    0

int leftCenterReading;
int leftNearReading;
int leftFarReading;
int rightCenterReading;
int rightNearReading;
int rightFarReading;
int middleReading;

int leftNudge;
int replaystage;
int rightNudge;

#define leapTime 200

#define leftMotor1  3
#define leftMotor2  2

#define rightMotor1 5
#define rightMotor2 4

#define led 13

#define border 200

NewPing sonar(12, 11, 300);
#define turndelay 372

char path[250] = {};
int pathLength = 0;
int readLength;

void setup() {

  //pinMode(leftCenterSensor, INPUT);
  //pinMode(leftNearSensor, INPUT);
  //pinMode(leftFarSensor, INPUT);
  //pinMode(rightCenterSensor, INPUT);
  //pinMode(rightNearSensor, INPUT);
  //pinMode(rightFarSensor, INPUT);
  pinMode(middleSensorPin, INPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  analogWrite(9, 155);
  analogWrite(10, 140);

  pinMode(leftMotor1, OUTPUT);
  pinMode(leftMotor2, OUTPUT);
  pinMode(rightMotor1, OUTPUT);
  pinMode(rightMotor2, OUTPUT);
  pinMode(led, OUTPUT);
  Serial.begin(115200);
  digitalWrite(led, HIGH);
  delay(5000);

  analogWrite(9, 155);
  analogWrite(10, 155);
}

int fping()
{
  int totaldist = 0;
  for (int i = 0; i < 10; ++i)
  {
    totaldist += sonar.ping_cm();
    delay(1);
  }
  return totaldist / 10;
}


int dist2 = 0;

void loop() {

  int dist = fping();
  digitalWrite(leftMotor1, HIGH);
  digitalWrite(leftMotor2, LOW);
  digitalWrite(rightMotor1, LOW);
  digitalWrite(rightMotor2, HIGH);

  delay(turndelay);

  digitalWrite(leftMotor1, LOW);
  digitalWrite(leftMotor2, LOW);
  digitalWrite(rightMotor1, LOW);
  digitalWrite(rightMotor2, LOW);

  digitalWrite(leftMotor1, LOW);
  digitalWrite(leftMotor2, HIGH);
  digitalWrite(rightMotor1, HIGH);
  digitalWrite(rightMotor2, LOW);

  delay(turndelay);

  digitalWrite(leftMotor1, LOW);
  digitalWrite(leftMotor2, LOW);
  digitalWrite(rightMotor1, LOW);
  digitalWrite(rightMotor2, LOW);

  delay(500);

  delay(500);
  bool oke = true;
  delay(3);
  digitalWrite(leftMotor1, HIGH);
  digitalWrite(leftMotor2, LOW);
  digitalWrite(rightMotor1, HIGH);
  digitalWrite(rightMotor2, LOW);

  while (oke == true)
  {
    dist2 = fping();
    if (dist2 < (dist - 20))
    {
      oke = false;
    }
  }

  digitalWrite(leftMotor1, LOW);
  digitalWrite(leftMotor2, LOW);
  digitalWrite(rightMotor1, LOW);
  digitalWrite(rightMotor2, LOW);

  delay(500);
}
