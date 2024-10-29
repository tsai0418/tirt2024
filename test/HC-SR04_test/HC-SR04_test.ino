  #include <NewPing.h> //HC-SR04函式庫

#define MAX_DISTANCE 100 //設定超聲波最大偵測範圍

#define TRIGGER_PIN_L  35
#define ECHO_PIN_L     37
#define TRIGGER_PIN_R  39
#define ECHO_PIN_R     41
NewPing sonar_L(TRIGGER_PIN_L, ECHO_PIN_L, MAX_DISTANCE); //左邊超聲波
NewPing sonar_R(TRIGGER_PIN_R, ECHO_PIN_R, MAX_DISTANCE); //右邊超聲波

//#define Lcm sonar_L.convert_cm(us_L)
#define Lcm sonar_L.ping_cm()
#define Rcm sonar_R.ping_cm()

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  //unsigned int us_L = sonar_L.ping_median();
  

  Serial.print("L:");
  Serial.print(Lcm);
  Serial.println("cm  ");
  
  Serial.print("R:");
  Serial.print(Rcm);
  Serial.println("cm  ");

  delay(!000);
  

  /*if (Rcm < 40 && Rcm != 0)
    Serial.print("近 ");
  else if (Rcm > 40)
    Serial.print("中 ");
  else if (Rcm == 0)
    Serial.print("遠 ");

  if (Lcm < 40 && Lcm != 0)
    Serial.print("近 ");
  else if (Lcm > 40)
    Serial.print("中 ");
  else if (Lcm == 0)
    Serial.print("遠 ");

  if (Rcm < 40 && Rcm != 0 && Lcm < 40 && Lcm != 0)
    Serial.println("衝撞");
  else if (Rcm > 40 && Lcm > 40)
    Serial.println("直走");
  else if (Rcm > 40 && Lcm == 0)
    Serial.println("右修");
  else if (Rcm == 0 && Lcm > 40)
    Serial.println("左修");
  else if (Rcm < 40 && Rcm != 0 && Lcm == 0)
    Serial.println("右旋轉");
  else
    Serial.println("左旋轉");*/
}
