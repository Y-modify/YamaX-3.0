/*************************************
  Actions - YamaX Arduino Core v3.0
  モーター制御ブロック
  made by Nyanyan, Y-modify
  Copyright © 2016 Y-modify All Rights Reserved.

  standの値をdefineして、
  それに+とか-して制御するようにしています。
*************************************/

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#if defined(S_ACCEL)  //Only Accelerometer Support
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>
#endif

/*****Pulse Adjust*****/
#define SERVOMIN  150 //on 0°,0~4095
#define SERVOMAX  600 //on 180°,0~4095
#define LEDREDMAX 4095
#define LEDGREENMAX 2400
#define LEDBLUEMAX 2300
#if defined(S_ACCEL)
#define ACCELRANGE ADXL345_RANGE_16_G
#define ACCELID 12345
#endif

/*****Object Making*****/
Adafruit_PWMServoDriver pwm1 = Adafruit_PWMServoDriver(0x40);//1
Adafruit_PWMServoDriver pwm2 = Adafruit_PWMServoDriver(0x41);//2
#if defined(S_ACCEL)
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(ACCELID);
#endif

/*****Servo Ports Definition*****/
/**Nyanyan's**/
/*
  #define servoA 15

  #define servoB 14
  #define servoC 13
  #define servoD 12

  #define servoE 16
  #define servoF 17
  #define servoG 18

  #define servoH 19 //3
  #define servoI 20 //4

  #define servoK 23 //7
  #define servoL 24 //8
  #define servoM 26 //10
  #define servoN 27 //11
  #define servoO 28 //12

  #define servoQ 7
  #define servoR 6
  #define servoS 5
  #define servoT 3
  #define servoU 1

  #define LEDr 11
  #define LEDg 10
  #define LEDb 9*/
/*************/




/**cood.e's**/

#define servoA 0

#define servoB 26
#define servoC 4
#define servoD 5

#define servoE 25 //9
#define servoF 24 //8
#define servoG 23 //7

#define servoH 22 //6
#define servoI 21 //5

#define servoK 19 //3
#define servoL 20 //4
#define servoM 18 //2
#define servoN 17 //1
#define servoO 16 //0

#define servoQ 6
#define servoR 7
#define servoS 8
#define servoT 9
#define servoU 10

#define LEDr 3
#define LEDg 2
#define LEDb 1
/***********/

/**standDefinition**/
#define stA 90   //+90    -90

#define stB 50   //+130   -50
#define stC 90   //+90    -90
#define stD 80   //+100   -80

#define stE 100  //+80    -100
#define stF 60   //+120   -60
#define stG 70   //+110   -70

#define stH 65   //+115   -65
#define stI 80   //+100   -80

#define stK 45   //+135   -45
#define stL 110  //+70    -110
#define stM 110  //+70  -110
#define stN 65   //+110   -70*
#define stO 65   //+115   -65

#define stQ 100  //+80    -100
#define stR 100  //+80    -100
#define stS 90   //+90    -90
#define stT 65   //+115   -65
#define stU 90   //+90    -90

/*******************/

void doAccelProcess(){
  /*int sumX,sumY,sumZ;
  for(int i=0; i<100; i++){
    sumX += accel.getX();
    sumY += accel.getY();
    sumZ += accel.getZ();
  }
  sumX /= 100;
  sumY /= 100;
  sumZ /= 100;*/
  print_c("X:%d\tY:%d\tZ:%d\n",accel.getX(),accel.getY(),accel.getZ());
}

/*****Initialize Servo Driver*****/
void ServoInit() {
#if defined(S_ACCEL)
  accel.begin();
  accel.setRange(ACCELRANGE);
#endif
  pwm1.begin();
  pwm2.begin();
  pwm1.setPWMFreq(60);  // Analog servos run at ~60 Hz updates
  pwm2.setPWMFreq(60);  // Analog servos run at ~60 Hz updates
}

/*****Base Functions*****/
void stand()
{
  setServoPulse(servoA, stA); //首

  setServoPulse(servoB, stB);
  setServoPulse(servoC, stC);
  setServoPulse(servoD, stD); //左腕

  setServoPulse(servoE, stE);
  setServoPulse(servoF, stF);
  setServoPulse(servoG, stG); //右腕

  setServoPulse(servoH, stH);
  setServoPulse(servoI, stI); //腰

  setServoPulse(servoK, stK);
  setServoPulse(servoL, stL); //170
  setServoPulse(servoM, stM);//170
  setServoPulse(servoN, stN);
  setServoPulse(servoO, stO); //右足

  setServoPulse(servoQ, stQ);
  setServoPulse(servoR, stR); //30
  setServoPulse(servoS, stS);//30
  setServoPulse(servoT, stT);
  setServoPulse(servoU, stU); //左足

}

void bow(int deltime)
{
  print_c("Bowing %dms\n", deltime);

  setServoPulse(servoA, stA); //首

  setServoPulse(servoB, stB);
  setServoPulse(servoC, stC);
  setServoPulse(servoD, stD); //左腕

  setServoPulse(servoE, stE);
  setServoPulse(servoF, stF);
  setServoPulse(servoG, stG); //右腕

  setServoPulse(servoH, stH);
  setServoPulse(servoI, stI + 50); //腰

  setServoPulse(servoK, stK);
  setServoPulse(servoL, stL - 20); //170
  setServoPulse(servoM, stM);//170
  setServoPulse(servoN, stN);
  setServoPulse(servoO, stO); //右足

  setServoPulse(servoQ, stQ);
  setServoPulse(servoR, stR + 20); //30
  setServoPulse(servoS, stS);//30
  setServoPulse(servoT, stT);
  setServoPulse(servoU, stU); //左足

  delay(deltime);
}

void foot(int times, int delaytime)
{
  int i = 0;
  for (i = 0; i < times; i += 2)
  {
    foot1();
    delay(delaytime);
    foot2();
    delay(delaytime);
  }
}

void foot1()//左足上げ
{
  setServoPulse(servoA, stA); //首

  setServoPulse(servoB, stB + 20);
  setServoPulse(servoC, stC + 20);
  setServoPulse(servoD, stD); //左腕

  setServoPulse(servoE, stE + 20);
  setServoPulse(servoF, stF - 20);
  setServoPulse(servoG, stG); //右腕

  setServoPulse(servoH, stH - 40);
  setServoPulse(servoI, stI - 12); //腰

  setServoPulse(servoK, stK/* - 20*/);
  setServoPulse(servoL, stL - 10); //170
  setServoPulse(servoM, stM); //170
  setServoPulse(servoN, stN);
  setServoPulse(servoO, stO - 10); //右足

  setServoPulse(servoQ, stQ - 30);
  setServoPulse(servoR, stR); //10?
  setServoPulse(servoS, stS); //20?
  setServoPulse(servoT, stT); //10?
  setServoPulse(servoU, stU - 30); //左足

}

