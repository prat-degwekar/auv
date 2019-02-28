int flag = 0;
void loop() {
  //Program loops over and over in 9 second duration
  if (flag == 0)
  { flag = 2;
    for (int i = 1; i < 50; i++)
    {
      digitalWrite(6, HIGH);
      delayMicroseconds(1500);
      digitalWrite(6, LOW);
      delayMicroseconds(2500);
    }
  }

  digitalWrite(6,HIGH);
  delayMicroseconds(2000);
  digitalWrite(6,LOW);
  delayMicroseconds(2000);

}
