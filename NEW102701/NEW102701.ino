int trigPin_L = 35;
int echoPin_L = 37;
int trigPin_R = 39;
int echoPin_R = 41;

long duration_L, Lcm, duration_R, Rcm ;  //宣告計算距離時，需要用到的兩個實數

int IR_L = 31; //-----------左邊紅外線
int IR_R = 33; //-----------右邊紅外線
#define IR_state HIGH //紅外線狀態
#define IR_L digitalRead(IR_L)
#define IR_R digitalRead(IR_R)

int sw1 = 23;
int sw2 = 25;
int sw3 = 27;
int sw4 = 29;

int L[] = {3, 2, 7}; //motor1 (in1A,in1B,pwm1)
int R[] = {5, 6, 4}; //motor2 (in2A,in2B,pwm2)

int mode = 0;

unsigned long time_walk = 0;//宣告時間計數器
unsigned long time_rise = 0;

void setup() {

  Serial.begin(9600);
  randomSeed(analogRead(A0));

  pinMode(IR_L, INPUT);//red
  pinMode(IR_R, INPUT);

  pinMode(L[0], OUTPUT);//motor1
  pinMode(L[1], OUTPUT);

  pinMode(R[0], OUTPUT);//motor2
  pinMode(R[1], OUTPUT);

  digitalWrite(L[0], LOW);//初始狀態
  digitalWrite(L[1], LOW);
  digitalWrite(R[0], LOW);
  digitalWrite(R[1], LOW);

  pinMode(sw1, INPUT);
  pinMode(sw2, INPUT);
  pinMode(sw3, INPUT);
  pinMode(sw4, INPUT);

  pinMode(trigPin_L, OUTPUT);      //Arduino 對外啟動距離感測器Trig腳，射出超音波
  pinMode(echoPin_L, INPUT);       //超音波被障礙物反射後，Arduino讀取感測器Echo腳的時間差
  pinMode(trigPin_R, OUTPUT);
  pinMode(echoPin_R, INPUT);

   
}

void loop() {

  select();

  switch (mode)
  {
    case 1:
        IR();
      Serial.println(" mode1 ");
      break;
    case 2:
        IR();
      Serial.println(" mode2 ");
      break;
    case 3:
        IR();
      Serial.println(" mode3 ");
      break;
    case 4:
        IR();
      Serial.println(" mode4 ");
      break;
    default:
      Serial.println(" x ");
      break;
  }
}

void select()
{
  if (digitalRead(sw1) == LOW)//                                              sw 1
  {
    delay(20);
    if (digitalRead(sw1) == LOW) {
      go(80);
      delay(700);
      mode = 1;
    }
  }
  else if (digitalRead(sw2) == LOW)//                                              sw 2
  {
    delay(20);
    if (digitalRead(sw2) == LOW) {
      mode = 2;
      circle_R(60);
      delay(450);
      go(80);
      delay(700);
    }
  }
  else if (digitalRead(sw3) == LOW)//                                              sw 3
  {
    delay(20);
    if (digitalRead(sw3) == LOW) {
      mode = 3;
      go(120);
      delay(300);
    }
  }
  else if (digitalRead(sw4) == LOW)//                                              sw 4
  {
    delay(20);
    if (digitalRead(sw4) == LOW) {
      mode = 4;
      delay(2000);
      go(120);
      delay(300);
    }
  }
}