void foot2()//右足上げ
{
  setServoPulse(servoA, stA); //首

  setServoPulse(servoB, stB - 20);
  setServoPulse(servoC, stC + 20);
  setServoPulse(servoD, stD); //左腕

  setServoPulse(servoE, stE - 20);
  setServoPulse(servoF, stF - 20);
  setServoPulse(servoG, stG); //右腕

  setServoPulse(servoH, stH + 40);
  setServoPulse(servoI, stI - 12); //腰

  setServoPulse(servoK, stK + 30);
  setServoPulse(servoL, stL); //170
  setServoPulse(servoM, stM); //170
  setServoPulse(servoN, stN);
  setServoPulse(servoO, stO + 30); //右足

  setServoPulse(servoQ, stQ/* + 20*/);
  setServoPulse(servoR, stR + 10); //30
  setServoPulse(servoS, stS); //30
  setServoPulse(servoT, stT);
  setServoPulse(servoU, stU + 10); //左足


}

/*****Walking*****/
void walk(int times, int delaytime)
{
  print_c("Walking %d steps with %dms\n", times, delaytime);

  int i = 0;
  for (i = 0; i < times; i += 2)
  {
    foot1();
    delay(delaytime);
    walk1();
    delay(delaytime);
    /*   setServoPulse(servoU, stU 80); //左足
       setServoPulse(servoO, stO 65); //右足
      //  setServoPulse(servoH, stH 55);*/
    delay(100);

    foot2();
    delay(delaytime);
    walk2();
    delay(delaytime);
    /*   setServoPulse(servoU, stU 80); //左足
       setServoPulse(servoO, stO 65); //右足
      //   setServoPulse(servoH, stH 75);*/
    delay(100);
  }
}

void walk1()//左足を出す
{
  setServoPulse(servoA, stA); //首

  setServoPulse(servoB, stB + 20);
  setServoPulse(servoC, stC + 20);
  setServoPulse(servoD, stD); //左腕

  setServoPulse(servoE, stE + 20);
  setServoPulse(servoF, stF - 20);
  setServoPulse(servoG, stG); //右腕

  setServoPulse(servoH, stH - 20);
  setServoPulse(servoI, stI - 12); //腰

  setServoPulse(servoK, stK/* - 15*/);
  setServoPulse(servoL, stL); //170
  setServoPulse(servoM, stM); //170
  setServoPulse(servoN, stN);
  setServoPulse(servoO, stO - 5); //右足

  setServoPulse(servoQ, stQ - 15);
  setServoPulse(servoR, stR - 60); //30
  setServoPulse(servoS, stS - 40); //30
  setServoPulse(servoT, stT - 0);
  setServoPulse(servoU, stU - 40); //左足


}

void walk2()//右足を出す
{
  setServoPulse(servoA, stA); //首

  setServoPulse(servoB, stB - 20);
  setServoPulse(servoC, stC + 20);
  setServoPulse(servoD, stD); //左腕

  setServoPulse(servoE, stE - 20);
  setServoPulse(servoF, stF - 20);
  setServoPulse(servoG, stG); //右腕

  setServoPulse(servoH, stH + 20);
  setServoPulse(servoI, stI - 12); //腰

  setServoPulse(servoK, stK + 15);
  setServoPulse(servoL, stL + 60); //170
  setServoPulse(servoM, stM + 40); //170
  setServoPulse(servoN, stN + 0);
  setServoPulse(servoO, stO + 40); //右足

  setServoPulse(servoQ, stQ/* + 15*/);
  setServoPulse(servoR, stR); //30
  setServoPulse(servoS, stS); //30
  setServoPulse(servoT, stT);
  setServoPulse(servoU, stU + 5); //左足


}

/*****回ろう*****/
void turnright(int times, int delaytime)
{
  print_c("Turning right %d times with %dms\n", times, delaytime);

  for (int i = 0; i < times; i ++)
  {
    //foot1();
    //setServoPulse(servoI, stI - 20); //腰
    //    setServoPulse(servoO, stO - 20); //右足
    //delay(delaytime);
    turnright1();
    //walk1();
    //setServoPulse(servoI, stI - 20); //腰
    delay(delaytime);
    stand();
    delay(delaytime);
  }
}

void turnleft(int times, int delaytime)
{
  print_c("Turning left %d times with %dms\n", times, delaytime);

  for (int i = 0; i < times; i ++)
  {
    //foot2();
    //setServoPulse(servoI, stI - 15); //腰
    //  setServoPulse(servoU, stU + 20); //左足
    //delay(delaytime);
    turnleft1();
    //walk2();
    //setServoPulse(servoI, stI - 15); //腰
    delay(delaytime);
    stand();
    delay(delaytime);
  }
}

void turnright1()//左足を出す
{
  setServoPulse(servoA, stA); //首

  setServoPulse(servoB, stB + 20);
  setServoPulse(servoC, stC + 20);
  setServoPulse(servoD, stD); //左腕

  setServoPulse(servoE, stE + 20);
  setServoPulse(servoF, stF - 20);
  setServoPulse(servoG, stG); //右腕

  setServoPulse(servoH, stH);
  setServoPulse(servoI, stI - 10); //腰

  setServoPulse(servoK, stK);
  setServoPulse(servoL, stL + 10); //170
  setServoPulse(servoM, stM); //170
  setServoPulse(servoN, stN);
  setServoPulse(servoO, stO - 10); //右足

  setServoPulse(servoQ, stQ);
  setServoPulse(servoR, stR - 60); //30
  setServoPulse(servoS, stS - 40); //30
  setServoPulse(servoT, stT - 10);
  setServoPulse(servoU, stU - 2); //左足


}


