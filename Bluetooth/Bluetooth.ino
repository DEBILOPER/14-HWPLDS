void setup() {
  Serial.begin(9600);
  pinMode(8,OUTPUT);
}

void loop() {
  if(Serial.available()>0)
  {
    char data = Serial.read();
    if (data == 'a')
    {
      digitalWrite(8,HIGH);
    }
    else if(data == 'b')
    {
      digitalWrite(8,LOW);
    }
  }
}
