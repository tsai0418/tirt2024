int LF[] = {5, 6, 7}; //(p,a,b)
int RF[] = {4, 3, 2};
int LB[] = {12, 11, 13};
int RB[] = {10, 9, 8};

void setup() {
  Serial.begin(9600);

  //第一個馬達
  pinMode(RF[1], OUTPUT);
  pinMode(RF[2], OUTPUT);

  //第二個馬達
  pinMode(LF[1], OUTPUT);
  pinMode(LF[2], OUTPUT);

  //第三個馬達
  pinMode(RB[1], OUTPUT);
  pinMode(RB[2], OUTPUT);

  //第四個馬達
  pinMode(LB[1], OUTPUT);
  pinMode(LB[2], OUTPUT);

  digitalWrite(RF[1], LOW);
  digitalWrite(RF[2], LOW);
  digitalWrite(LF[1], LOW);
  digitalWrite(LF[2], LOW);
  digitalWrite(RB[1], LOW);
  digitalWrite(RB[2], LOW);
  digitalWrite(LB[1], LOW);
  digitalWrite(LB[2], LOW);
  //
  //  right_front();
  //  delay(3000);
  //
  //  stopp();
  stopp();
  delay(800);


}

void loop() {
    right_max();
  
 }


void turn_L(int value) { //原地左旋
  digitalWrite(RF[1], HIGH);
  digitalWrite(RF[2], LOW);
  digitalWrite(LF[2], HIGH);
  digitalWrite(LF[1], LOW);
  digitalWrite(RB[1], HIGH);
  digitalWrite(RB[2], LOW);
  digitalWrite(LB[2], HIGH);
  digitalWrite(LB[1], LOW);

  analogWrite(RF[0], value);
  analogWrite(LF[0], value);
  analogWrite(RB[0], value);
  analogWrite(LB[0], value);
}
void ff()//前進
{
  digitalWrite(RF[1], HIGH);
  digitalWrite(RF[2], LOW);
  digitalWrite(LF[1], HIGH);
  digitalWrite(LF[2], LOW);
  digitalWrite(RB[1], HIGH);
  digitalWrite(RB[2], LOW);
  digitalWrite(LB[1], HIGH);
  digitalWrite(LB[2], LOW);

  analogWrite(RF[0], 232);
  analogWrite(LF[0], 255);
  analogWrite(RB[0], 255);
  analogWrite(LB[0], 255);
}

void back()//後退
{
  digitalWrite(RF[2], HIGH);
  digitalWrite(RF[1], LOW);
  digitalWrite(LF[2], HIGH);
  digitalWrite(LF[1], LOW);
  digitalWrite(RB[2], HIGH);
  digitalWrite(RB[1], LOW);
  digitalWrite(LB[2], HIGH);
  digitalWrite(LB[1], LOW);

  analogWrite(RF[0], 232);
  analogWrite(LF[0], 255);
  analogWrite(RB[0], 255);
  analogWrite(LB[0], 255);
}

void stopp()//停止
{
  digitalWrite(RF[1], LOW);
  digitalWrite(RF[2], LOW);
  digitalWrite(LF[1], LOW);
  digitalWrite(LF[2], LOW);
  digitalWrite(RB[1], LOW);
  digitalWrite(RB[2], LOW);
  digitalWrite(LB[1], LOW);
  digitalWrite(LB[2], LOW);
}

void turn_L(int value_LF, int value_RF, int value_LB, int value_RB) { //原地左旋
  digitalWrite(RF[1], HIGH);
  digitalWrite(RF[2], LOW);
  digitalWrite(LF[2], HIGH);
  digitalWrite(LF[1], LOW);
  digitalWrite(RB[1], HIGH);
  digitalWrite(RB[2], LOW);
  digitalWrite(LB[2], HIGH);
  digitalWrite(LB[1], LOW);

  analogWrite(RF[0], value_LF);
  analogWrite(LF[0], value_RF);
  analogWrite(RB[0], value_LB);
  analogWrite(LB[0], value_RB);
}