void turnright2()
{
  setServoPulse(servoA, stA); //首

  setServoPulse(servoB, stB - 20);
  setServoPulse(servoC, stC + 20);
  setServoPulse(servoD, stD); //左腕

  setServoPulse(servoE, stE - 20);
  setServoPulse(servoF, stF - 20);
  setServoPulse(servoG, stG); //右腕

  setServoPulse(servoH, stH);
  setServoPulse(servoI, stI - 10); //腰

  setServoPulse(servoK, stK);
  setServoPulse(servoL, stL + 20); //170
  setServoPulse(servoM, stM + 10); //170
  setServoPulse(servoN, stN);
  setServoPulse(servoO, stO + 2); //右足

  setServoPulse(servoQ, stQ);
  setServoPulse(servoR, stR - 10); //30
  setServoPulse(servoS, stS); //30
  setServoPulse(servoT, stT);
  setServoPulse(servoU, stU + 10); //左足
}



void turnleft1()//右足を出す
{
  setServoPulse(servoA, stA); //首

  setServoPulse(servoB, stB - 20);
  setServoPulse(servoC, stC + 20);
  setServoPulse(servoD, stD); //左腕

  setServoPulse(servoE, stE - 20);
  setServoPulse(servoF, stF - 20);
  setServoPulse(servoG, stG); //右腕

  setServoPulse(servoH, stH);
  setServoPulse(servoI, stI + 10); //腰

  setServoPulse(servoK, stK);
  setServoPulse(servoL, stL + 60); //170
  setServoPulse(servoM, stM + 40); //170
  setServoPulse(servoN, stN + 10);
  setServoPulse(servoO, stO + 2); //右足

  setServoPulse(servoQ, stQ);
  setServoPulse(servoR, stR - 10); //30
  setServoPulse(servoS, stS); //30
  setServoPulse(servoT, stT);
  setServoPulse(servoU, stU + 5); //左足


}
void turnleft2()
{
  setServoPulse(servoA, stA); //首

  setServoPulse(servoB, stB + 20);
  setServoPulse(servoC, stC + 20);
  setServoPulse(servoD, stD); //左腕

  setServoPulse(servoE, stE + 20);
  setServoPulse(servoF, stF - 20);
  setServoPulse(servoG, stG); //右腕

  setServoPulse(servoH, stH);
  setServoPulse(servoI, stI + 10); //腰

  setServoPulse(servoK, stK);
  setServoPulse(servoL, stL + 10); //170
  setServoPulse(servoM, stM); //170
  setServoPulse(servoN, stN);
  setServoPulse(servoO, stO - 5); //右足

  setServoPulse(servoQ, stQ);
  setServoPulse(servoR, stR - 20); //30
  setServoPulse(servoS, stS - 10); //30
  setServoPulse(servoT, stT);
  setServoPulse(servoU, stU - 2); //左足
}


void achilles1()

{
  setServoPulse(servoA, stA); //首

  setServoPulse(servoB, stB + 20);
  setServoPulse(servoC, stC + 20);
  setServoPulse(servoD, stD); //左腕

  setServoPulse(servoE, stE + 20);
  setServoPulse(servoF, stF - 20);
  setServoPulse(servoG, stG); //右腕

  setServoPulse(servoH, stH - 30);
  setServoPulse(servoI, stI + 40); //腰

  setServoPulse(servoK, stK);
  setServoPulse(servoL, stL - 60); //170
  setServoPulse(servoM, stM - 40); //170
  setServoPulse(servoN, stN);
  setServoPulse(servoO, stO); //右足

  setServoPulse(servoQ, stQ);
  setServoPulse(servoR, stR - 60); //30
  setServoPulse(servoS, stS - 40); //30
  setServoPulse(servoT, stT - 20);
  setServoPulse(servoU, stU); //左足
}

void achilles2()
{
  setServoPulse(servoA, stA); //首

  setServoPulse(servoB, stB - 20);
  setServoPulse(servoC, stC + 20);
  setServoPulse(servoD, stD); //左腕

  setServoPulse(servoE, stE - 20);
  setServoPulse(servoF, stF - 20);
  setServoPulse(servoG, stG); //右腕

  setServoPulse(servoH, stH + 30);
  setServoPulse(servoI, stI + 40); //腰

  setServoPulse(servoK, stK);
  setServoPulse(servoL, stL + 60); //170
  setServoPulse(servoM, stM + 40); //170
  setServoPulse(servoN, stN + 20);
  setServoPulse(servoO, stO); //右足

  setServoPulse(servoQ, stQ);
  setServoPulse(servoR, stR + 60); //30
  setServoPulse(servoS, stS + 40); //30
  setServoPulse(servoT, stT);
  setServoPulse(servoU, stU); //左足

}



/*****首*****/
void no(int times)
{
  print_c("Denying %d times\n", times);

  for (int i = 0; i < times; i ++)
  {
    stand();
    setServoPulse(servoA, stA - 60); //首
    delay(200);
    stand();
    setServoPulse(servoA, stA + 60); //首
    delay(200);
  }
}

/*****ダンス?*****/
void dance(int times)
{
  print_c("Dancing %d times\n", times);
  for (int i = 0; i < times; i ++)
  {
    foot1();
    //   setServoPulse(servoI, stI 90); //腰
    delay(30);
    walk1();
    //    setServoPulse(servoI, stI 90); //腰
    delay(30);
    foot2();
    //    setServoPulse(servoI, stI 90); //腰
    delay(30);
    walk2();
    //    setServoPulse(servoI, stI 90); //腰
    delay(30);
  }
}
/****************/

/***クソーラン節***/

#define KUSORAN_TEMPO 400
//TEMPO, CJ said it is 407.6

void kusoran()
{
  stand();
  // delay(4000);
  kamae();
  delay(10000);
  setLEDColor(color.BLUE());
  delay(1000);
  waver();
  wavel();
  amimaki1(5);
  amimaki2();
  amimaki3();
  amimaki1(5);
  amimaki2();
  amimaki3();
  amimaki1(5);
  amimaki2();
  amimaki3();
  amimaki1(2);
  amimaki2();
  Tparty1(KUSORAN_TEMPO * 2);
  Tparty2(KUSORAN_TEMPO);
  tie(KUSORAN_TEMPO);
  dokkoisyor();
  dokkoisyol();
  soransoran();
  dokkoisyor();
  dokkoisyol();
  soransoran();
  tekogi(5);
  haihai();
  koshimage(KUSORAN_TEMPO);
  amimaki1(6);
  volt1(KUSORAN_TEMPO);
  koshimage(KUSORAN_TEMPO);
  amimaki1(6);
  volt2(KUSORAN_TEMPO);
  human(KUSORAN_TEMPO);
  tie(KUSORAN_TEMPO);
  yajiron(16);
  dokkoisyo();
  dokkoisyor();
  dokkoisyol();
  soransoran();
  dokkoisyor();
  dokkoisyol();
  soransoran();
  gattsu(4);
  biem(4);
  tekogi(4);
  dosuru(KUSORAN_TEMPO * 2);
  volt1(4000);
}

