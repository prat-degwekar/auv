void setup() {
  //Port initialization (Pin setup)
  pinMode(6,OUTPUT); //Pins 30,31,32,33 for ESCS
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  Serial.begin(115200);
  Serial.print("Serial begin");
  /********************************** Thruster Initialization Sequence **********************************/
  digitalWrite(6,HIGH);
  delayMicroseconds(1000);
  digitalWrite(6, LOW);
  delay(3);
  
  digitalWrite(6, HIGH);
  delayMicroseconds(1500);
  digitalWrite(6,LOW);
  delayMicroseconds(2500);
}
