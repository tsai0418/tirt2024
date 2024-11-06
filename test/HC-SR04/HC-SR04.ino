int trigPin_L = 39;    
int echoPin_L = 41;    
int trigPin_R = 43;    
int echoPin_R = 45; 

long duration_L, Lcm, duration_R, Rcm ;  //宣告計算距離時，需要用到的兩個實數
 
void setup() {
  Serial.begin (9600);           //設定序列埠監控視窗 (Serial Monitor) 和 Arduino資料傳輸速率為 9600 bps (Bits Per Second)
  pinMode(trigPin_L, OUTPUT);      //Arduino 對外啟動距離感測器Trig腳，射出超音波 
  pinMode(echoPin_L, INPUT);       //超音波被障礙物反射後，Arduino讀取感測器Echo腳的時間差
  pinMode(trigPin_R, OUTPUT);       
  pinMode(echoPin_R, INPUT);   
}
 
void loop()
{                        
  delay(300);
  //程式計算出距離值 cm
  digitalWrite(trigPin_L, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin_L, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_L, LOW);
  pinMode(echoPin_L, INPUT);
  duration_L = pulseIn(echoPin_L, HIGH);
  Lcm = (duration_L/2) / 29.1; 
  
  Serial.print("Lcm ");     //印出距離值 cm 在序列埠監控顯示器 單位公分
  Serial.println(Lcm);

  digitalWrite(trigPin_R, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin_R, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_R, LOW);
  pinMode(echoPin_R, INPUT);
  duration_R = pulseIn(echoPin_R, HIGH);
  Rcm = (duration_R/2) / 29.1; 
  
  Serial.print("Rcm ");     //印出距離值 cm 在序列埠監控顯示器 單位公分
  Serial.println(Rcm);
}
