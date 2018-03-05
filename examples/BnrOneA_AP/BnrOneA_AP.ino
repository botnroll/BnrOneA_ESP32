#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event_loop.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "esp_partition.h"
#include "cJSON.h"
#include "soc/rtc.h"
#include "driver/mcpwm.h"
#include "soc/mcpwm_reg.h"
#include "soc/mcpwm_struct.h"

#include <WiFi.h>

#include <Preferences.h>

#define LED 13

//Memory namespace
const char * NamespacePreferences = "BnrOneA";

Preferences memory;

int freqInt = 0;
int intervalInt = 0;

bool WIFI_STATE = false;

//////////////////////
// WiFi Definitions //
//////////////////////
const char WiFiAPP_NAME[] = "BnrOneA";
const char WiFiAPP_PASS[] = "botnroll";

WiFiServer server(80);

#define GPIO_PWM0A_OUT 16   //Set GPIO 16 as PWM0A

void serverTask(void *data);

void setupWiFi()
{
  if(!WIFI_STATE)
  {
    WIFI_STATE = true;

    WiFi.mode(WIFI_AP);

    WiFi.softAP(WiFiAPP_NAME, WiFiAPP_PASS);

    server.begin();

    Serial.print("Connedted to: ");
    Serial.println(WiFiAPP_NAME);

    Serial.println("Acess from: 192.168.4.1");
  }
}




void setup()
{
      // Initialize NVS.
    esp_err_t err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES) {
      // OTA app partition table has a smaller NVS partition size than the non-OTA
      // partition table. This size mismatch may cause NVS initialization to fail.
      // If this happens, we erase NVS partition and initialize NVS again.
      const esp_partition_t* nvs_partition = esp_partition_find_first(
              ESP_PARTITION_TYPE_DATA, ESP_PARTITION_SUBTYPE_DATA_NVS, NULL);
      assert(nvs_partition && "partition table must have an NVS partition");
      ESP_ERROR_CHECK( esp_partition_erase_range(nvs_partition, 0, nvs_partition->size) );
      err = nvs_flash_init();
    }
    ESP_ERROR_CHECK( err );

    //begin namespace
    memory.begin(NamespacePreferences, false);

    pinMode(LED,OUTPUT);

    digitalWrite(LED,LOW);
    
    freqInt = memory.getUInt("FQ",32000);

    intervalInt = memory.getUInt("IN",5000);

    Serial.begin(115200);

    setupWiFi();
}

void loop()
{
   WiFiClient client = server.available();

      if (client)
      {                             // if you get a client,
        Serial.println("new client");           // print a message out the serial port
        String currentLine = "";  // make a String to hold incoming data from the client
        String recieved = "";
        while (client.connected())
        {            // loop while the client's connected
          if (client.available())
          {             // if there's bytes to read from the client,
            char c = client.read();             // read a byte, then
            recieved += c;                    // print it out the serial monitor
            if (c == '\n')
            {                    // if the byte is a newline character

              // if the current line is blank, you got two newline characters in a row.
              // that's the end of the client HTTP request, so send a response:
              if (currentLine.length() == 0)
              {
                // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
                // and a content-type so the client knows what's coming, then a blank line:
                client.println("HTTP/1.1 200 OK");
                client.println("Content-type:text/html");
                client.println();

                // the content of the HTTP response follows the header:
                //client.print(HTML);

                String pp = "";

                //pp =  "<a href='H' style='width:25%;margin-left:50%;margin-top:100px;height:150px;background-color:green;float:left;border-radius:50px;text-align:center;line-height:150px;color:white;'>Ligar</a>";
                //pp += "<a href='L' style='width:25%;margin-left:50%;margin-top:100px;height:150px;background-color:red;float:left;border-radius:50px;text-align:center;line-height:150px;color:white;'>Desligar</a>";
                pp += "{'fq':'"+String(freqInt)+"','tm':'"+String(intervalInt)+"'}";
                client.print(pp);

                // The HTTP response ends with another blank line:
                client.println();
                // break out of the while loop:
                break;
              }
              else
              {    // if you got a newline, then clear currentLine:
                currentLine = "";
              }
            }
             else if (c != '\r')
             {  // if you got anything else but a carriage return character,
              currentLine += c;      // add it to the end of the currentLine
             }
          }

        }

        String request = "";
        if(recieved.indexOf("Android")==-1) request = recieved.substring(recieved.indexOf("Referer: http://192.168.4.1/?")+29,recieved.indexOf("Accept-Encoding:"));
        else request = recieved.substring(recieved.indexOf("GET /?")+6,recieved.indexOf(" HTTP/1.1"));
        Serial.print("Request:");
        Serial.print(request);
        Serial.println("|END");

        if(request.indexOf("fq=")!=-1)
        {
          String val = recieved.substring(recieved.indexOf("fq=")+3,recieved.length());
          printf("NEW FREQ: %s\n",val.c_str());

          freqInt = val.toInt();
          memory.putUInt("FQ",freqInt);
          printf("FreqDefine saved : %ul\n",freqInt);

          //configPWM(freqInt,50);
        }
        else if(request.indexOf("tm=")!=-1)
        {
          String val = recieved.substring(recieved.indexOf("tm=")+3,recieved.length());
          printf("NEW TIME: %s\n",val.c_str());

          intervalInt = val.toInt();
          memory.putUInt("IN",intervalInt);
          printf("intervalInt saved : %ul\n",intervalInt);

        }

        // close the connection:
        client.stop();
        Serial.println("client disonnected");

        delay(100);
      }
}

