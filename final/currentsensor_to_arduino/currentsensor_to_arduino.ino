
#include <ACS712.h>
#include <SoftwareSerial.h>
SoftwareSerial nodemcu(2,3);// RX pin, TX pin we design

const float sensor1 = A0;   // select the input pin for currentsensor
const float sensor2 = A1;
const float sensor3 = A2;
const float sensor4 = A3;
double total;


int fiadcValue= 0;
double fiadcVoltage = 0;
double ficurrentValue = 0;
int secadcValue= 0;
double secadcVoltage = 0;
double seccurrentValue = 0;
int thiadcValue= 0;
double thiadcVoltage = 0;
double thicurrentValue = 0;
int foradcValue= 0;
double foradcVoltage = 0;
double forcurrentValue = 0;
int fipower=0,secpower=0,thipower=0,forpower=0;




void setup(){
  Serial.begin(9600); // Configuring pin A1 as input

  nodemcu.begin(9600);
  sensor.calibrate();
   // declare the currentsenor an INPUT:
  pinMode(sensor1,INPUT);
  pinMode(sensor2,INPUT);
  pinMode(sensor3,INPUT);
  pinMode(sensor4,INPUT);
  pinMode(relayact,OUTPUT);
  
}
void loop(){
  
   int V=230;
  fiadcValue = analogRead(sensor1);
  fiadcVoltage = (fiadcValue / 1024.0) * 5000;
  ficurrentValue = ((fiadcVoltage - offsetVoltage) / sensitivity);
  fipower= V*ficurrentValue;
  Serial.print("\t Power=");
  Serial.println(fipower);
  
  secadcValue = analogRead(sensor2);
  secadcVoltage = (secadcValue / 1024.0) * 5000;
  seccurrentValue = ((secadcVoltage - offsetVoltage) / sensitivity);
  secpower= V*seccurrentValue;
  Serial.print("\t Power=");
  Serial.println(secpower);
  
  thiadcValue = analogRead(sensor3);
  thiadcVoltage = (thiadcValue / 1024.0) * 5000;
  thicurrentValue = ((thiadcVoltage - offsetVoltage) / sensitivity);
  thipower= V*thicurrentValue;
  Serial.print("\t Power=");
  Serial.println(thipower);
  
  foradcValue = analogRead(sensor4);
  foradcVoltage = (foradcValue / 1024.0) * 5000;
  forcurrentValue = ((foradcVoltage - offsetVoltage) / sensitivity);
  forpower= V*forcurrentValue;
  Serial.print("\t Power=");
  Serial.println(forpower);

  total=fipower+secpower+thipower+forpower;
  Serial.println(total);
  delay(3000);

}

 
