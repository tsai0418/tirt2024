int L[] = {36,34,6}; //motor1 (in1A,in1B,pwm1)
int R[] = {38,40,6}; //motor2 (in2A,in2B,pwm2)

int i;

void setup() {
  Serial.begin(9600);

  //第一個馬達
  pinMode(L[0], OUTPUT);
  pinMode(L[1], OUTPUT);

  //第二個馬達
  pinMode(R[0], OUTPUT);
  pinMode(R[1], OUTPUT);

  digitalWrite(L[0], LOW);
  digitalWrite(L[1], LOW);
  digitalWrite(R[0], LOW);
  digitalWrite(R[1], LOW);

  back();
  
}

void loop() 
{ 
//    i=0;
//  do{
//    digitalWrite(L[0], HIGH);
//    digitalWrite(L[1], LOW);
//    digitalWrite(R[0], HIGH);
//    digitalWrite(R[1], LOW);
// 
//    analogWrite(L[2],i+=1);
//    analogWrite(R[2],i+=1);
//
//    Serial.println(i);
//    
//    delay(10);
//  }while(i==255);
//  
//  Serial.print("Max:");
//  Serial.println(i);
}

void ff()//前進
{
  digitalWrite(L[0], HIGH);
  digitalWrite(L[1], LOW);
  digitalWrite(R[0], HIGH);
  digitalWrite(R[1], LOW);

  analogWrite(L[2],50);
  analogWrite(R[2],50);
}

void back()//後退
{
  digitalWrite(L[1], HIGH);
  digitalWrite(L[0], LOW);
  digitalWrite(R[1], HIGH);
  digitalWrite(R[0], LOW);

  analogWrite(L[2],250);
  analogWrite(R[2],250);
}

void stopp()//停止
{ 
  digitalWrite(L[0], LOW);
  digitalWrite(L[1], LOW);
  digitalWrite(R[0], LOW);
  digitalWrite(R[1], LOW);
}

//void right()//右移
//{
//  digitalWrite(L[0], HIGH);
//  digitalWrite(L[1], LOW);
//  digitalWrite(R[1], HIGH);
//  digitalWrite(R[0], LOW);
//
//  analogWrite(L[2],51);
//  analogWrite(R[2],51);
//
//}
//
//void right_max()//右移最大速度
//{
//  digitalWrite(L[1], HIGH);
//  digitalWrite(L[2], LOW);
//  digitalWrite(R[2], HIGH);
//  digitalWrite(R[1], LOW);
//  
//  analogWrite(R[0],240);
//  analogWrite(L[0],240);
//}
//
//void left_max()//左移最大速度
//{
//  digitalWrite(L[2], HIGH);
//  digitalWrite(L[1], LOW);
//  digitalWrite(R[1], HIGH);
//  digitalWrite(R[2], LOW);
//  
//  analogWrite(R[0],240);
//  analogWrite(L[0],240);
//}

void aaa()//慢慢加速
{
  int i;
  for(i=0;i<256;i++){
    digitalWrite(L[0], HIGH);
    digitalWrite(L[1], LOW);
    digitalWrite(R[0], HIGH);
    digitalWrite(R[1], LOW);
 
    analogWrite(L[2],i);
    analogWrite(R[2],i);
    
    delay(3);
    Serial.println(i);
  }
  if(i>=255){
    i=255;
  }
  Serial.print(i);
}

void bbb()//慢慢減速
{
  for(int i=255;i>=0;i--){
    digitalWrite(L[0], HIGH);
    digitalWrite(L[1], LOW);
    digitalWrite(R[0], HIGH);
    digitalWrite(R[1], LOW);

    analogWrite(L[2],i);
    analogWrite(R[2],i);

    delay(10);
  }
}

//void right_front()//右前
//{
//  digitalWrite(R[1], HIGH);
//  digitalWrite(R[2], LOW);
//  digitalWrite(L[1], HIGH);
//  digitalWrite(L[2], LOW);
//
//  for(int i=50;i<=255;i++){
//    analogWrite(L[0],i);
//    analogWrite(R[0],i);
//    
//    delay(10);
//  }
//
//  for(int i=255;i>=0;i--){
//    analogWrite(L[0],i);
//    analogWrite(R[0],i);
//    
//    delay(10);
//  }
  
//}
