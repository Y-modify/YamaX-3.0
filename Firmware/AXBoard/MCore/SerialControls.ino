/*************************************
  Controls - YamaX Arduino Core v3.0
  コマンド処理ブロック
  made by coord.e, Y-modify
  Copyright © 2016 Y-modify All Rights Reserved.
*************************************/

#include <SerialCommand.h>

SerialCommand SCmd;

void ControlInit() {
  SCmd.addCommand("walk", walkStep);
  SCmd.addCommand("right", tRightStep);
  SCmd.addCommand("left", tLeftStep);
  SCmd.addCommand("bow", bowS);
  SCmd.addCommand("dance", danceS);
  SCmd.addCommand("stand", stand);
  SCmd.addCommand("bye", byeS);
  SCmd.addCommand("no", noS);
  SCmd.addCommand("kusoran", kusoran);
  SCmd.addCommand("red", ledRed);
  SCmd.addCommand("green", ledGreen);
  SCmd.addCommand("blue", ledBlue);
  SCmd.addCommand("yellow", ledYellow);
  SCmd.addCommand("white", ledWhite);
  SCmd.addCommand("setred", ledRedAdj);
  SCmd.addCommand("setgreen", ledGreenAdj);
  SCmd.addCommand("setblue", ledBlueAdj);
  SCmd.addCommand("version", verInfo);
  SCmd.addCommand("setwifi", setWifi);
  SCmd.setDefaultHandler(what);
}

void CommandCheck() {
  SCmd.readSerial();
}

/*****Functions for Response*****/
void walkStep() {
  char *arg;

  arg = SCmd.next();
  if (arg != NULL)
  {
    int steps = atoi(arg);    // Converts a char string to an integer
    arg = SCmd.next();
    if (arg != NULL)
    {
      int del = atol(arg);
      walk(steps, del);
    }
    else {
      what();
    }
  }
  else {
    what();
  }
  stand();
  clearBuf();
}

void bowS() {
  char *arg;

  arg = SCmd.next();
  if (arg != NULL)
  {
    int val = atoi(arg);
    bow(val);
  }
  else {
    what();
  }
  stand();
  clearBuf();
}

void noS() {
  char *arg;

  arg = SCmd.next();
  if (arg != NULL)
  {
    int val = atoi(arg);
    no(val);
  }
  else {
    what();
  }
  stand();
  clearBuf();
}

void danceS() {
  char *arg;

  arg = SCmd.next();
  if (arg != NULL)
  {
    int val = atoi(arg);
    dance(val);
  }
  else {
    what();
  }
  stand();
  clearBuf();
}

void byeS() {
  char *arg;

  arg = SCmd.next();
  if (arg != NULL)
  {
    int val = atoi(arg);
    bye(val);
  }
  else {
    what();
  }
  stand();
  clearBuf();
}

void tRightStep() {
  char *arg;

  arg = SCmd.next();
  if (arg != NULL)
  {
    int steps = atoi(arg);    // Converts a char string to an integer
    arg = SCmd.next();
    if (arg != NULL)
    {
      int del = atol(arg);
      turnright(steps, del);
    }
    else {
      what();
    }
  }
  else {
    what();
  }
  stand();
  clearBuf();
}

void tLeftStep() {
  char *arg;

  arg = SCmd.next();
  if (arg != NULL)
  {
    int steps = atoi(arg);    // Converts a char string to an integer
    arg = SCmd.next();
    if (arg != NULL)
    {
      int del = atol(arg);
      turnleft(steps, del);
    }
    else {
      what();
    }
  }
  else {
    what();
  }
  stand();
  clearBuf();
}

void ledRedAdj() {
  char *arg;

  arg = SCmd.next();
  if (arg != NULL)
  {
    int val = atoi(arg);    // Converts a char string to an integer
    print_c("Set red LED to %d\n", val);
    setLEDr(map(val, 0, 100, 0, LEDREDMAX));
  }
  else {
    what();
  }
  clearBuf();
}

void ledGreenAdj() {
  char *arg;

  arg = SCmd.next();
  if (arg != NULL)
  {
    int val = atoi(arg);    // Converts a char string to an integer
    print_c("Set green LED to %d\n", val);
    setLEDg(map(val, 0, 100, 0, LEDGREENMAX));
  }
  else {
    what();
  }
  clearBuf();
}

void ledBlueAdj() {
  char *arg;

  arg = SCmd.next();
  if (arg != NULL)
  {
    int val = atoi(arg);    // Converts a char string to an integer
    print_c("Set blue LED to %d\n", val);
    setLEDb(map(val, 0, 100, 0, LEDBLUEMAX));
  }
  else {
    what();
  }
  clearBuf();
}

void ledRed() {
  setLEDColor(color.RED());
}

void ledBlue() {
  setLEDColor(color.BLUE());
}

void ledGreen() {
  setLEDColor(color.GREEN());
}

void ledYellow() {
  setLEDColor(color.YELLOW());
}

void ledWhite() {
  setLEDColor(color.WHITE());
}

void setWifi() {
#if defined(S_WIFI)
  char *arg;

  arg = SCmd.next();
  if (arg != NULL)
  {
    char wssid[32];
    strcpy(wssid, arg);
    arg = SCmd.next();
    if (arg != NULL)
    {
      print_c("Change Wifi Settings\nSSID: %s\nPASS: %s\n", wssid, arg);
      ChangeWifiSetting(wssid, arg);
    }
    else {
      what();
    }
  }
  else {
    what();
  }
  stand();
#else
  print_c("This Feature is not Supported\n");
#endif
  clearBuf();
}

void what() {
  print_c("I can't understand.\n");
  no(2);
  stand();
}

void what(const char *command) {
  print_c("Command \"%s\" is not defined\n", command);
  no(2);
  stand();
}

void clearBuf() {
  while (Serial.available())
    Serial.read();
}

