#include <NewPing.h> //HC-SR04函式庫

#define MAX_DISTANCE 80 //設定超聲波最大偵測範圍

#define TRIGGER_PIN_L  34
#define ECHO_PIN_L     36
NewPing sonar_L(TRIGGER_PIN_L, ECHO_PIN_L, MAX_DISTANCE); //左邊超聲波

//#define Lcm sonar_L.convert_cm(us_L)
#define Lcm sonar_L.ping_cm()

#define TRIGGER_PIN_R  40
#define ECHO_PIN_R     38
NewPing sonar_R(TRIGGER_PIN_R, ECHO_PIN_R, MAX_DISTANCE); //右邊超聲波

#define Rcm sonar_R.ping_cm()
//#define Rcm sonar_R.convert_cm(us_R)

int Moter[5][4] =
{
  {47, 46 }, //------------------AA
  {47, 48 }, //------------------AB
  {49, 46 }, //------------------BA
  {49, 48 }, //------------------BB
  {47, 49 , 46 , 48 } //-------------馬驅右AB腳,馬驅左AB腳
}; //----------------------------馬達方位控制腳

int Motor_PWM_R = 45; //--------直向右邊馬達速度控制腳
int Motor_PWM_L = 44; //--------直向左邊馬達速度控制腳


int Walk_Speed = 240; //---------正常走路速度
int Walk_Speed_Max = 255; //----最快走路速度

int Mode_Button [] = {22, 24, 26, 28};//四顆按鈕

//----------<<按鈕調整區>>----------按下為LOW
#define ButtonA digitalRead(Mode_Button[0])
#define ButtonB digitalRead(Mode_Button[1])
#define ButtonC digitalRead(Mode_Button[2])
#define ButtonD digitalRead(Mode_Button[3])
//----------<<按鈕調整區>>----------

int IR_R = 32; //-----------右邊紅外線
int IR_L = 30; //-----------左邊紅外線

//----------<<循線調整區>>----------循出線色為HIGH
#define IR_R_OUT digitalRead(IR_R)==LOW
#define IR_L_OUT digitalRead(IR_L)==LOW
#define IR_R_On digitalRead(IR_R)==HIGH
#define IR_L_On digitalRead(IR_L)==HIGH
//----------<<循線調整區>>----------

void setup()
{
  Serial.begin(9600);

  pinMode(IR_R, INPUT);//右邊紅外線宣告
  pinMode(IR_L, INPUT);//左邊紅外線宣告

  for (int i = 0; i < 4; i++)
  {
    pinMode(Moter[4][i], OUTPUT);//定義直向馬達為輸出腳
    digitalWrite(Moter[4][i], LOW);//直向馬達煞車
    pinMode(Mode_Button[i], INPUT);//按鈕宣告
  }
}

void loop()
{
  Button();
}

void motercontrol(int Mmode)
{
  if (Mmode != 4)
    Walk_Speed = 240;

  switch (Mmode)
  {
    case 0:
      for (int i = 0; i < 4; i++)
        digitalWrite(Moter[4][i], LOW);

      break; //---------------------------直向馬達煞車

    case 1:
      for (int i = 0; i < 2; i++)
      {
        digitalWrite(Moter[1][i], LOW);
        digitalWrite(Moter[2][i], HIGH);
      }

      analogWrite(Motor_PWM_L, Walk_Speed);
      analogWrite(Motor_PWM_R, Walk_Speed / 3);
      break; //---------------------------向右偏移

    case 2:
      for (int i = 0; i < 2; i++)
      {
        digitalWrite(Moter[1][i], LOW);
        digitalWrite(Moter[2][i], HIGH);
      }

      analogWrite(Motor_PWM_L, Walk_Speed / 3);
      analogWrite(Motor_PWM_R, Walk_Speed);
      break; //---------------------------向左偏移

    case 3:
      for (int i = 0; i < 2; i++)
      {
        digitalWrite(Moter[1][i], LOW);
        digitalWrite(Moter[2][i], HIGH);
      }

      analogWrite(Motor_PWM_L, Walk_Speed);
      analogWrite(Motor_PWM_R, Walk_Speed);
      break; //---------------------------前進

    case 4:
      for (int i = 0; i < 2; i++)
      {
        digitalWrite(Moter[1][i], LOW);
        digitalWrite(Moter[2][i], HIGH);
      }

      if (Walk_Speed < Walk_Speed_Max && Mmode == 4)
      {
        Walk_Speed += 5;
        delay(10);
        analogWrite(Motor_PWM_L, Walk_Speed);
        analogWrite(Motor_PWM_R, Walk_Speed);
      }
      break; //---------------------------加速前進

    case 5:
      for (int i = 0; i < 2; i++)
      {
        digitalWrite(Moter[1][i], LOW);
        digitalWrite(Moter[2][i], HIGH);
      }

      analogWrite(Motor_PWM_L, Walk_Speed_Max);
      analogWrite(Motor_PWM_R, Walk_Speed_Max);
      break; //---------------------------全速前進

    case 6:
      for (int i = 0; i < 2; i++)
      {
        digitalWrite(Moter[3][i], LOW);
        digitalWrite(Moter[0][i], HIGH);
      }

      analogWrite(Motor_PWM_L, Walk_Speed);
      analogWrite(Motor_PWM_R, Walk_Speed);
      break; //---------------------------原地右旋轉

    case 7:
      for (int i = 0; i < 2; i++)
      {
        digitalWrite(Moter[0][i], LOW);
        digitalWrite(Moter[3][i], HIGH);
      }

      analogWrite(Motor_PWM_L, Walk_Speed);
      analogWrite(Motor_PWM_R, Walk_Speed);
      break; //---------------------------原地左旋轉

    case 8:
      for (int i = 0; i < 2; i++)
      {
        digitalWrite(Moter[2][i], LOW);
        digitalWrite(Moter[1][i], HIGH);
      }

      analogWrite(Motor_PWM_L, Walk_Speed);
      analogWrite(Motor_PWM_R, Walk_Speed);
      break; //---------------------------後退

    default:
      for (int i = 0; i < 4; i++)
        digitalWrite(Moter[4][i], HIGH);
      break;//---------------------------滑行
  }
}

