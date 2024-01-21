
int lampu=8;
void setup() {
  // put your setup code here, to run once:
pinMode(lampu, OUTPUT);
digitalWrite(lampu, LOW);    
}

void loop() {
  // put your main code here, to run repeatedly:
 digitalWrite(lampu, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(lampu, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);         
}
