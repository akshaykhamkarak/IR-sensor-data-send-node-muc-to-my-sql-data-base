#include<SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#define rxpin D1
#define txpin D2

String url="http://192.168.43.3:80/toll/acceptToll.php?tollId=1&id=";
char iid[4];
int count=0;
bool flag=false;
const char* ssid     = "ME";
const char* password = "12121212";
HTTPClient http;



String id=String("1");
String temp=String("1");
SoftwareSerial softSerial=SoftwareSerial(rxpin,txpin,true);
void setup() {
  Serial.begin(19200);
   WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
     while (WiFi.status() != WL_CONNECTED) 
          {
            delay(500);
            Serial.print(".");
            
          }
          Serial.println("");
      Serial.println("WiFi connected");

      
  // put your setup code here, to run once:
softSerial.begin(38400);

String s="\nm u \nazas";
s.trim();
Serial.println(s);


}

void loop() {
  // put your main code here, to run repeatedly:
while(softSerial.available()>0){

  // temp.remove(0,temp.length());
  
  temp=String(softSerial.readString());
  
 /*if(flag==false&&softSerial.read()=='@'){
  flag=true;
  
  }else if(flag==true&&softSerial.read()=='#'){
    count=0;
    flag=false;

    }else if(flag==true){
          iid[count]=softSerial.read();
          count++;
      }*/
  
  }
/*
if(count!=0){
Serial.println(iid[0]);}
*/

 temp.trim();
 temp=temp.substring(0,12);
   if(temp.equals(id)){
    
    }else{

     //   id.remove(0,id.length());
       id=String(temp);
       Serial.println("in else");
    Serial.print(id); 
   // String req=String(url);
   // req+=id;
     Serial.println(url+id);
     http.begin(url+id);
     int code= http.GET();
     Serial.println(code);
     if (code > 0) 
    {

      const size_t bufferSize = JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(3) + JSON_OBJECT_SIZE(5) + JSON_OBJECT_SIZE(8) + 370;
      DynamicJsonBuffer jsonBuffer(bufferSize);
      JsonObject& root = jsonBuffer.parseObject(http.getString());
 
      //int id = root["id"]; 
      const char* name = root["success"]; 
      const char* username = root["message"]; 
     // const char* email = root["email"]; 

      Serial.print("Name:");
      Serial.println(name);
      Serial.print("Username:");
      Serial.println(username);
     
    }
     http.end();
 
       
      }

    

}
