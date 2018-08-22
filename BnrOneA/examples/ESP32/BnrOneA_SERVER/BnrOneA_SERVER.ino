#include <BnrOneA.h>      // Bot'n Roll ONE A library
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <ArduinoOTA.h>   // ESP 32 OTA lib

const char *ssid = "ZON-2006";//YourSSIDHere
const char *password = "5454545454545";//YourPSKHere

WebServer server(80);

BnrOneA one;           // declaration of object variable to control the Bot'n Roll ONE A
#define SSPIN  2       // Slave Select (SS) pin for SPI communication

void handleRoot() 
{
  String html_code = get_index();
  int size_index = html_code.length();
  char temp[size_index];
  snprintf(temp,size_index,html_code.c_str());
  server.send(200, "text/html", temp);
}

void handleJoy() 
{
  String html_code = get_joystick_page();
  int size_index = html_code.length();
  char temp[size_index];
  snprintf(temp,size_index,html_code.c_str());
  server.send(200, "text/html", temp);
}

void handleLcd() 
{
  String html_code = get_lcd_page();
  int size_index = html_code.length();
  char temp[size_index];
  snprintf(temp,size_index,html_code.c_str());
  server.send(200, "text/html", temp);
}

void handleNotFound() 
{
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";

  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }

  server.send(404, "text/plain", message);
}

void drawGraph() 
{
  String out = "";
  char temp[100];
  out += "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" width=\"400\" height=\"150\">\n";
  out += "<rect width=\"400\" height=\"150\" fill=\"rgb(250, 230, 210)\" stroke-width=\"1\" stroke=\"rgb(0, 0, 0)\" />\n";
  out += "<g stroke=\"black\">\n";
  int y = rand() % 130;
  for (int x = 10; x < 390; x += 10) 
  {
    int y2 = rand() % 130;
    sprintf(temp, "<line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" stroke-width=\"1\" />\n", x, 140 - y, x + 10, 140 - y2);
    out += temp;
    y = y2;
  }
  out += "</g>\n</svg>\n";
  server.send(200, "image/svg+xml", out);
}

void returnFail(String msg) {
  server.send(500, "text/plain", msg + "\r\n");
}

void ledControl()
{
  if(!server.hasArg("l")) {
    return returnFail("BAD ARGS, ?l=0 or ?l=1");
  }
  String path = server.arg("l");
  if (path != "1" && path != "0") 
  {
    return returnFail("BAD acess, ?l=0 or ?l=1 ");
  }
  else if(path == "1") {
    one.setLEDColor(0,255,0);//Red,Green,Blue
    String json = "{";
    json += "led:on";
    json += "}";
    server.send(200, "text/json", json);
  }
  else {
    one.setLEDColor(0,0,0);//Red,Green,Blue
    String json = "{";
    json += "led:off";
    json += "}";
    server.send(200, "text/json", json);
  }
}

void controled()
{
  int x = -server.arg("x").toInt()/2;
  int y = -server.arg("y").toInt()/2;
  if(x<-100) x = -100; 
  else if(x>100)  x = 100; 
  if(y<-100) y = -100; 
  else if(y>100)  y = 100; 
  int V =(100-abs(x)) * (y/100) + y;   
  int W = (100-abs(y)) * (x/100) + x; 
  int left = (V-W) /2;
  int right = (V+W) /2; 
  one.move(left,right);
  //Serial.println(x+":"+y);
  String json = "{ control:ok }";
  server.send(200, "text/json", json);
 
}

void lcd_control()
{
    String txt1 = server.arg("line1");
    String txt2 = server.arg("line2");
    one.lcd1(txt1); // print data on LCD line 1
    one.lcd2(txt2); // print data on LCD line 2
    String json = "{ lcd:ok }";
    server.send(200, "text/json", json);
} 

void setup(void) 
{
  setupOTA();
  Serial.begin(115200);
  Serial.println("Connecting to BnrOneA");
  one.spiConnect(SSPIN);   // start the communication module
  Serial.println("Stoping Motors");
  one.stop();              // stop motors
   
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }

  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  
  if (MDNS.begin("esp32"))
  {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);
  server.on("/led", HTTP_GET, ledControl);
  server.on("/joy", HTTP_GET, handleJoy);
  server.on("/lcd", HTTP_GET, handleLcd);
  server.on("/cntrl", HTTP_GET, controled);
  server.on("/lcd_control", HTTP_GET, lcd_control);
  server.on("/test.svg", drawGraph);
  server.on("/inline", []() 
  {
    server.send(200, "text/plain", "this works as well");
  });
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");

  one.lcd1("SSID: "+String(ssid)); // print data on LCD line 1
  one.lcd2("IP:"+WiFi.localIP().toString()); // print data on LCD line 2
}

void loop(void) 
{
  updateOTA();//Function necessary to OTA update
  server.handleClient();
}