void IR()
{
  if ((IR_L == IR_state) && (IR_R == IR_state) ) //都黑
  {
    Serial.println("L:黑 R:黑");
    if (mode == 1)
    {
      m0();
      Serial.println("m0 ok");
    }
    else if (mode == 2)
    {
      m1();
      Serial.println("m1 ok");
    }
    else if (mode == 3)
    {

      m2();
      Serial.println("m2 ok");
    }
    else if (mode == 4)
    {

      m3();
      Serial.println("m3 ok");
    }
  }
  else if ((IR_L == IR_state) && (IR_R == !(IR_state)) ) //左黑
  {
//    if (mode == 1 || mode == 2)
//    {
     int i = random(300, 500);
      stopp();
      delay(20);
      back();
      delay(800);
      three_L(i, 60);
//    }
//    else if (mode == 3)
//    {
//      int i = random(300, 500);
//      stopp();
//      delay(20);
//      back();
//      delay(800);
//      three_R(i, 60);
//    }
    Serial.println("L:黑 R:白");
  }
  else if ((IR_L == !(IR_state)) && (IR_R == IR_state) ) //右黑
  {
//    if (mode == 1 || mode == 2)
//    {
      int i = random(300, 600);
      stopp();
      delay(20);
      back();
      delay(800);
      three_R(i, 60);
//    }
//    else if (mode == 3)
//    {
//      int i = random(300, 600);
//      stopp();
//      delay(20);
//      back();
//      delay(800);
//      three_L(i, 60);
//    }
    Serial.println("L:白 R:黑");
  }
  else if (((IR_L) == !(IR_state)) && ((IR_R) == !(IR_state) )) //都白
  {
//    if (mode == 1 || mode == 2)
//    {
       int i = random(300, 600);
      stopp();
      delay(20);
      back();
      delay(1000);
      circle_L(60);
      delay(i);
//    }
//    else if (mode == 3)
//    {
//      int i = random(300, 600);
//      stopp();
//      delay(20);
//      back();
//      delay(1000);
//      circle_R(60);
//      delay(i);
//    }
    Serial.println("L:白 R:白");
  }
}

void m0()//中間找人
{
  HRSR04();

  if ((Lcm >= 40 && Rcm >= 40) || (Lcm == 0 && Rcm == 0))
  {
    circle_L(37);
    Serial.println("旋轉");
  }
  else if ((Lcm == 0 && Rcm >= 40) || (Lcm >= 40 && Rcm == 0))
  {
    circle_L(37);
    Serial.println("旋轉");
  }
  else if (Lcm < 40 && (Rcm == 0 || Rcm > 40))
  {
    turn(80, 10);
    Serial.println(" 左邊有人 ");
  }
  else if ((Lcm == 0 || Lcm > 40) && Rcm < 40)
  {
    turn(10, 80);
    Serial.println(" 右邊有人 ");
  }
  else if (Lcm <= 30 && (Rcm == 0 || Rcm > 30))
  {
    turn(150, 10);
    Serial.println("左邊有人");
  }
  else if ((Lcm == 0 || Lcm > 30) && Rcm <= 30)
  {
    turn(10, 150);
    Serial.println("右邊有人");
  }
  else if ((Lcm < 25 && Rcm < 25) && (Lcm >= 1 && Rcm >= 1))
  {

    int value = 150;
    while (Lcm < 25 && Rcm < 25)
    {
      HRSR04();
      //      Serial.print("Lcm:");
      //      Serial.println(Lcm);
      //      Serial.print("Rcm:");
      //      Serial.println(Rcm);
      go(value);
      value ++;
      delay(0.01);
      if (value >= 255)
        value = 255;
      if (Lcm > 25 && Rcm > 25)
        break;
      else if (Lcm ==  0 && Rcm == 0)
        break;
      //      Serial.print("value:");
      //      Serial.println(value);
    }
  }
}

