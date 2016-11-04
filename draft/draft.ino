#define legoSensorPin 15 // digital pin D14 is analog pin A0
#define legoSensor 1

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  int raw=ReadLegoSensor(); // we read the raw value of the sensor
  Serial.print("Raw value: ");
  Serial.println(raw); // and print it to the monitor
}

int ReadLegoSensor(){
  pinMode(legoSensorPin, OUTPUT); //set pin as output
  digitalWrite(legoSensorPin, HIGH); //set output high
  delay(10); // wait a bit
  pinMode(legoSensorPin, INPUT); //set pin as input
  int value=analogRead(legoSensor); //read the input
  return value; //return the raw value
}