void kamae()
{
  setServoPulse(servoA, stA); //首

  setServoPulse(servoB, stB + 20);
  setServoPulse(servoC, stC);
  setServoPulse(servoD, stD); //左腕

  setServoPulse(servoE, stE + 60);
  setServoPulse(servoF, stF);
  setServoPulse(servoG, stG + 70); //右腕

  setServoPulse(servoH, stH);
  setServoPulse(servoI, stI + 60); //腰

  setServoPulse(servoK, stK + 50);
  setServoPulse(servoL, stL + 70); //170
  setServoPulse(servoM, stM + 70); //170
  setServoPulse(servoN, stN - 20);
  setServoPulse(servoO, stO + 50); //右足

  setServoPulse(servoQ, stQ - 50);
  setServoPulse(servoR, stR - 70); //30
  setServoPulse(servoS, stS - 70); //30
  setServoPulse(servoT, stT + 20);
  setServoPulse(servoU, stU - 50); //左足
}

void waver()
{
  setServoPulse(servoB, stB);
  setServoPulse(servoC, stC);
  setServoPulse(servoD, stD); //左腕

  setServoPulse(servoH, stH);
  setServoPulse(servoI, stI); //腰

  setServoPulse(servoK, stK + 50);
  setServoPulse(servoL, stL + 70); //170
  setServoPulse(servoM, stM + 50); //170
  setServoPulse(servoN, stN - 30);
  setServoPulse(servoO, stO + 50); //右足

  setServoPulse(servoQ, stQ - 50);
  setServoPulse(servoR, stR - 70); //30
  setServoPulse(servoS, stS - 50); //30
  setServoPulse(servoT, stT + 30);
  setServoPulse(servoU, stU - 50); //左足

  for (int i = 0; i < 8; i++)
  {
    int j = 10 * i;
    setServoPulse(servoA, stA + 40 - j);//-40~+40

    setServoPulse(servoE, stE + 50);
    setServoPulse(servoF, stF + 40 - j); //-40~+40
    setServoPulse(servoG, stG);


    delay(KUSORAN_TEMPO / 2);
    setServoPulse(servoG, stG + 30); //右腕
    delay(KUSORAN_TEMPO / 2);
  }
}

void wavel()
{
  setServoPulse(servoE, stE);
  setServoPulse(servoF, stF);
  setServoPulse(servoG, stG); //右腕

  setServoPulse(servoH, stH);
  setServoPulse(servoI, stI); //腰

  setServoPulse(servoK, stK + 50);
  setServoPulse(servoL, stL + 70); //170
  setServoPulse(servoM, stM + 50); //170
  setServoPulse(servoN, stN - 30);
  setServoPulse(servoO, stO + 50); //右足

  setServoPulse(servoQ, stQ - 50);
  setServoPulse(servoR, stR - 70); //30
  setServoPulse(servoS, stS - 50); //30
  setServoPulse(servoT, stT + 30);
  setServoPulse(servoU, stU - 50); //左足

  for (int i = 0; i < 8; i++)
  {
    int j = 10 * i;
    setServoPulse(servoA, stA - 40 + j);//-40~+40

    setServoPulse(servoB, stB - 50);
    setServoPulse(servoC, stC - 40 + j);
    setServoPulse(servoD, stD);

    delay(KUSORAN_TEMPO / 2);
    setServoPulse(servoD, stD - 30); //左腕
    delay(KUSORAN_TEMPO / 2);
  }
}

void amimaki1(int times)
{
  setServoPulse(servoA, stA); //首

  setServoPulse(servoB, stB - 50);
  setServoPulse(servoC, stC - 20);
  setServoPulse(servoD, stD - 30); //左腕

  setServoPulse(servoE, stE + 40);
  setServoPulse(servoF, stF + 20);
  setServoPulse(servoG, stG + 30); //右腕

  setServoPulse(servoH, stH);
  setServoPulse(servoI, stI + 50); //腰

  setServoPulse(servoK, stK + 50);
  setServoPulse(servoL, stL + 70); //170
  setServoPulse(servoM, stM + 50); //170
  setServoPulse(servoN, stN - 20);
  setServoPulse(servoO, stO + 50); //右足

  setServoPulse(servoQ, stQ - 50);
  setServoPulse(servoR, stR - 70); //30
  setServoPulse(servoS, stS - 50); //30
  setServoPulse(servoT, stT + 20);
  setServoPulse(servoU, stU - 50); //左足

  for (int i = 0; i < times; i++)
  {
    setServoPulse(servoB, stB - 40);
    setServoPulse(servoC, stC - 60);
    setServoPulse(servoD, stD - 20); //左腕

    setServoPulse(servoE, stE + 50);
    setServoPulse(servoF, stF + 40);
    setServoPulse(servoG, stG + 20); //右腕

    delay(KUSORAN_TEMPO / 2);

    setServoPulse(servoB, stB - 50);
    setServoPulse(servoC, stC - 40);
    setServoPulse(servoD, stD - 20); //左腕

    setServoPulse(servoE, stE + 40);
    setServoPulse(servoF, stF + 60);
    setServoPulse(servoG, stG + 20); //右腕

    delay(KUSORAN_TEMPO / 2);
  }

}

void amimaki2()
{

  setServoPulse(servoB, stB);
  setServoPulse(servoC, stC);
  setServoPulse(servoD, stD); //左腕

  setServoPulse(servoE, stE + 50);
  setServoPulse(servoF, stF);
  setServoPulse(servoG, stG + 70); //右腕

  setServoPulse(servoH, stH);
  setServoPulse(servoI, stI); //腰

  setServoPulse(servoK, stK + 50);
  setServoPulse(servoL, stL + 70); //170
  setServoPulse(servoM, stM + 50); //170
  setServoPulse(servoN, stN - 20);
  setServoPulse(servoO, stO + 50); //右足

  setServoPulse(servoQ, stQ - 50);
  setServoPulse(servoR, stR - 70); //30
  setServoPulse(servoS, stS - 50); //30
  setServoPulse(servoT, stT + 20);
  setServoPulse(servoU, stU - 50); //左足

  delay(KUSORAN_TEMPO);

  setServoPulse(servoB, stB - 50);
  setServoPulse(servoC, stC);
  setServoPulse(servoD, stD - 70); //左腕

  setServoPulse(servoE, stE);
  setServoPulse(servoF, stF);
  setServoPulse(servoG, stG); //右腕

  delay(KUSORAN_TEMPO);
}

