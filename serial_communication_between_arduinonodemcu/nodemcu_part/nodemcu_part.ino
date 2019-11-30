#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <SimpleTimer.h>                                                                        
                                                                                                                                                                    
SoftwareSerial fromUno(D6,D5); //rx to tx
#include <ArduinoJson.h> 
char *ssid= "BBC";
char *password="Mylovelymom1";
double totalVal;
String mystring;
char rdata;
 
void setup() {
  // Initialize Serial port
  WiFi.begin(ssid,password);
  fromUno.begin(9600);
  Serial.begin(112500);
  while(WiFi.status()!=WL_CONNECTED)
  {
    
    Serial.print(".");                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    
    delay(500);
  }
 Serial.println("IP Address:");
 Serial.println(WiFi.localIP());
 
 while(!Serial) continue;
 
 
}

 
void loop() {
  
  if (fromUno.available()> 0)
  {
    rdata=fromUno.read(); //read the every data from the arduino
    Serial.print("something herer");
    Serial.print(rdata)l;
    mystring= mystring + rdata;
    if (rdata='\n')
    {
     String l= getValue(mystring, ',' ,0);
     
     totalVal=l.toFloat(); //Convert the string to float value
     

     mystring="";
     

    }
  }
  
  
  HTTPClient http;    //Declare object of class HTTPClient
 
  DynamicJsonBuffer jsonBuffer;
  JsonObject& request= jsonBuffer.createObject(); 
  request["name"] = "gotach";  //String to interger conversion
  request["power_consumption"] = totalVal;  

  char jsonmessageBuffer[300];
  request.prettyPrintTo(jsonmessageBuffer, sizeof(jsonmessageBuffer));
  Serial.println(jsonmessageBuffer);
    
  http.begin("http://192.168.1.105:8000/housedetails");              //Specify request destination
  http.addHeader("Content-Type", "application/json");    //Specify content-type header
 
  int httpCode = http.POST(jsonmessageBuffer); //Send the request
  //Check the returning code
  if(httpCode>0){
    
  const size_t bufferSize =JSON_OBJECT_SIZE(2) +JSON_OBJECT_SIZE(3)+JSON_OBJECT_SIZE(5)+JSON_OBJECT_SIZE(8)+370;
  DynamicJsonBuffer jsonBuffer(bufferSize);
  JsonObject& root= jsonBuffer.parseObject(http.getString());
    ///Parameters
  boolean Status =root["status"];
  //Output to serial monitor
  Serial.print("Status:");
  Serial.print(Status);
  fromUno.write (Status);
  delay(10000);
  
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
