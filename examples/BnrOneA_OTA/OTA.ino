//DONT EDIT THIS FILE!
//NECESSARY FILE TO OTA(OVER THE AIR) PROGRAMMING

void setupOTA()
{
  Serial.begin(115200);//Default ESP32 baudrate
  Serial.println("Booting");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) 
  {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }

  // Hostname defaults to esp3232-[MAC]
  ArduinoOTA.setHostname("BnrOneA");

  ArduinoOTA
    .onStart([]() {
      String type;
      if (ArduinoOTA.getCommand() == U_FLASH)
        type = "sketch";
      else // U_SPIFFS
        type = "filesystem";

      // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
      Serial.println("Download program " + type);
      one.lcd1("Downloading...");
    })
    .onEnd([]() {
      Serial.println("\nEnd");
      one.lcd1("SUCESS");
      one.lcd2("Update DONE");
    })
    .onProgress([](unsigned int progress, unsigned int total) {
      int percent = (progress *100 / total);
      Serial.printf("Progress: %d",percent);
      String data = "Program: "+String(percent)+"%%";
      one.lcd2(data);
    })
    .onError([](ota_error_t error) {
      Serial.printf("Error[%u]: ", error);
      if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
      else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
      else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
      else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
      else if (error == OTA_END_ERROR) Serial.println("End Failed");
    });

   ArduinoOTA.begin();
}

void updateOTA()
{
  ArduinoOTA.handle();
}