void m1()
{
  HRSR04();

  if ((Lcm >= 40 && Rcm >= 40) || (Lcm == 0 && Rcm == 0))
  {
    //    IR();
    go(60);
    //    IR();
    Serial.println(" 沒人 ");
  }
  else if (Lcm < 40 && (Rcm == 0 || Rcm > 40))
  {
    turn(80, 10);
    Serial.println(" 左邊有人 ");
  }
  else if ((Lcm == 0 || Lcm > 40) && Rcm < 40)
  {
    turn(10, 80);
    Serial.println(" 右邊有人 ");
  }
  else if (Lcm <= 32 && (Rcm == 0 || Rcm > 32))
  {
    turn(150, 10);
    Serial.println("左邊有人");
  }
  else if ((Lcm == 0 || Lcm > 32) && Rcm <= 32)
  {
    turn(10, 150);
    Serial.println("右邊有人");
  }
  else if ((Lcm < 25 && Rcm < 25) && (Lcm >= 1 && Rcm >= 1))
  {
    int value = 150;
    while (Lcm < 25 && Rcm < 25)
    {
      HRSR04();
      //      Serial.print("Lcm:");
      //      Serial.println(Lcm);
      //      Serial.print("Rcm:");
      //      Serial.println(Rcm);
      go(value);
      value ++;
      delay(0.01);
      if (value >= 255)
        value = 255;
      if (Lcm > 25 && Rcm > 25)
        break;
      else if (Lcm ==  0 && Rcm == 0)
        break;
      //      Serial.print("value:");
      //      Serial.println(value);
    }

  }
  //  Serial.print(" Left ");
  //  Serial.print(Lcm);
  //  Serial.print("cm  ");
  //
  //  Serial.print("Right ");
  //  Serial.print(Rcm);
  //  Serial.print("cm  ");
}

void m2()//繞圈圈
{
  HRSR04();

  if ((Lcm >= 40 && Rcm >= 40) || (Lcm == 0 && Rcm == 0))
  {
    go(80);
    Serial.println(" 沒人 ");
  }
  else if (Lcm < 40 && (Rcm == 0 || Rcm > 40))
  {
    turn(100, 30);
    Serial.println(" 左邊有人 ");
  }
  else if ((Lcm == 0 || Lcm > 40) && Rcm < 40)
  {
    turn(30, 100);
    Serial.println(" 右邊有人 ");
  }
  else if (Lcm <= 32 && (Rcm == 0 || Rcm >= 32))
  {
    turn(170, 20);
    Serial.println("左邊有人");
  }
  else if ((Lcm == 0 || Lcm >= 32) && Rcm <= 32)
  {
    turn(30, 170);
    Serial.println("右邊有人");
  }
  else if ((Lcm < 25 && Rcm < 25) && (Lcm >= 1 && Rcm >= 1))
  {
    int value = 170;
    while (Lcm < 25 && Rcm < 25)
    {
      HRSR04();
      go(value);
      value ++;
      delay(0.01);
      if (value >= 255)
        value = 255;
      if (Lcm > 25 && Rcm > 25)
        break;
      else if (Lcm ==  0 && Rcm == 0)
        break;
    }
  }
}

void m3()
{
   HRSR04();

  if ((Lcm >= 40 && Rcm >= 40) || (Lcm == 0 && Rcm == 0))
  {
    go(80);
    Serial.println(" 沒人 ");
  }
  else if (Lcm < 40 && (Rcm == 0 || Rcm > 40))
  {
    turn(100, 30);
    Serial.println(" 左邊有人 ");
  }
  else if ((Lcm == 0 || Lcm > 40) && Rcm < 40)
  {
    turn(30, 100);
    Serial.println(" 右邊有人 ");
  }
  else if (Lcm <= 32 && (Rcm == 0 || Rcm > 32))
  {
    turn(170, 20);
    Serial.println("左邊有人");
  }
  else if ((Lcm == 0 || Lcm > 32) && Rcm <= 32)
  {
    turn(30, 170);
    Serial.println("右邊有人");
  }
  else if ((Lcm < 25 && Rcm < 25) && (Lcm >= 1 && Rcm >= 1))
  {
    int value = 170;
    while (Lcm < 25 && Rcm < 25)
    {
      HRSR04();
      go(value);
      value ++;
      delay(0.01);
      if (value >= 255)
        value = 255;
      if (Lcm > 25 && Rcm > 25)
        break;
      else if (Lcm ==  0 && Rcm == 0)
        break;
    }
  }
}