void amimaki3()
{
  setServoPulse(servoB, stB);
  setServoPulse(servoC, stC);
  setServoPulse(servoD, stD); //左腕

  setServoPulse(servoE, stE + 50);
  setServoPulse(servoF, stF);
  setServoPulse(servoG, stG + 70); //右腕

  setServoPulse(servoH, stH);
  setServoPulse(servoI, stI); //腰

  setServoPulse(servoK, stK);
  setServoPulse(servoL, stL); //170
  setServoPulse(servoM, stM); //170
  setServoPulse(servoN, stN);
  setServoPulse(servoO, stO); //右足

  setServoPulse(servoQ, stQ);
  setServoPulse(servoR, stR); //30
  setServoPulse(servoS, stS); //30
  setServoPulse(servoT, stT);
  setServoPulse(servoU, stU); //左足

  delay(KUSORAN_TEMPO);

}

void Tparty1(int Time)
{
  setServoPulse(servoA, stA); //首

  setServoPulse(servoB, stB);
  setServoPulse(servoC, stC + 60);
  setServoPulse(servoD, stD); //左腕

  setServoPulse(servoE, stE);
  setServoPulse(servoF, stF - 60);
  setServoPulse(servoG, stG); //右腕

  setServoPulse(servoH, stH);
  setServoPulse(servoI, stI); //腰

  setServoPulse(servoK, stK);
  setServoPulse(servoL, stL); //170
  setServoPulse(servoM, stM);//170
  setServoPulse(servoN, stN);
  setServoPulse(servoO, stO); //右足

  setServoPulse(servoQ, stQ);
  setServoPulse(servoR, stR); //30
  setServoPulse(servoS, stS);//30
  setServoPulse(servoT, stT);
  setServoPulse(servoU, stU); //左足
  delay(Time);
}

void Tparty2(int Time)
{
  setServoPulse(servoA, stA); //首

  setServoPulse(servoB, stB);
  setServoPulse(servoC, stC);
  setServoPulse(servoD, stD); //左腕

  setServoPulse(servoE, stE);
  setServoPulse(servoF, stF);
  setServoPulse(servoG, stG); //右腕

  setServoPulse(servoH, stH);
  setServoPulse(servoI, stI); //腰

  setServoPulse(servoK, stK);
  setServoPulse(servoL, stL); //170
  setServoPulse(servoM, stM);//170
  setServoPulse(servoN, stN);
  setServoPulse(servoO, stO); //右足

  setServoPulse(servoQ, stQ);
  setServoPulse(servoR, stR); //30
  setServoPulse(servoS, stS);//30
  setServoPulse(servoT, stT);
  setServoPulse(servoU, stU); //左足
  delay(Time);
}

void tie(int Time)
{
  setServoPulse(servoA, stA); //首

  setServoPulse(servoB, stB);
  setServoPulse(servoC, stC + 60);
  setServoPulse(servoD, stD); //左腕

  setServoPulse(servoE, stE);
  setServoPulse(servoF, stF - 60);
  setServoPulse(servoG, stG); //右腕

  setServoPulse(servoH, stH);
  setServoPulse(servoI, stI); //腰

  setServoPulse(servoK, stK + 50);
  setServoPulse(servoL, stL); //170
  setServoPulse(servoM, stM); //170
  setServoPulse(servoN, stN);
  setServoPulse(servoO, stO + 50); //右足

  setServoPulse(servoQ, stQ - 50);
  setServoPulse(servoR, stR); //30
  setServoPulse(servoS, stS); //30
  setServoPulse(servoT, stT);
  setServoPulse(servoU, stU - 50); //左足

  delay(Time);
}

void dokkoisyor()
{
  setServoPulse(servoA, stA + 50); //首

  setServoPulse(servoB, stB);
  setServoPulse(servoC, stC);
  setServoPulse(servoD, stD); //左腕

  setServoPulse(servoE, stE + 30);
  setServoPulse(servoF, stF + 90);
  setServoPulse(servoG, stG); //右腕

  setServoPulse(servoH, stH);
  setServoPulse(servoI, stI); //腰

  setServoPulse(servoK, stK + 50);
  setServoPulse(servoL, stL); //170
  setServoPulse(servoM, stM); //170
  setServoPulse(servoN, stN - 20);
  setServoPulse(servoO, stO + 50); //右足

  setServoPulse(servoQ, stQ - 50);
  setServoPulse(servoR, stR); //30
  setServoPulse(servoS, stS); //30
  setServoPulse(servoT, stT + 20);
  setServoPulse(servoU, stU - 50); //左足

  delay(KUSORAN_TEMPO);

  setServoPulse(servoB, stB);
  setServoPulse(servoC, stC + 60);
  setServoPulse(servoD, stD); //左腕

  delay(KUSORAN_TEMPO);

  setServoPulse(servoK, stK + 50);
  setServoPulse(servoL, stL + 70); //170
  setServoPulse(servoM, stM + 70); //170
  setServoPulse(servoN, stN - 30);
  setServoPulse(servoO, stO + 50); //右足

  setServoPulse(servoQ, stQ - 50);
  setServoPulse(servoR, stR); //30
  setServoPulse(servoS, stS); //30
  setServoPulse(servoT, stT + 30);
  setServoPulse(servoU, stU - 50); //左足

  delay(KUSORAN_TEMPO);

  setServoPulse(servoK, stK + 50);
  setServoPulse(servoL, stL); //170
  setServoPulse(servoM, stM); //170
  setServoPulse(servoN, stN - 20);
  setServoPulse(servoO, stO + 50); //右足

  setServoPulse(servoQ, stQ - 50);
  setServoPulse(servoR, stR); //30
  setServoPulse(servoS, stS); //30
  setServoPulse(servoT, stT + 20);
  setServoPulse(servoU, stU - 50); //左足

  delay(KUSORAN_TEMPO);

}

