/* 
 This example was created by Hélder Ribeiro (www.botnroll.com)
 on the 20th March 2018
 
 This code example is in the public domain. 
 https://github.com/botnroll/BnrOneA_ESP32

Description:
Botnroll One A Robot with ESP32 
Test the rgb led on BnrOneA
*/
#include <BnrOneA.h>      // Bot'n Roll ONE A library

BnrOneA one;           // declaration of object variable to control the Bot'n Roll ONE A
#define SSPIN  2       // Slave Select (SS) pin for SPI communication

void setup() 
{
   Serial.println("Connecting to BnrOneA");
   one.spiConnect(SSPIN);   // start the communication module
   Serial.println("Stoping Motors");
   one.stop();              // stop motors
}

void loop() {
  //BOTA shield LED RED
  one.setLEDColor(255,0,0);//Red,Green,Blue
  delay(100);
  //BOTA shield LED GREEN
  one.setLEDColor(0,255,0);//Red,Green,Blue
  delay(100);
  //BOTA shield LED BLUE
  one.setLEDColor(0,0,255);//Red,Green,Blue
  delay(100);
  //BOTA shield LED OFF
  one.setLEDColor(0,0,0);//Red,Green,Blue
  delay(100);

}
