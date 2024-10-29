int IR_L = 26; //-----------左邊紅外線
int IR_R = 28; //-----------右邊紅外線
int IR_TL = 22; //-----------轉彎紅外線左
int IR_TR = 24; //-----------轉彎紅外線右
int E18 = 36;//紅外線避障

#define IR_state HIGH //紅外線狀態 黑
#define IR_L digitalRead(IR_L)
#define IR_R digitalRead(IR_R)
#define IR_TL !digitalRead(IR_TL)
#define IR_TR digitalRead(IR_TR)
#define E18 digitalRead(E18)

void setup()
{
  Serial.begin(9600);

  pinMode(IR_L, INPUT);
  pinMode(IR_R, INPUT);
  pinMode(IR_TL, INPUT);
  pinMode(IR_TR, INPUT);
  pinMode(E18, INPUT);
}

void loop()
{
  delay(500);
  if (IR_L)
    Serial.println("L:黑 ");
  else
    Serial.println("L:白 ");
  if (IR_R)
    Serial.println("R:黑 ");
  else
    Serial.println("R:白 ");
  if (IR_TL)
    Serial.println("TL:黑 ");
  else
    Serial.println("TL:白 ");
  if (IR_TR)
    Serial.println("TR:黑 ");
  else
    Serial.println("TR:白 ");
  if (E18)
    Serial.println("沒東西 ");
  else
    Serial.println("有東西 ");
}
