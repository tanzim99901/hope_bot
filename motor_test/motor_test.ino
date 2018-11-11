#define in1 47
#define in2 49
#define in3 51
#define in4 53
#define ena 11
#define enb 12

void setup() {
  Serial.begin(9600);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(ena, OUTPUT);
  pinMode(enb, OUTPUT);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, HIGH);
}

void loop() {
  wheel(255, 255);
  delay(2000);
  wheel(-255,-255);
  delay(2000);
  wheel(0,0);
  delay(2000);

}

void wheel(int lm, int rm)
{
  if (lm == 0)
  {
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
  }

  else if (lm > 0)
  {
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
  }

  else if (lm < 0)
  {
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
  }



  if (rm == 0)
  {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
  }

  else if (rm > 0)
  {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
  }

  else if (rm < 0)
  {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
  }

  if (lm > 254) lm = 254;
  if (lm < -254) lm = -254;
  if (rm > 254) rm = 254;
  if (rm < -254) rm = -254;

  analogWrite(ena, abs(rm));
  analogWrite(enb, abs(lm));

}

