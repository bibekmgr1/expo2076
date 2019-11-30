


int currentsensor1 = A0;    // select the input pin for currentsensor
int currentsensor2 =A1;
int currentsensor3 =A2;
int currentsensor4=A3;

int relayPin1 = 5;// select the pin for relayoutput
int relayPin2=6;
int relayPin3= 7;
int relayPin4=8;

int sensorValue1 = 0; // variable to store the value coming from the sensor
int sensorValue2=0;
int sensorValue3 = 0;
int sensorValue4 =0;
int sum;


void setup() {
  // declare the currentsenor an INPUT:
  pinMode(currentsensor1,INPUT);
  pinMode(currentsensor2,INPUT);
  pinMode(currentsensor3,INPUT);
  pinMode(currentsensor4,INPUT);
  
//declare the relayPin as OUTPUT:

  pinMode(relayPin1, OUTPUT);
  pinMode(relayPin2, OUTPUT);
  pinMode(relayPin3, OUTPUT);
  pinMode(relayPin4, OUTPUT);

}

void loop() {
  // read the value from the sensor:
  sensorValue1 = analogRead(currentsensor1);
 sensorValue2=analogRead(currentsensor2);
 sensorValue3 = analogRead(currentsensor3);
 sensorValue4 =analogRead(currentsensor4);
 
 sum = (sensorValue1+sensorValue2+sensorValue3+sensorValue4);

 if(sensorValue1 > sensorValue2  && sensorValue1 > sensorValue3 && sensorValue1 > sensorValue4)
  {
    digitalWrite(relayPin1,LOW);
  }
  if(sensorValue2 > sensorValue1  && sensorValue2 > sensorValue3 && sensorValue2 > sensorValue4)
  {
    digitalWrite(relayPin2,LOW);
  }
  if(sensorValue3 > sensorValue1  && sensorValue3 > sensorValue2 && sensorValue3 > sensorValue4)
  {
    digitalWrite(relayPin3,LOW);
  }
  if(sensorValue4 > sensorValue2  && sensorValue4 > sensorValue3 && sensorValue4 > sensorValue3)
  {
    digitalWrite(relayPin4,LOW);
  }
 
 
}
