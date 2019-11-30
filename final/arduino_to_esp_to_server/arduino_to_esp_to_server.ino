#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <Wire.h>
#include <SimpleTimer.h>
#include <ESP8266HTTPClient.h>
SoftwareSerial esp(D2,D3);

const char* ssid= "";
const char* password="";

SimpleTimer timer;

String mystring;
char rdata;
float totalVal;

const char* host ="http://192.168.1.105:8000";



void setup()
{
Serial.begin(9600);
esp.begin(9600);

//Connect to wifi 
  Serial.begin(115200);
  delay(10);
  Serial.println('\n');
  WiFi.begin(ssid,password);
  Serial.println("Connecting to ");
  Serial.println(ssid);
  Serial.println("......");
  int i =0;
  while(WiFi.status() !=WL_CONNECTED)
  {
   delay(1000);
   Serial.print(++i);
   Serial.print(' ');
   
  }
Serial.println('\n');
Serial.println("Connection established!");
Serial.print("IP address: \t");
Serial.print("MAC of nodemcu is :");
Serial.print(WiFi.macAddress());
Serial.println(WiFi.localIP());

delay(2000);
timer.setInterval(1000L, totalValue);  //calling user defined function every second to send the data to server 

}

void loop()
{

  if (Serial.available()> 0)
  {
    rdata=Serial.read(); //read the every data from the arduino
    mystring= mystring + rdata;
    if (rdata='\n')
    {
     String l= getValue(mystring, ',' ,0);
     
     totalVal=l.toFloat(); //Convert the string to float value
     

     mystring="";
     

    }
  }
}
void totalValue()
{
  float sdata=totalVal; //value from arduino inform of float to send to server 
  Serial.println(sdata); //print value from arduino to serial monitor
  if (WiFi.status()==WL_CONNECTED)
  {
  HTTPClient client;
//Get request to the server 

  String uri = "http://www.192.168.1.105:8000/housedetails";
  String data = String("?total=") + sdata;
  bool httpResult = client.begin(uri + data);
  if (!httpResult) {
    Serial.println("Invalid HTTP request:");
    Serial.println(uri + data);
  }
  int httpCode = client.GET();
  if (httpCode > 0) 
  { // Request has been made
    Serial.printf("HTTP status: %d\n", httpCode);
    String payload = client.getString();
    Serial.println(payload);
  } 
  else 
  { // Request could not be made
    Serial.printf("HTTP request failed. Error: %s\r\n", client.errorToString(httpCode).c_str());
  }
  client.end();
}
else
{
   Serial.println("Internet Problem!");
    
}

}

String getValue(String data, char separator, int index)
{
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 1;
 
    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
