#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include<ArduinoJson.h>


const char *ssid = "BBC"; 

const char *password = "Mylovelymom1";

const char *host = "http://192.168.1.105:8000"; ///website or IP address of server

void setup() {

delay(1000);
Serial.begin(115200);
WiFi.mode(WIFI_OFF); //Prevents reconnection issue (taking too long to connect)
delay(1000);
WiFi.mode(WIFI_STA); //This line hides the viewing of ESP as wifi hotspot
WiFi.begin(ssid, password); //Connect to your WiFi router
Serial.println("");
Serial.print("Connecting");
// Wait for connection
while (WiFi.status() != WL_CONNECTED) {
delay(500);
Serial.print(".");
}
//If connection successful show IP address in serial monitor
Serial.println("");
Serial.print("Connected to ");
Serial.println(ssid);
Serial.print("IP address: ");
Serial.println(WiFi.localIP()); //IP address assigned to your ESP
}

void loop() {

  
  HTTPClient http;    //Declare object of class HTTPClient
 
  DynamicJsonBuffer jsonBuffer;
  JsonObject& request= jsonBuffer.createObject(); 
  request["name"] = "serial";  //String to interger conversion
  request["power_consumption"] = 10;  

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
  const boolean Status =root["status"];
  //Output to serial monitor
  if(Status==false){
    Serial.print("boolean here");
  }
  http.end();  //Close connection

  delay(10000);  //Post Data at every 10 seconds
}
}
//======================================
