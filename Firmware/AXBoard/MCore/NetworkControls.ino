/*************************************
  Networks - YamaX Arduino Core v3.0
  ネットワーク制御ブロック
  made by coord.e, Y-modify
  Copyright © 2016 Y-modify All Rights Reserved.
*************************************/

#if defined(S_WIFI)  //Only Wifi Support

#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <EEPROM.h>
#include <ESP8266HTTPClient.h>

/*****Wifi Settings*****/
#define ESPHOST "yamax-ota"
#define ESPSERVER "yamax"
#define ESPSETADDR 0

#define COMURL "http://debug.y-modify.org/axboard-remote/command.txt"
#define CTRLURL "http://debug.y-modify.org/axboard-remote/control.html"
#define CONURL "http://debug.y-modify.org/axboard-remote/console.html"

struct WiFiConfig {
  char ssid[32];
  char pass[32];
};

/*****Object Making*****/
ESP8266WebServer server(80);

/*****Initialization for Wifi*****/
void NetInit() {
  EEPROM.begin(100);
  WiFiConfig buf;
  EEPROM.get<WiFiConfig>(ESPSETADDR, buf);
  WiFi.mode(WIFI_STA);
  WiFi.begin(buf.ssid, buf.pass);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Scanning other networks...");
    int n = WiFi.scanNetworks();
    Serial.println("Scan done");
    if (n == 0)
      Serial.println("No networks found. Continue with non-wifi enviromnent");
    else
    {
      Serial.print(n);
      Serial.println(" networks found");
      for (int i = 0; i < n; ++i)
      {
        // Print SSID and RSSI for each network found
        Serial.print(i + 1);
        Serial.print(": ");
        Serial.print(WiFi.SSID(i));
        Serial.print(" (");
        Serial.print(WiFi.RSSI(i));
        Serial.print(")");
        Serial.println((WiFi.encryptionType(i) == ENC_TYPE_NONE) ? " " : "*");
        delay(10);
      }
    }
    Serial.println("Enter the number: ");
    while (!Serial.available()) {
      delay(100);
    }
    int num = Serial.parseInt();
    Serial.print("Connect to "); Serial.println(WiFi.SSID(num - 1));
    Serial.println("Enter the password: ");
    while (Serial.available()) Serial.read(); //While data is available, read data (Clean buffer)
    while (!Serial.available()) {
      delay(100);
    }
    char buf[31];
    for (int j = 0; j < 30; j++) {
      buf[j] = Serial.read();
      if (buf[j] == '\n') {
        buf[j] = '\0';
        break;
      }
    }
    Serial.write(buf);
    Serial.write("\n");
    Serial.println("Trying to connect...");
    WiFi.begin(WiFi.SSID(num - 1).c_str(), buf);
    if (WiFi.waitForConnectResult() == WL_CONNECTED) {
      Serial.println("Done. Do you want to save this?(0/1)");
      while (Serial.available()) Serial.read(); //While data is available, read data (Clean buffer)
      while (!Serial.available()) {
        delay(100);
      }
      if (Serial.parseInt() == 1) {
        Serial.println("Saving...");
        char ssidbuf[30];
        strcpy(ssidbuf, WiFi.SSID(num - 1).c_str());
        ChangeWifiSetting(ssidbuf, buf);
      }
    } else {
      Serial.println("Oh no...");
    }
  }
  IPAddress ip = WiFi.localIP();
  String ipStr = String(ip[0]) + '.' + String(ip[1]) + '.' + String(ip[2]) + '.' + String(ip[3]);
  print_c("Wifi has initialized. IP is: %s\n", ipStr.c_str());
}
/*****Initialization for Web Server*****/
void ServerInit() {
  if (MDNS.begin(ESPSERVER)) {
    print_c("MDNS responder started\n");
  }
  server.on("/", []() {
    HTTPClient http;
    http.begin(CONURL);
    int httpCode = http.GET();
    server.send(httpCode, "text/html", http.getString());
    http.end();
  });
  server.on("/console", []() {
    digitalWrite(LED, HIGH);
    server.send(200, "text/plain", console);
    digitalWrite(LED, LOW);
  });
  server.on("/set", []() {
    if (server.hasArg("c")) {
      motion = server.arg("c");
      print_c("motion is set (%s)\n", motion.c_str());
      server.send(200, "text/plain", "done");
    } else
      server.send(404, "text/plain", "Please use c option to set motion");
  });
  server.on("/control", []() {
    HTTPClient http;
    http.begin(CTRLURL);
    int httpCode = http.GET();
    server.send(httpCode, "text/html", http.getString());
    http.end();
  });
  server.on("/do", []() {
    if (server.hasArg("c")) {
      processCommand(server.arg("c"));
      server.send(200, "text/plain", "done");
    } else
      server.send(404, "text/plain", "Please use c option to do motion");
  });
  server.onNotFound([]() {
    server.send(404, "text/plain", "Flie not found");
  });
  server.begin();
}

