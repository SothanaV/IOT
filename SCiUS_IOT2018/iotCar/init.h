
void handleRoot() {
  server.send(200, "text/html", "<input type=\"number\" id=\"input1\"><button onclick=\"window.open('/go?method=forward&delay='+String(document.getElementById('input1').value),'_self')\">Forward</button><p></p><input type=\"number\" id=\"input2\"><button onclick=\"window.open('/go?method=backward&delay='+String(document.getElementById('input2').value),'_self')\">Backward</button><p></p><input type=\"number\" id=\"input3\"><button onclick=\"window.open('/go?method=left&delay='+String(document.getElementById('input3').value),'_self')\">Left</button><p></p><input type=\"number\" id=\"input4\"><button onclick=\"window.open('/go?method=right&delay='+String(document.getElementById('input4').value),'_self')\">Right</button>");
}
void handleSet() {
  String Method;
  int Delay;
  for (uint8_t i = 0; i < server.args(); i++) {
    if (server.argName(i) == "method") {
      Method = server.arg(i).c_str();
    }else if(server.argName(i) == "delay"){
      Delay = String(server.arg(i).c_str()).toInt();
    }
  }
  server.sendHeader("Location", String("/"), true);
  server.send ( 302, "text/plain", "");
  if(Method == "forward") motor.forward(Delay);
  else if(Method == "backward") motor.backward(Delay);
  else if(Method == "right") motor.right(Delay);
  else if(Method == "left") motor.left(Delay);
}

void handleDht() {
  int temp = int(dht.readTemperature());
  int humi = int(dht.readHumidity());
  for(int i=0;i<10 && (isnan(temp) || isnan(humi)) ;i++){
    temp = int(dht.readTemperature());
    humi = int(dht.readHumidity());
    delay(100);
  }
  server.send ( 200, "text/plain", String(temp)+","+String(humi));
}

void handleLed() {
  int r,g,b;
  for (uint8_t i = 0; i < server.args(); i++) {
    if (server.argName(i) == "r") {
      r = String(server.arg(i).c_str()).toInt();
    }else if (server.argName(i) == "g") {
      g = String(server.arg(i).c_str()).toInt();
    }else if (server.argName(i) == "b") {
      b = String(server.arg(i).c_str()).toInt();
    }
  }
  led(r,g,b);
  server.sendHeader("Location", String("/"), true);
  server.send ( 302, "text/plain", "");
}

void handleSound() {
  int noteDuration = 0,melody = 0;
  for (uint8_t i = 0; i < server.args(); i++) {
    if (server.argName(i) == "duration") {
      noteDuration = String(server.arg(i).c_str()).toInt();
    }else if (server.argName(i) == "melody") {
      melody = String(server.arg(i).c_str()).toInt();
    }
  }

  tone(pin[7], melody, noteDuration);
  int pauseBetweenNotes = noteDuration * 1.30;
  delay(pauseBetweenNotes);
  noTone(pin[7]);
  
  server.sendHeader("Location", String("/"), true);
  server.send ( 302, "text/plain", "");
}

void Init(){
  Serial.begin(115200);
  Serial.println();
  Serial.print("Configuring access point...");
  /* You can remove the password parameter if you want the AP to be open. */
  //WiFi.softAP(ssid, password);

  // MARK : Wifi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  // MARK : Server
  //IPAddress myIP = WiFi.softAPIP();
  //Serial.print("AP IP address: ");
  //Serial.println(myIP);
  server.on("/", handleRoot);
  server.on("/go", handleSet);
  server.on("/led", handleLed);
  server.on("/dht", handleDht);
  server.on("/sound", handleSound);
  server.begin();
  Serial.println("HTTP server started");

  // MARK : OTA
  ArduinoOTA.setHostname("WEMOS1");
  ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH)
      type = "sketch";
    else // U_SPIFFS
      type = "filesystem";

    // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
    Serial.println("Start updating " + type);
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR) Serial.println("End Failed");
  });
  ArduinoOTA.begin();
  Serial.println("OTA Ready");

  // MARK : Neopixel LED
  pixels.begin();

  // MARK : DHT
  dht.begin();

}

