int sw1 = 23;//o > mode1
int sw2 = 25;//x > mode2
int sw3 = 27;
int sw4 = 29;

int mode = 0;

void setup(){
  Serial.begin(9600);

  pinMode(sw1, INPUT);
  pinMode(sw2, INPUT);
  pinMode(sw3, INPUT);
  pinMode(sw4, INPUT);
}

void loop(){

  delay(500);

//  Serial.print("sw1=");
//  Serial.println(digitalRead(sw1));
//  Serial.print("sw2=");
//  Serial.println(digitalRead(sw2));
  select();

  switch(mode)
  {
     case 1:
//             Serial.print("sw1=");
//             Serial.println(digitalRead(sw1));
             Serial.println(" mode1 ");
             break; 
     case 2:
//             Serial.print("sw2=");
//             Serial.println(digitalRead(sw2));
             Serial.println(" mode2 ");
             break;         
     case 3:;
             Serial.println(" mode3 ");
             break; 
     case 4:
             Serial.println(" mode4 ");
             break; 
     default:
             Serial.println(" x ");    
             break;              
  } 
}

void select()
{
  if(digitalRead(sw1) == LOW)//sw1
  {
    delay(20);
    if(digitalRead(sw1) == LOW){
      mode = 1;
      delay(100);                                                                                                                                                                              
    }
  }
  else if(digitalRead(sw2) == LOW)//sw2
  {
    delay(20);
    if(digitalRead(sw2) == LOW){
      mode = 2;
      delay(2000);
    }
  }
  else if(digitalRead(sw3) == LOW)//sw3
  {
    delay(20);
    if (digitalRead(sw3) == LOW){
      mode = 3;
      delay(1400);
    }
  }
  else if(digitalRead(sw4) == LOW)//sw4
  {
    delay(20);
    if (digitalRead(sw4) == LOW){
      mode = 4;
    }
  }
}