void processCommand(String doing) {
  if (!doing.compareTo("walk")) { //in case of straight
    walk(server.hasArg("arg1") ? server.arg("arg1").toInt() : 6, server.hasArg("arg2") ? server.arg("arg2").toInt() : 200);
    stand();
  } else if (!doing.compareTo("right")) {
    turnright(server.hasArg("arg1") ? server.arg("arg1").toInt() : 6, server.hasArg("arg2") ? server.arg("arg2").toInt() : 200);
    stand();
  } else if (!doing.compareTo("left")) {
    turnleft(server.hasArg("arg1") ? server.arg("arg1").toInt() : 6, server.hasArg("arg2") ? server.arg("arg2").toInt() : 200);
    stand();
  } else if (!doing.compareTo("bow")) {
    bow(server.hasArg("arg1") ? server.arg("arg1").toInt() : 800);
    stand();
  } else if (!doing.compareTo("bye")) {
    bye(server.hasArg("arg1") ? server.arg("arg1").toInt() : 4);
    stand();
  } else if (!doing.compareTo("no")) {
    no(server.hasArg("arg1") ? server.arg("arg1").toInt() : 4);
    stand();
  } else if (!doing.compareTo("dance")) {
    dance(server.hasArg("arg1") ? server.arg("arg1").toInt() : 4);
    stand();
  } else if (!doing.compareTo("stand")) {
    stand();
  } else if (!doing.compareTo("version")) {
    verInfo();
  } else if (!doing.compareTo("kusoran")) {
    kusoran();
    stand();
  } else if (!doing.compareTo("red")) {
    ledRed();
  } else if (!doing.compareTo("green")) {
    ledGreen();
  } else if (!doing.compareTo("blue")) {
    ledBlue();
  } else if (!doing.compareTo("setred")) {
    setLEDr(map(server.hasArg("arg1") ? server.arg("arg1").toInt() : 100, 0, 100, 0, LEDREDMAX));
  } else if (!doing.compareTo("setgreen")) {
    setLEDg(map(server.hasArg("arg1") ? server.arg("arg1").toInt() : 100, 0, 100, 0, LEDGREENMAX));
  } else if (!doing.compareTo("setblue")) {
    setLEDb(map(server.hasArg("arg1") ? server.arg("arg1").toInt() : 100, 0, 100, 0, LEDBLUEMAX));
  } else if (!doing.compareTo("setwifi")) {
    print_c("I can't configure Wifi through Wifi console.\nSorry!");
  } else {
    what(doing.c_str());
  }
}

void ChangeWifiSetting(char* wssid, char* wpass) {
  WiFiConfig buf;
  strcpy(buf.ssid, wssid);
  strcpy(buf.pass, wpass);
  EEPROM.put<WiFiConfig>(0, buf);
  EEPROM.commit();
}

/*****Initialization for OTA Update*****/
void OTAInit() {
  ArduinoOTA.setHostname(ESPHOST);
  ArduinoOTA.onStart([]() {
    print_c("Start\n");
  });
  ArduinoOTA.onEnd([]() {
    print_c("End\n");
    ESP.restart();
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    print_c("Progress: %u%%\n", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    print_c("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) print_c("Auth Failed\n");
    else if (error == OTA_BEGIN_ERROR) print_c("Begin Failed\n");
    else if (error == OTA_CONNECT_ERROR) print_c("Connect Failed\n");
    else if (error == OTA_RECEIVE_ERROR) print_c("Receive Failed\n");
    else if (error == OTA_END_ERROR) print_c("End Failed\n");
  });
  ArduinoOTA.begin();
  print_c("OTA Ready: %s\n", ESPHOST);
}

void OTACheck() {
  ArduinoOTA.handle();
}

void ServerCheck() {
  server.handleClient();
}

void RemoteCheck() {
  HTTPClient http;
  http.begin(COMURL);
  int httpCode = http.GET();
  if (httpCode > 0) {
    // file found at server
    if (httpCode == HTTP_CODE_OK) {
      motion = http.getString();
      print_c("motion is set (%s)\n", motion.c_str());
    }
  } else {
    print_c("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
  }
  http.end();
}

#endif

