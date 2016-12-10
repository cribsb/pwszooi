#include <NewPing.h>


#define leapTime 200

#define leftMotor1  3
#define leftMotor2  2

#define rightMotor1 5
#define rightMotor2 4

#define led 13

NewPing sonar(12, 11, 300);
#define turndelay 372

char path[250] = {};
int pathLength = 0;
int readLength;

int replaystage;

void setup() {

  //pinMode(leftCenterSensor, INPUT);
  //pinMode(leftNearSensor, INPUT);
  //pinMode(leftFarSensor, INPUT);
  //pinMode(rightCenterSensor, INPUT);
  //pinMode(rightNearSensor, INPUT);
  //pinMode(rightFarSensor, INPUT);
  //pinMode(middleSensorPin, INPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  analogWrite(9, 155);
  analogWrite(10, 155);

  pinMode(leftMotor1, OUTPUT);
  pinMode(leftMotor2, OUTPUT);
  pinMode(rightMotor1, OUTPUT);
  pinMode(rightMotor2, OUTPUT);
  pinMode(led, OUTPUT);
  Serial.begin(115200);
  digitalWrite(led, HIGH);
  delay(10000);
}

boolean canGo = false;

boolean klaar = false;

void loop() {

  int distance = fping();

  klaar = (distance > 150);
  if (klaar)
  {
    straight();
    straight();
    straight();
    done();
  }

  canGo = (distance > 20);

  right();

  if (fping() > 20)
  {
    straight();
    path[pathLength] = 'R';
    pathLength++;

  }
  else if (canGo)
  {
    left();
    straight();
    path[pathLength] = 'S';
    pathLength++;
  }
  else
  {
    left();
    if (fping() > 20)
    {
      straight();
      path[pathLength] = 'L';
      pathLength++;
    }
    else
    {
      turnaround();
      straight();
      path[pathLength] = 'B';
      pathLength++;
    }
  }

}

void straight()
{
  int dist = fping();
  int dist2 = 0;
  bool oke = true;
  digitalWrite(leftMotor1, HIGH);
  digitalWrite(leftMotor2, LOW);
  digitalWrite(rightMotor1, HIGH);
  digitalWrite(rightMotor2, LOW);

  while (oke)
  {
    dist2 = fping();
    if(dist2 < dist - 20)
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

int fping()
{
  int totaldist = 0;
  for(int i = 0; i < 10; ++i)
  {
    totaldist += sonar.ping_cm();
    delay(1);
  }
  return totaldist/10;
}

void left()
{
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
}

void turnaround()
{
  digitalWrite(leftMotor1, HIGH);
  digitalWrite(leftMotor2, LOW);
  digitalWrite(rightMotor1, LOW);
  digitalWrite(rightMotor2, HIGH);

  delay(turndelay * 2);

  digitalWrite(leftMotor1, LOW);
  digitalWrite(leftMotor2, LOW);
  digitalWrite(rightMotor1, LOW);
  digitalWrite(rightMotor2, LOW);

  delay(500);
}

void right()
{
  digitalWrite(leftMotor1, HIGH);
  digitalWrite(leftMotor2, LOW);
  digitalWrite(rightMotor1, LOW);
  digitalWrite(rightMotor2, HIGH);

  delay(turndelay);

  digitalWrite(leftMotor1, LOW);
  digitalWrite(leftMotor2, LOW);
  digitalWrite(rightMotor1, LOW);
  digitalWrite(rightMotor2, LOW);

  delay(500);
}

void done() {
  digitalWrite(leftMotor1, LOW);
  digitalWrite(leftMotor2, LOW);
  digitalWrite(rightMotor1, LOW);
  digitalWrite(rightMotor2, LOW);
  replaystage = 1;
  path[pathLength] = 'D';
  pathLength++;
  shortPath();
  delay(15000);
  replay();
}


void shortPath() {
  int shortDone = 0;
  if (path[pathLength - 3] == 'L' && path[pathLength - 1] == 'R') {
    pathLength -= 3;
    path[pathLength] = 'B';
    //Serial.println("test1");
    shortDone = 1;
  }

  if (path[pathLength - 3] == 'L' && path[pathLength - 1] == 'S' && shortDone == 0) {
    pathLength -= 3;
    path[pathLength] = 'R';
    //Serial.println("test2");
    shortDone = 1;
  }

  if (path[pathLength - 3] == 'R' && path[pathLength - 1] == 'L' && shortDone == 0) {
    pathLength -= 3;
    path[pathLength] = 'B';
    //Serial.println("test3");
    shortDone = 1;
  }


  if (path[pathLength - 3] == 'S' && path[pathLength - 1] == 'L' && shortDone == 0) {
    pathLength -= 3;
    path[pathLength] = 'R';
    //Serial.println("test4");
    shortDone = 1;
  }

  if (path[pathLength - 3] == 'S' && path[pathLength - 1] == 'S' && shortDone == 0) {
    pathLength -= 3;
    path[pathLength] = 'B';
    //Serial.println("test5");
    shortDone = 1;
  }
  if (path[pathLength - 3] == 'L' && path[pathLength - 1] == 'L' && shortDone == 0) {
    pathLength -= 3;
    path[pathLength] = 'S';
    //Serial.println("test6");
    shortDone = 1;
  }

  path[pathLength + 1] = 'D';
  path[pathLength + 2] = 'D';
  pathLength++;
  //Serial.print("Path length: ");
  //Serial.println(pathLength);
  //printPath();
}

void printPath() {
  Serial.println("+++++++++++++++++");
  int x;
  while (x <= pathLength) {
    Serial.println(path[x]);
    x++;
  }
  Serial.println("+++++++++++++++++");
}


void replay() {
  if (path[readLength] == 'D') {
    digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
    delay(100);
    digitalWrite(leftMotor1, LOW);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, LOW);
    digitalWrite(rightMotor2, LOW);
    //endMotion();
  }
  if (path[readLength] == 'L') {
    digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
    delay(leapTime);
    left();
  }
  if (path[readLength] == 'R') {
    digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
    delay(leapTime);
    right();
  }
  if (path[readLength] == 'S') {
    digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
    delay(leapTime);
    straight();
  }

  readLength++;

  replay();

}

void endMotion() {
  digitalWrite(led, LOW);
  delay(500);
  digitalWrite(led, HIGH);
  delay(200);
  digitalWrite(led, LOW);
  delay(200);
  digitalWrite(led, HIGH);
  delay(500);
  endMotion();
}
