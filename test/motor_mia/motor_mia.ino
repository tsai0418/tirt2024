int LB[] = {3, 35, 37}; //(p,a,b)
int RB[] = {2, 39, 41};
int LF[] = {5, 49, 47};
int RF[] = {4, 45, 43};

void setup() {
  Serial.begin(9600);

  for (int i = 1; i <= 2; i++) { //馬達
    pinMode(LF[i], OUTPUT);
    pinMode(RF[i], OUTPUT);
    pinMode(LB[i], OUTPUT);
    pinMode(RB[i], OUTPUT);
    digitalWrite(LF[i], LOW);
    digitalWrite(RF[i], LOW);
    digitalWrite(LB[i], LOW);
    digitalWrite(RB[i], LOW);
  }
}

void loop() {

  digitalWrite(RF[1], HIGH);
  digitalWrite(RF[2], LOW);
  digitalWrite(LF[1], HIGH);
  digitalWrite(LF[2], LOW);
  digitalWrite(RB[1], HIGH);
  digitalWrite(RB[2], LOW);
  digitalWrite(LB[1], HIGH);
  digitalWrite(LB[2], LOW);

  analogWrite(LF[0], 0);
  analogWrite(RF[0], 100);
  analogWrite(LB[0], 0);
  analogWrite(RB[0], 0);
}