void dokkoisyol()
{
  setServoPulse(servoA, stA - 50); //首

  setServoPulse(servoB, stB - 30);
  setServoPulse(servoC, stC - 90);
  setServoPulse(servoD, stD); //左腕

  setServoPulse(servoE, stE);
  setServoPulse(servoF, stF);
  setServoPulse(servoG, stG); //右腕

  setServoPulse(servoH, stH);
  setServoPulse(servoI, stI); //腰

  setServoPulse(servoK, stK + 50);
  setServoPulse(servoL, stL); //170
  setServoPulse(servoM, stM); //170
  setServoPulse(servoN, stN - 20);
  setServoPulse(servoO, stO + 50); //右足

  setServoPulse(servoQ, stQ - 50);
  setServoPulse(servoR, stR); //30
  setServoPulse(servoS, stS); //30
  setServoPulse(servoT, stT + 20);
  setServoPulse(servoU, stU - 50); //左足

  delay(KUSORAN_TEMPO);

  setServoPulse(servoE, stE);
  setServoPulse(servoF, stF - 60);
  setServoPulse(servoG, stG); //右腕

  delay(KUSORAN_TEMPO);

  setServoPulse(servoK, stK + 50);
  setServoPulse(servoL, stL); //170
  setServoPulse(servoM, stM); //170
  setServoPulse(servoN, stN - 30);
  setServoPulse(servoO, stO + 50); //右足

  setServoPulse(servoQ, stQ - 50);
  setServoPulse(servoR, stR - 70); //30
  setServoPulse(servoS, stS - 70); //30
  setServoPulse(servoT, stT + 30);
  setServoPulse(servoU, stU - 50); //左足

  delay(KUSORAN_TEMPO);

  setServoPulse(servoK, stK + 50);
  setServoPulse(servoL, stL); //170
  setServoPulse(servoM, stM); //170
  setServoPulse(servoN, stN - 20);
  setServoPulse(servoO, stO + 50); //右足

  setServoPulse(servoQ, stQ - 50);
  setServoPulse(servoR, stR); //30
  setServoPulse(servoS, stS); //30
  setServoPulse(servoT, stT + 20);
  setServoPulse(servoU, stU - 50); //左足

  delay(KUSORAN_TEMPO);
}

void soransoran()
{

  for (int i = 0; i < 2; i++)
  {
    setServoPulse(servoA, stA); //首

    setServoPulse(servoB, stB - 40);
    setServoPulse(servoC, stC - 20);
    setServoPulse(servoD, stD - 20); //左腕

    setServoPulse(servoE, stE + 40);
    setServoPulse(servoF, stF + 20);
    setServoPulse(servoG, stG + 20); //右腕

    setServoPulse(servoH, stH);
    setServoPulse(servoI, stI + 50); //腰

    setServoPulse(servoK, stK + 50);
    setServoPulse(servoL, stL); //170
    setServoPulse(servoM, stM); //170
    setServoPulse(servoN, stN);
    setServoPulse(servoO, stO + 50); //右足

    setServoPulse(servoQ, stQ - 50);
    setServoPulse(servoR, stR); //30
    setServoPulse(servoS, stS); //30
    setServoPulse(servoT, stT);
    setServoPulse(servoU, stU - 50); //左足

    delay(KUSORAN_TEMPO * 2);

    setServoPulse(servoB, stB - 50);
    setServoPulse(servoC, stC + 60);
    setServoPulse(servoD, stD - 80); //左腕

    setServoPulse(servoE, stE + 50);
    setServoPulse(servoF, stF - 60);
    setServoPulse(servoG, stG + 80); //右腕

    setServoPulse(servoH, stH);
    setServoPulse(servoI, stI); //腰

    setServoPulse(servoK, stK + 50);
    setServoPulse(servoL, stL + 70); //170
    setServoPulse(servoM, stM + 50); //170
    setServoPulse(servoN, stN - 30);
    setServoPulse(servoO, stO + 50); //右足

    setServoPulse(servoQ, stQ - 50);
    setServoPulse(servoR, stR - 70); //30
    setServoPulse(servoS, stS - 50); //30
    setServoPulse(servoT, stT + 30);
    setServoPulse(servoU, stU - 50); //左足

    delay(KUSORAN_TEMPO * 2);
  }
}

void tekogi(int times)
{
  for (int i = 0; i < times; i++)
  {
    setServoPulse(servoA, stA); //首

    setServoPulse(servoB, stB - 50);
    setServoPulse(servoC, stC + 60);
    setServoPulse(servoD, stD - 80); //左腕

    setServoPulse(servoE, stE + 50);
    setServoPulse(servoF, stF - 60);
    setServoPulse(servoG, stG + 80); //右腕

    setServoPulse(servoH, stH);
    setServoPulse(servoI, stI - 20); //腰

    setServoPulse(servoK, stK + 50);
    setServoPulse(servoL, stL - 30); //170
    setServoPulse(servoM, stM - 30); //170
    setServoPulse(servoN, stN - 30);
    setServoPulse(servoO, stO + 50); //右足

    setServoPulse(servoQ, stQ - 50);
    setServoPulse(servoR, stR + 30); //30
    setServoPulse(servoS, stS + 30); //30
    setServoPulse(servoT, stT + 30);
    setServoPulse(servoU, stU - 50); //左足

    delay(KUSORAN_TEMPO * 2);

    setServoPulse(servoA, stA); //首

    setServoPulse(servoB, stB);
    setServoPulse(servoC, stC + 60);
    setServoPulse(servoD, stD - 80); //左腕

    setServoPulse(servoE, stE);
    setServoPulse(servoF, stF - 60);
    setServoPulse(servoG, stG + 80); //右腕

    setServoPulse(servoH, stH);
    setServoPulse(servoI, stI); //腰

    setServoPulse(servoK, stK + 50);
    setServoPulse(servoL, stL + 70); //170
    setServoPulse(servoM, stM + 40); //170
    setServoPulse(servoN, stN - 30);
    setServoPulse(servoO, stO + 50); //右足

    setServoPulse(servoQ, stQ - 50);
    setServoPulse(servoR, stR - 70); //30
    setServoPulse(servoS, stS - 40); //30
    setServoPulse(servoT, stT + 30);
    setServoPulse(servoU, stU - 50); //左足

    delay(KUSORAN_TEMPO * 2);
  }

}