void Button()
{
  if (ButtonA == LOW)
  {
    delay(10);
    if (ButtonA == LOW)
      Mode_1();
  }

  else if (ButtonB == LOW)
  {
    delay(10);
    if (ButtonB == LOW)
      Mode_2();
  }

  else if (ButtonC == LOW)
  {
    delay(10);
    if (ButtonC == LOW)
      Mode_3();
  }

  else if (ButtonD == LOW)
  {
    delay(10);
    if (ButtonD == LOW)
      Mode_4();
  }
}

void Mode_1()//停止
{
  motercontrol(0);
}

void Mode_2()//馬達測試
{
  motercontrol(5);//出場
  delay(1500);

  while (ButtonA == HIGH)
  {
    if ((Rcm < 30 && Rcm != 0) || (Lcm < 30 && Lcm != 0)) //左右超聲波距離都在衝撞範圍
    {
      motercontrol(4);
    }
    else
    {
      if (IR_R_OUT && IR_L_On)//右邊紅外線碰到白線
      {
        motercontrol(8);
        delay(500);
        motercontrol(7);
        delay(random(3, 10) * 120);
      }
      else if (IR_R_On && IR_L_OUT)//左邊紅外線碰到白線
      {
        motercontrol(8);
        delay(500);
        motercontrol(6);
        delay(random(3, 10) * 120);
      }
      else if (IR_R_OUT && IR_L_OUT)//兩邊紅外線碰到白線
      {
        motercontrol(6);
      }
      else if (IR_R_On && IR_L_On)
      {
        if ((Rcm < 70 && Rcm != 0) || (Lcm < 70 && Lcm != 0))
          motercontrol(4);
        else
          motercontrol(6);
      }
    }
  }
}

void Mode_3()//乖寶寶
{
  motercontrol(5);//出場
  delay(1500);

  while (ButtonA == HIGH)
  {
    if ((Rcm < 30 && Rcm != 0) || (Lcm < 30 && Lcm != 0)) //左右超聲波距離都在衝撞範圍
    {
      motercontrol(4);
    }
    else
    {
      if (IR_R_OUT && IR_L_On)//右邊紅外線碰到白線
      {
        motercontrol(8);
        delay(500);
        motercontrol(7);
        delay(random(3, 10) * 120);
      }
      else if (IR_R_On && IR_L_OUT)//左邊紅外線碰到白線
      {
        motercontrol(8);
        delay(500);
        motercontrol(6);
        delay(random(3, 10) * 120);
      }
      else if (IR_R_OUT && IR_L_OUT)//兩邊紅外線碰到白線
      {
        motercontrol(6);
      }
      else if (IR_R_On && IR_L_On)
      {
        if (Rcm < 60 && Rcm != 0 && Lcm < 60 && Lcm != 0)
          motercontrol(4);
        else if (Rcm < 60 && Rcm != 0 && Lcm == 0)
          motercontrol(1);
        else  if (Rcm == 0 && Lcm < 60 && Lcm != 0)
          motercontrol(2);
        else
          motercontrol(3);
      }
    }
  }
}

void Mode_4()//過敏兒
{
  motercontrol(5);//出場
  delay(1500);

  while (ButtonA == HIGH)
  {
    if ((Rcm < 30 && Rcm != 0) || (Lcm < 30 && Lcm != 0)) //左右超聲波距離都在衝撞範圍
    {
      motercontrol(4);
    }
    else
    {
      if (IR_R_OUT && IR_L_On)//右邊紅外線碰到白線
      {
        motercontrol(8);
        delay(500);
        motercontrol(7);
        delay(random(3, 12) * 100);
      }
      else if (IR_R_On && IR_L_OUT)//左邊紅外線碰到白線
      {
        motercontrol(8);
        delay(500);
        motercontrol(6);
        delay(random(3, 12) * 100);
      }
      else if (IR_R_OUT && IR_L_OUT)//兩邊紅外線碰到白線
      {
        motercontrol(6);
      }
      else if (IR_R_On && IR_L_On)
      {
        if ((Rcm < 70 && Rcm != 0) || (Lcm < 70 && Lcm != 0))
          motercontrol(4);
        else
          motercontrol(7);
      }
    }
  }
}