void go(int value)//前進
{
  digitalWrite(L[0], LOW);
  digitalWrite(L[1], HIGH);
  digitalWrite(R[0], LOW);
  digitalWrite(R[1], HIGH);

  analogWrite(L[2], value );
  analogWrite(R[2], value );
}

void turn(int value_L, int value_R)
{
  digitalWrite(L[0], LOW);
  digitalWrite(L[1], HIGH);
  digitalWrite(R[0], LOW);
  digitalWrite(R[1], HIGH);

  analogWrite(L[2], value_L );
  analogWrite(R[2], value_R );
}

void back()//後退
{
  digitalWrite(L[0], HIGH);
  digitalWrite(L[1], LOW);
  digitalWrite(R[0], HIGH);
  digitalWrite(R[1], LOW);

  analogWrite(L[2], 60 );
  analogWrite(R[2], 60 );
}

void back_r()//向右後退
{
  int i = random(70, 90);
  int j = random(20, 40);
  Serial.println(i);
  Serial.println(j);

  digitalWrite(L[0], HIGH);
  digitalWrite(L[1], LOW);
  digitalWrite(R[0], HIGH);
  digitalWrite(R[1], LOW);

  analogWrite(L[2], i );
  analogWrite(R[2], j );

  delay(600);
}

void back_l()//向左後退
{
  int i = random(20, 40);
  int j = random(70, 90);
  Serial.println(i);
  Serial.println(j);

  digitalWrite(L[0], HIGH);
  digitalWrite(L[1], LOW);
  digitalWrite(R[0], HIGH);
  digitalWrite(R[1], LOW);

  analogWrite(L[2], i );
  analogWrite(R[2], j );

  delay(600);
}

void circle_L(int i)//逆時針
{
  digitalWrite(L[0], HIGH);
  digitalWrite(L[1], LOW);
  digitalWrite(R[0], LOW);
  digitalWrite(R[1], HIGH);

  analogWrite(L[2], i );
  analogWrite(R[2], i );
}

void circle_R(int i)//順時針
{
  digitalWrite(L[0], LOW);
  digitalWrite(L[1], HIGH);
  digitalWrite(R[0], HIGH);
  digitalWrite(R[1], LOW);

  analogWrite(L[2], i );
  analogWrite(R[2], i );
}

void stopp()//停止
{
  digitalWrite(L[0], LOW);
  digitalWrite(L[1], LOW);
  digitalWrite(R[0], LOW);
  digitalWrite(R[1], LOW);
}

void three_L(int timecount, int value)//扇形向左
{
  time_rise = millis();
  while (millis() - time_rise <= timecount)
  {
    digitalWrite(L[0], HIGH);
    digitalWrite(L[1], LOW);
    digitalWrite(R[0], LOW);
    digitalWrite(R[1], HIGH);

    analogWrite(L[2], value );
    analogWrite(R[2], value );
  }
}

void three_R(int timecount, int value)//扇形向右
{
  time_rise = millis();
  while (millis() - time_rise <= timecount)
  {
    digitalWrite(L[0], LOW);
    digitalWrite(L[1], HIGH);
    digitalWrite(R[0], HIGH);
    digitalWrite(R[1], LOW);

    analogWrite(L[2], value );
    analogWrite(R[2], value );
  }
}

void HRSR04()
{
  digitalWrite(trigPin_L, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin_L, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_L, LOW);
  pinMode(echoPin_L, INPUT);
  duration_L = pulseIn(echoPin_L, HIGH);
  Lcm = (duration_L / 2) / 29.1;

  digitalWrite(trigPin_R, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin_R, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_R, LOW);
  pinMode(echoPin_R, INPUT);
  duration_R = pulseIn(echoPin_R, HIGH);
  Rcm = (duration_R / 2) / 29.1;
}