void haihai()
{
  for (int i = 0; i < 2; i++)
  {
    setServoPulse(servoA, stA); //首

    setServoPulse(servoB, stB);
    setServoPulse(servoC, stC);
    setServoPulse(servoD, stD); //左腕

    setServoPulse(servoE, stE + 80);
    setServoPulse(servoF, stF);
    setServoPulse(servoG, stG + 90); //右腕

    setServoPulse(servoH, stH);
    setServoPulse(servoI, stI); //腰

    setServoPulse(servoK, stK + 50);
    setServoPulse(servoL, stL); //170
    setServoPulse(servoM, stM); //170
    setServoPulse(servoN, stN);
    setServoPulse(servoO, stO + 50); //右足

    setServoPulse(servoQ, stQ - 50);
    setServoPulse(servoR, stR); //30
    setServoPulse(servoS, stS); //30
    setServoPulse(servoT, stT);
    setServoPulse(servoU, stU - 50); //左足

    delay(KUSORAN_TEMPO / 2);

    setServoPulse(servoA, stA); //首

    setServoPulse(servoB, stB);
    setServoPulse(servoC, stC);
    setServoPulse(servoD, stD); //左腕

    setServoPulse(servoE, stE + 80);
    setServoPulse(servoF, stF);
    setServoPulse(servoG, stG + 40); //右腕

    delay(KUSORAN_TEMPO / 2);
  }

}

void koshimage(int t)
{
  setServoPulse(servoA, stA); //首

  setServoPulse(servoB, stB - 60);
  setServoPulse(servoC, stC - 40);
  setServoPulse(servoD, stD - 40); //左腕

  setServoPulse(servoE, stE + 40);
  setServoPulse(servoF, stF + 40);
  setServoPulse(servoG, stG + 40); //右腕

  setServoPulse(servoH, stH);
  setServoPulse(servoI, stI + 50); //腰

  setServoPulse(servoK, stK + 50);
  setServoPulse(servoL, stL + 70); //170
  setServoPulse(servoM, stM + 50); //170
  setServoPulse(servoN, stN - 20);
  setServoPulse(servoO, stO + 50); //右足

  setServoPulse(servoQ, stQ - 50);
  setServoPulse(servoR, stR - 70); //30
  setServoPulse(servoS, stS - 50); //30
  setServoPulse(servoT, stT + 20);
  setServoPulse(servoU, stU - 50); //左足
  delay(t);
}

void volt1(int t)
{
  setServoPulse(servoA, stA + 50); //首

  setServoPulse(servoE, stE + 30);
  setServoPulse(servoF, stF + 90);
  setServoPulse(servoG, stG); //右腕

  setServoPulse(servoB, stB);
  setServoPulse(servoC, stC + 60);
  setServoPulse(servoD, stD); //左腕

  setServoPulse(servoH, stH);
  setServoPulse(servoI, stI); //腰

  setServoPulse(servoK, stK + 50);
  setServoPulse(servoL, stL); //170
  setServoPulse(servoM, stM); //170
  setServoPulse(servoN, stN);
  setServoPulse(servoO, stO + 50); //右足

  setServoPulse(servoQ, stQ - 50);
  setServoPulse(servoR, stR); //30
  setServoPulse(servoS, stS); //30
  setServoPulse(servoT, stT);
  setServoPulse(servoU, stU - 50); //左足

  delay(t);
}

void volt2(int t)
{
  setServoPulse(servoA, stA - 50); //首

  setServoPulse(servoB, stB - 30);
  setServoPulse(servoC, stC - 90);
  setServoPulse(servoD, stD); //左腕

  setServoPulse(servoE, stE);
  setServoPulse(servoF, stF - 60);
  setServoPulse(servoG, stG); //右腕

  setServoPulse(servoH, stH);
  setServoPulse(servoI, stI); //腰

  setServoPulse(servoK, stK + 50);
  setServoPulse(servoL, stL); //170
  setServoPulse(servoM, stM); //170
  setServoPulse(servoN, stN);
  setServoPulse(servoO, stO + 50); //右足

  setServoPulse(servoQ, stQ - 50);
  setServoPulse(servoR, stR); //30
  setServoPulse(servoS, stS); //30
  setServoPulse(servoT, stT);
  setServoPulse(servoU, stU - 50); //左足
  delay(t);
}

void human(int Time)
{
  setServoPulse(servoA, stA); //首

  setServoPulse(servoB, stB);
  setServoPulse(servoC, stC);
  setServoPulse(servoD, stD); //左腕

  setServoPulse(servoE, stE);
  setServoPulse(servoF, stF);
  setServoPulse(servoG, stG); //右腕

  setServoPulse(servoH, stH);
  setServoPulse(servoI, stI); //腰

  setServoPulse(servoK, stK + 50);
  setServoPulse(servoL, stL); //170
  setServoPulse(servoM, stM); //170
  setServoPulse(servoN, stN);
  setServoPulse(servoO, stO + 50); //右足

  setServoPulse(servoQ, stQ - 50);
  setServoPulse(servoR, stR); //30
  setServoPulse(servoS, stS); //30
  setServoPulse(servoT, stT);
  setServoPulse(servoU, stU - 50); //左足
  delay(Time);
}

void yajiron(int times)
{
  for (int i = 0; i < times; i++)
  {
    setServoPulse(servoA, stA); //首

    setServoPulse(servoB, stB);
    setServoPulse(servoC, stC);
    setServoPulse(servoD, stD); //左腕

    setServoPulse(servoE, stE);
    setServoPulse(servoF, stF - 60);
    setServoPulse(servoG, stG); //右腕

    setServoPulse(servoH, stH);
    setServoPulse(servoI, stI); //腰

    setServoPulse(servoK, stK + 50);
    setServoPulse(servoL, stL); //170
    setServoPulse(servoM, stM); //170
    setServoPulse(servoN, stN);
    setServoPulse(servoO, stO + 50); //右足

    setServoPulse(servoQ, stQ - 50);
    setServoPulse(servoR, stR); //30
    setServoPulse(servoS, stS); //30
    setServoPulse(servoT, stT);
    setServoPulse(servoU, stU - 50); //左足

    delay(KUSORAN_TEMPO / 2);

    setServoPulse(servoB, stB);
    setServoPulse(servoC, stC + 60);
    setServoPulse(servoD, stD); //左腕

    setServoPulse(servoE, stE);
    setServoPulse(servoF, stF);
    setServoPulse(servoG, stG); //右腕

    delay(KUSORAN_TEMPO / 2);
  }
}

void dokkoisyo()
{
  Tparty1(KUSORAN_TEMPO);
  syuwach(KUSORAN_TEMPO);
}