void turn_R(int value_LF, int value_RF, int value_LB, int value_RB) { //原地右旋
  digitalWrite(RF[2], HIGH);
  digitalWrite(RF[1], LOW);
  digitalWrite(LF[1], HIGH);
  digitalWrite(LF[2], LOW);
  digitalWrite(RB[2], HIGH);
  digitalWrite(RB[1], LOW);
  digitalWrite(LB[1], HIGH);
  digitalWrite(LB[2], LOW);

  analogWrite(RF[0], value_LF);
  analogWrite(LF[0], value_RF);
  analogWrite(RB[0], value_LB);
  analogWrite(LB[0], value_RB);
}

void right()//右移
{
  digitalWrite(LF[1], HIGH);
  digitalWrite(LF[2], LOW);
  digitalWrite(RB[1], HIGH);
  digitalWrite(RB[2], LOW);
  digitalWrite(RF[2], HIGH);
  digitalWrite(RF[1], LOW);
  digitalWrite(LB[2], HIGH);
  digitalWrite(LB[1], LOW);

  analogWrite(RF[0], 51);
  analogWrite(LF[0], 51);
  analogWrite(RB[0], 53);
  analogWrite(LB[0], 50);
}

void right_max()//右移最大速度
{
  digitalWrite(LF[1], HIGH);
  digitalWrite(LF[2], LOW);
  digitalWrite(RB[1], HIGH);
  digitalWrite(RB[2], LOW);
  digitalWrite(RF[2], HIGH);
  digitalWrite(RF[1], LOW);
  digitalWrite(LB[2], HIGH);
  digitalWrite(LB[1], LOW);

  analogWrite(RF[0], 235);
  analogWrite(LF[0], 255);
  analogWrite(RB[0], 255);
  analogWrite(LB[0], 255);
}

void left_max()//左移最大速度
{
  digitalWrite(LF[2], HIGH);
  digitalWrite(LF[1], LOW);
  digitalWrite(RB[2], HIGH);
  digitalWrite(RB[1], LOW);
  digitalWrite(RF[1], HIGH);
  digitalWrite(RF[2], LOW);
  digitalWrite(LB[1], HIGH);
  digitalWrite(LB[2], LOW);

  analogWrite(RF[0], 244);
  analogWrite(LF[0], 255);
  analogWrite(RB[0], 255);
  analogWrite(LB[0], 255);
}

void aaa()//慢慢加速
{
  for (int i = 30; i < 255; i++) {
    digitalWrite(RF[1], HIGH);
    digitalWrite(RF[2], LOW);
    digitalWrite(LF[1], HIGH);
    digitalWrite(LF[2], LOW);
    digitalWrite(RB[1], HIGH);
    digitalWrite(RB[2], LOW);
    digitalWrite(LB[1], HIGH);
    digitalWrite(LB[2], LOW);

    analogWrite(RF[0], i);
    analogWrite(LF[0], i);
    analogWrite(RB[0], i);
    analogWrite(LB[0], i);

    delay(10);
  }
}

void bbb()//慢慢減速
{
  for (int i = 255; i >= 0; i--) {
    digitalWrite(RF[1], HIGH);
    digitalWrite(RF[2], LOW);
    digitalWrite(LF[1], HIGH);
    digitalWrite(LF[2], LOW);
    digitalWrite(RB[1], HIGH);
    digitalWrite(RB[2], LOW);
    digitalWrite(LB[1], HIGH);
    digitalWrite(LB[2], LOW);

    analogWrite(RF[0], i);
    analogWrite(LF[0], i);
    analogWrite(RB[0], i);
    analogWrite(LB[0], i);

    delay(10);
  }
}

void right_1()
{
  right_max();
  delay(1400);
  stopp();
}

void right_2()
{
  right_max();
  delay(3000);
  stopp();
}

void go_1()
{
  ff();
  delay(1900);
  stopp();
}
