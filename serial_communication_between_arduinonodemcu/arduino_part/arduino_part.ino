

#include<SoftwareSerial.h>
#include<ArduinoJson.h>
#include<stdlib.h>
#include<stdio.h>
#include<math.h>
SoftwareSerial toNode(5,6); ///rx and tx


int sensitivity = 100; /// 100 for 20A; 66 for 30A 
int offsetVoltage = 2470;  //offsetvalue i.e. current sensor gives 2.5V before switch on. 
 
const int sensor1 = A0;
const int sensor2= A1;



int fiadcValue= 0;
double fiadcVoltage = 0;
double ficurrentValue = 0;
int fipower=0;
int secadcValue= 0;
double secadcVoltage = 0;
double seccurrentValue = 0;
double secpower=0;
double total=0;
 
void setup() 
{
  Serial.begin(9600);
  toNode.begin(9600);
  Serial.print(" Current Sensor with Arduino ");
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  delay(1000);
}
 
void loop()
{
 

  int   V=230;
  fiadcValue = analogRead(sensor1);
  fiadcVoltage = (fiadcValue / 1024.0) * 5000;
  ficurrentValue = ((fiadcVoltage - offsetVoltage) / sensitivity);
  fipower= V*ficurrentValue;
  
  Serial.print("1st ADC Value =     ");
  Serial.print(fiadcValue);
  delay(2000);
  Serial.print("\t 1stCurrent = ");
  Serial.println(ficurrentValue);
  Serial.print("\t 1stPower=");
  Serial.println(fipower);
  
  delay(2500);
  secadcValue = analogRead(sensor2);
  secadcVoltage = (secadcValue / 1024.0) * 5000;
  seccurrentValue = ((secadcVoltage - offsetVoltage) / sensitivity);
  secpower= V*seccurrentValue;
  
  Serial.print("2nd ADC Value =     ");
    Serial.print(secadcValue);
  Serial.print("\t 2stCurrent = ");
  Serial.println(seccurrentValue);
  Serial.print("\t 2nd Power=");
  Serial.println(secpower);
  
  total=fipower+secpower;
  Serial.println("\n total is :");
  Serial.println(total);
  
  

  parsefloat(total);

//data send from nodemcu to arduino
  if(toNode.available()>0){
  boolean Status = toNode.read();
  Serial.print("finally code is complete");
  }
  delay(10000);
}
void parsefloat(double totalstr){
  
  toNode.println(totalstr);
}
 