void syuwach(int t)
{
  setServoPulse(servoA, stA); //首

  setServoPulse(servoB, stB - 30);
  setServoPulse(servoC, stC - 80);
  setServoPulse(servoD, stD); //左腕

  setServoPulse(servoE, stE + 80);
  setServoPulse(servoF, stF);
  setServoPulse(servoG, stG + 90); //右腕

  setServoPulse(servoH, stH);
  setServoPulse(servoI, stI); //腰

  setServoPulse(servoK, stK + 50);
  setServoPulse(servoL, stL); //170
  setServoPulse(servoM, stM); //170
  setServoPulse(servoN, stN);
  setServoPulse(servoO, stO + 50); //右足

  setServoPulse(servoQ, stQ - 50);
  setServoPulse(servoR, stR); //30
  setServoPulse(servoS, stS); //30
  setServoPulse(servoT, stT);
  setServoPulse(servoU, stU - 50); //左足

  delay(t);

  setServoPulse(servoE, stE + 80);
  setServoPulse(servoF, stF);
  setServoPulse(servoG, stG + 40); //右腕
  delay(t * 2);
}

void gattsu(int times)
{
  for (int i = 0; i < times; i++)
  {
    setServoPulse(servoA, stA); //首

    setServoPulse(servoB, stB);
    setServoPulse(servoC, stC);
    setServoPulse(servoD, stD - 80); //左腕

    setServoPulse(servoE, stE);
    setServoPulse(servoF, stF);
    setServoPulse(servoG, stG + 80); //右腕

    setServoPulse(servoH, stH);
    setServoPulse(servoI, stI); //腰

    setServoPulse(servoK, stK + 50);
    setServoPulse(servoL, stL + 70); //170
    setServoPulse(servoM, stM + 40); //170
    setServoPulse(servoN, stN - 30);
    setServoPulse(servoO, stO + 50); //右足

    setServoPulse(servoQ, stQ - 50);
    setServoPulse(servoR, stR - 70); //30
    setServoPulse(servoS, stS - 40); //30
    setServoPulse(servoT, stT + 30);
    setServoPulse(servoU, stU - 50); //左足

    delay(KUSORAN_TEMPO * 2);

    setServoPulse(servoA, stA); //首

    setServoPulse(servoB, stB);
    setServoPulse(servoC, stC);
    setServoPulse(servoD, stD - 80); //左腕

    setServoPulse(servoE, stE);
    setServoPulse(servoF, stF);
    setServoPulse(servoG, stG + 80); //右腕

    setServoPulse(servoH, stH);
    setServoPulse(servoI, stI); //腰

    setServoPulse(servoK, stK + 50);
    setServoPulse(servoL, stL); //170
    setServoPulse(servoM, stM); //170
    setServoPulse(servoN, stN);
    setServoPulse(servoO, stO + 50); //右足

    setServoPulse(servoQ, stQ - 50);
    setServoPulse(servoR, stR); //30
    setServoPulse(servoS, stS); //30
    setServoPulse(servoT, stT);
    setServoPulse(servoU, stU - 50); //左足

    delay(KUSORAN_TEMPO * 2);

    setServoPulse(servoB, stB - 10);
    setServoPulse(servoE, stE + 10);
    delay(KUSORAN_TEMPO);

    setServoPulse(servoB, stB - 20);
    setServoPulse(servoE, stE + 20);
    delay(KUSORAN_TEMPO);

    setServoPulse(servoB, stB - 30);
    setServoPulse(servoE, stE + 30);
    delay(KUSORAN_TEMPO);

    setServoPulse(servoB, stB - 40);
    setServoPulse(servoE, stE + 40);
    delay(KUSORAN_TEMPO);


  }
}

void biem(int times)
{
  for (int i = 0; i < times / 2; i++)
  {
    volt1(KUSORAN_TEMPO);
    volt2(KUSORAN_TEMPO);
    volt1(KUSORAN_TEMPO * 2);

    volt2(KUSORAN_TEMPO);
    volt1(KUSORAN_TEMPO);
    volt2(KUSORAN_TEMPO * 2);
  }
}

void dosuru(int t)
{
  setServoPulse(servoA, stA); //首

  setServoPulse(servoB, stB - 40);
  setServoPulse(servoC, stC);
  setServoPulse(servoD, stD - 80); //左腕

  setServoPulse(servoE, stE + 40);
  setServoPulse(servoF, stF);
  setServoPulse(servoG, stG + 80); //右腕

  setServoPulse(servoH, stH);
  setServoPulse(servoI, stI); //腰

  setServoPulse(servoK, stK + 50);
  setServoPulse(servoL, stL); //170
  setServoPulse(servoM, stM); //170
  setServoPulse(servoN, stN);
  setServoPulse(servoO, stO + 50); //右足

  setServoPulse(servoQ, stQ - 50);
  setServoPulse(servoR, stR); //30
  setServoPulse(servoS, stS); //30
  setServoPulse(servoT, stT);
  setServoPulse(servoU, stU - 50); //左足

  delay(t);
}


/******************/

/*****ばいばい*****/
void bye(int times)
{
  print_c("Bye %d times\n", times);

  setServoPulse(servoB, stB - 50);
  setServoPulse(servoC, stC + 80);
  for (int i = 0; i < times; i ++)
  {
    int tim = 20;
    for (int j = 0; j < 8; j++)
    {
      setServoPulse(servoD, stD - 80 + j * 10); //左腕
      delay(tim);
    }
    for (int j = 0; j < 8; j++)
    {
      setServoPulse(servoD, stD - j * 10); //左腕
      delay(tim);
    }
  }

}

/**************/

/*****Core Functions*****/
uint8_t setServoPulse(uint8_t n, uint8_t degress) {
  if (degress > 180)
    return false;
  double pulse = map(degress, 0, 180, SERVOMIN, SERVOMAX);
  //Serial.println(pulse);
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

void setLEDColor(uint16_t color) {
  setLEDr(map(colorUtil::getRED(color), 0, 255, 0, LEDREDMAX));
  setLEDb(map(colorUtil::getBLUE(color), 0, 255, 0, LEDBLUEMAX));
  setLEDg(map(colorUtil::getGREEN(color), 0, 255, 0, LEDGREENMAX));
}

bool setLEDr(uint16_t value) {
  if (value > 4095 || value < 0)
    return false;
  pwm1.setPWM(LEDr, 0, value);
}

bool setLEDb(uint16_t value) {
  if (value > 4095 || value < 0)
    return false;
  pwm1.setPWM(LEDb, 0, value);
}

bool setLEDg(uint16_t value) {
  if (value > 4095 || value < 0)
    return false;
  pwm1.setPWM(LEDg, 0, value);
}
