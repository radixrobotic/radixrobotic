#define LED 11
int PB=2;
int PA=A5;
bool Tombol;
int TA;

void setup() {
  pinMode(LED,OUTPUT);
  pinMode(PB,INPUT_PULLUP);
  pinMode(PA,INPUT);

  digitalWrite(LED,LOW);
  
  // put your setup code here, to run once:

}

void loop() {
  Tombol=digitalRead(PB);
  TA=analogRead(PA);
  analogWrite(LED,TA/4);
  
/*  if(Tombol==0)
  {
    digitalWrite(LED,HIGH);
  }
  else
  {
    digitalWrite(LED,LOW);
  }*/
  // put your main code here, to run repeatedly:

}
