/* 
 This example was created by Hélder Ribeiro (www.botnroll.com)
 on the 20th March 2018
 
 This code example is in the public domain. 
 https://github.com/botnroll/BnrOneA_ESP32

Description:
Botnroll One A Robot with ESP32 
Over The Air Programming basic example
*/
#include <BnrOneA.h>      // Bot'n Roll ONE A library
#include <WiFi.h>         // ESP32 WifiLib
#include <ESPmDNS.h>      // ESP 32 DNS lib
#include <WiFiUdp.h>      // ESP 32 UDP lib
#include <ArduinoOTA.h>   // ESP 32 OTA lib

const char* ssid = "BnrOneA";         //Router SSID
const char* password = "botnroll01";  //Router password

BnrOneA one;           // declaration of object variable to control the Bot'n Roll ONE A
#define SSPIN  2       // Slave Select (SS) pin for SPI communication

void setup() 
{
   setupOTA();

   Serial.println("Connecting to BnrOneA");
   one.spiConnect(SSPIN);   // start the communication module
   Serial.println("Stoping Motors");
   one.stop();              // stop motors
   Serial.println("BOTA shield LED OFF");
   one.setLEDColor(0,0,0);//Red Green Blue
    
   one.lcd1("SSID: "+String(ssid)); // print data on LCD line 1
   one.lcd2("IP:"+WiFi.localIP().toString()); // print data on LCD line 2

   Serial.print("IP address: ");
   Serial.println(WiFi.localIP().toString());
}

void loop()
{
  updateOTA();//Function necessary to OTA update

  //BOTA shield LED GREEN
  one.setLEDColor(0,255,0);//Red,Green,Blue
  delay(100);
  //BOTA shield LED OFF
  one.setLEDColor(0,0,0);//Red,Green,Blue
  delay(100);
  
}
