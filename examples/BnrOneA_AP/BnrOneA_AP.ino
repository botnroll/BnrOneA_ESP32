#include <WiFi.h>

#define LED 13

int freqInt = 0;
int intervalInt = 0;

bool WIFI_STATE = false;

//////////////////////
// WiFi Definitions //
//////////////////////
const char WiFiAPP_NAME[] = "BnrOneA";
const char WiFiAPP_PASS[] = "botnroll";

WiFiServer server(80);

void setup()
{
    Serial.begin(115200);
    
    pinMode(LED,OUTPUT);
    digitalWrite(LED,LOW);

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
          printf("FreqDefine saved : %ul\n",freqInt);

          //configPWM(freqInt,50);
        }
        else if(request.indexOf("tm=")!=-1)
        {
          String val = recieved.substring(recieved.indexOf("tm=")+3,recieved.length());
          printf("NEW TIME: %s\n",val.c_str());

          intervalInt = val.toInt();
          printf("intervalInt saved : %ul\n",intervalInt);

        }

        // close the connection:
        client.stop();
        Serial.println("client disonnected");
        delay(100);
      }
}

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
