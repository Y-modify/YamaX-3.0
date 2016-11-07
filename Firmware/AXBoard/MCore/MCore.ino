/*************************************
  YamaX Arduino Core v3.0
  To burn on AX-03 for YamaX 3.0
  made by Y-modify, Nyanyan & coord.e
  Copyright © 2016 Y-modify All Rights Reserved.
  QIO,80,160,4M(1M),Disabled,none,nodemcu,115200~
*************************************/

/*****Version Definition*****/
#define YAMAX_VER "3.0"
#define FIRMWARE_VER "3.0"

#if defined(ARDUINO_ESP8266_ESP01)  //AX-03
#define S_WIFI    //Support Wifi         comment out to wifi free
//#define S_REMOTE  //Support Remote       comment out to wifi free*
#define S_SERVER  //Support Server       comment out to wifi free
//#define S_OTA     //Support OTA Update   comment out to wifi free*
#define S_ACCEL     //Support Accelerometer
#define BOARD_VER "03"
#elif defined(ARDUINO_AVR_UNO)  //AX-01
#define S_STABLE
#define BOARD_VER "01"
#else
#error This board is not supported! Please use ESP8266 or Arduino UNO.
#endif

#include <libcolor.h>
colors color(THEME_PRIMARY);

#define LED 13

/*****Web Console*****/
String console;
String motion;
bool encout = true;

/*****System Setup*****/
void setup() {
  Serial.begin(115200);
  delay(1000);

  print_c("HELLO YamaX %s\n", YAMAX_VER);

  verInfo();  //Print Version Information

  print_c("Initializing...\n");

  ControlInit();  //Serial Command Control Initialize

  ServoInit();  //Servo Driver Setup

  setLEDColor(color.RED());
  stand();

#if defined(S_WIFI)
  NetInit();  //Connect to Wifi
#endif
#if defined(S_SERVER)
  ServerInit(); //Initialize Server
#endif
#if defined(S_OTA)
  OTAInit();  //Initialize OTA Updater
#endif

  //Start
  setLEDColor(color.GREEN());

  print_c("Initialization Complete.\n");

  /*   for(int i = 0; i <5; i++)
     {
       stand();
       delay(5000);
      bow();
       delay(900);
       stand();
       delay(2000);
       walk(10,300);
       stand();
       delay(1000);
      bye(10);
       stand();
       delay(1000);
       no(5);
     }*/
  //  delay(4000);
  //  walk(10,300);
  //  stand();
  // kusoran();
}

/*****Waiting Loop*****/
void loop() {
  CommandCheck();
#if defined(S_OTA)
  OTACheck();
#endif
#if defined(S_SERVER)
  ServerCheck();
#endif
#if defined(S_REMOTE)
  RemoteCheck();
#endif
#if defined(S_REMOTE) || defined(S_SERVER)
  if (!motion.compareTo("stand")) {
    stand();
    encout = true;
  } else {
    encout = false;
    if (!motion.compareTo("straight")) { //in case of straight
      walk(1, 170);
    } else if (!motion.compareTo("right")) {
      turnright(1, 170);
    } else if (!motion.compareTo("left")) {
      turnleft(1, 170);
    } else if (!motion.compareTo("bow")) {
      bow(0);
    } else if (!motion.compareTo("bye")) {
      bye(1);
    } else if (!motion.compareTo("no")) {
      no(1);
    }
  }
#endif
  //doAccelProcess();
  delay(1);
}

/*****Print Version Information*****/
void verInfo() {
  print_c("\n*************************************\n");
  print_c("YamaX Arduino Core (MCore) v%s\n", FIRMWARE_VER);
  print_c("To burn on AX-%s for YamaX %s\n", BOARD_VER, YAMAX_VER);
  print_c("Made by Y-modify, Nyanyan & coord.e\n");
  print_c("Copyright (c) 2016 Y-modify All Rights Reserved.\n");
  print_c("*************************************\n\n");
}

/*****That's all. Enjoy!*****/
