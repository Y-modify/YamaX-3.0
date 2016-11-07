/*************************************
* AX-Board Testing Program
* To burn on AX-03 for YamaX 3.0
* made by Y-modify, coord.e
* Copyright © 2016 Y-modify All Rights Reserved.
* QIO,80,160,4M(1M),Disabled,none,nodemcu,115200~
*************************************/

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>
#include <SerialCommand.h>

#define SERVOMIN  150
#define SERVOMAX  600

Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);

Adafruit_PWMServoDriver pwm1 = Adafruit_PWMServoDriver(0x40);
Adafruit_PWMServoDriver pwm2 = Adafruit_PWMServoDriver(0x41);

SerialCommand SCmd;

boolean output = true;
uint8_t lastDeg = 0;
uint8_t port = 0;
uint8_t type = 1; //0=x,1=y,2=z

uint8_t setServoPulse(uint8_t n, uint8_t degress) {
  if (degress > 180)
    return false;
  double pulse = map(degress, 0, 180, SERVOMIN, SERVOMAX);

  if (n < 16) {
    pwm1.setPWM(n, 0, pulse);
  }
  else if (n < 32) {
    pwm2.setPWM(n - 16, 0, pulse);
  }
  else {
    return false;
  }
  return pulse;
}

void changePort()
{
  Serial.print("port ");
  char *arg = SCmd.next();
  if (arg != NULL) {
    port = atoi(arg);
    Serial.println(port);
  }
  else {
    Serial.println("Enter the port.");
  }
  Serial.print("~$ ");
}

void setDeg()
{
  Serial.print("deg ");
  char *arg = SCmd.next();
  if (arg != NULL) {
    int val = atoi(arg);
    Serial.println(val);
    output = false;
    setServoPulse(port, val);
  }
  else {
    Serial.println("Enter the value.");
  }
  Serial.print("~$ ");
}

void setType()
{
  Serial.print("type ");
  char *arg = SCmd.next();
  if (arg != NULL) {
    Serial.println(arg);
    if(strcmp("x",arg) == 0){
      type = 0;
    }else if(strcmp("y",arg) == 0){
      type = 1;
    }else if(strcmp("z",arg) == 0){
      type = 2;      
    }else{
      Serial.println("Please enter x, y, or z.");
    }
  }
  else {
    Serial.println("\nEnter enter x, y, or z.");
  }
  Serial.print("~$ ");
}

void printHelp()
{
  Serial.println("help");
  Serial.println("\n************************");
  Serial.println("Tester for AXBoard");
  Serial.println("Shell-like board testing program");
  Serial.println("Commands:");
  Serial.println("- \"port *\": change output servo's port");
  Serial.println("- \"type [x,y,z]\": set output accel type");
  Serial.println("- \"stop\": stop syncing with accel");
  Serial.println("- \"start\": start syncing with accel");
  Serial.println("- \"deg *\": change servo's degress and stop syncing with accel");
  Serial.println("- \"watch (-i)\": show values");
  Serial.println("- \"help\": show this information again");
  Serial.println("************************\n");
  Serial.print("~$ ");
}

void setup() {
  Serial.begin(9600);
  Serial.print("\n~$ ");
  printHelp();

  delay(200);
    
  if(!accel.begin())
  {
    Serial.println("Error: no ADXL345 detected ... Check your wiring!");
    Serial.println("Exit.");
    while(1){ delay(10); }
  }

  accel.setRange(ADXL345_RANGE_16_G);
  
  pwm1.begin();
  pwm2.begin();
  
  pwm1.setPWMFreq(60);
  pwm2.setPWMFreq(60);

  SCmd.addCommand("port", changePort);
  SCmd.addCommand("watch", [](){
    Serial.print("watch ");
    char *arg = SCmd.next();
    if (arg != NULL) {
      Serial.println(arg);
      if(strcmp("-i", arg) == 0){
        Serial.println("X\tY\tZ");
        while(1){
          Serial.print(accel.getX());Serial.print("\t");
          Serial.print(accel.getY());Serial.print("\t");
          Serial.print(accel.getZ());Serial.print("\n");
          delay(100);
        }
      }else{
        Serial.println("Unrecognized option");
      }
    }else{
      Serial.print("\nX: ");Serial.println(accel.getX());
      Serial.print("Y: ");Serial.println(accel.getY());
      Serial.print("Z: ");Serial.println(accel.getZ());
      Serial.print("Port: ");Serial.println(port);
      Serial.print("Degress: ");Serial.println(lastDeg);
    }
    Serial.print("~$ ");
  });
  SCmd.addCommand("stop", [](){ 
    Serial.println("stop");
    output = false; 
    Serial.println("stopped");
    Serial.print("~$ ");
  });
  SCmd.addCommand("start", [](){ 
    Serial.println("start");
    output = true; 
    Serial.println("started");
    Serial.print("~$ ");
  });
  SCmd.addCommand("type", setType);
  SCmd.addCommand("deg", setDeg);
  SCmd.addCommand("help", printHelp);
  SCmd.setDefaultHandler([](const char *command){ 
    Serial.println(command);
    Serial.print(command); 
    Serial.println(": command not found"); 
    Serial.print("~$ ");
  });
}

void loop() {
  if(output){
    int value;
    switch(type){
      case 0:
      value = accel.getX();
      break;
      case 1:
      value = accel.getY();
      break;
      case 2:
      value = accel.getZ();
      break;
      default:break;
    }
    lastDeg = map(value, -275, 275, 0, 180);
    setServoPulse(port, lastDeg);
  }
  SCmd.readSerial();
  delay(30);
}
