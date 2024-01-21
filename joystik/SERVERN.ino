#include <SoftwareSerial.h>
#include <Servo.h>

#include <PS2X_lib.h>  //for v1.6

PS2X ps2x; // create PS2 Controller Class

//right now, the library does NOT support hot pluggable controllers, meaning
//you must always either restart your Arduino after you conect the controller,
//or call config_gamepad(pins) againafter connecting the controller.
const int pwmka11 =  9;
const int pwmka12 =  8;

const int mtr1 =  7;
const int mtr2 =  6;

const int pwmka13 =  5;
const int pwmka14 =  4;


const int mtr3 =  22;
const int mtr4 = 23;

const int x = 24; //srepet
const int segitiga = 26;///keatas
const int bundar = 27;
const int kotak = 25;//jepit


int pwm;
int pwm1;
int nilai;
/////////////// PWM
int error = 0;
byte type = 0;
byte vibrate = 0;
int LY, LX, RY, RX, LYold, LXold, RYold, RXold;
#include "MotorANol.h"
void setup(){
  Serial.begin(115200);
        pinMode(pwmka11, OUTPUT);
        pinMode(mtr1, OUTPUT);
        pinMode(pwmka12, OUTPUT);
        pinMode(mtr2, OUTPUT);
        pinMode(pwmka13, OUTPUT);
        pinMode(mtr3, OUTPUT);
        pinMode(pwmka14, OUTPUT);
        pinMode(mtr4, OUTPUT);
        //////////
        pinMode(x, OUTPUT);
        pinMode(segitiga, OUTPUT);
        pinMode(bundar, OUTPUT);
        pinMode(kotak, OUTPUT);        
  MotorANol.init(); //inisialisasi Motor A0
  //CHANGES for v1.6 HERE!!! **************PAY ATTENTION*************
  delay(50);
  error = ps2x.config_gamepad(13,11,10,12, false, false);   //setup pins and settings:  GamePad(clock, command, attention, data, Pressures?, Rumble?) check for error
  if(error == 0){
    Serial.println("Found Controller, configured successful");
  }
  else if(error == 1)
    Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");

  else if(error == 2)
    Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");

  else if(error == 3)
    Serial.println("Controller refusing to enter Pressures mode, may not support it. ");

  //Serial.print(ps2x.Analog(1), HEX);

  type = ps2x.readType();
  switch(type) {
  case 0:
    Serial.println("Unknown Controller type");
    break;
  case 1:
    Serial.println("DualShock Controller Found");
    break;
  case 2:
    Serial.println("GuitarHero Controller Found");
    break;
  }
}

void loop()
{
//MotorANol.proses2(); //melakukan proses pada motor A0
MotorANol.proses2(); //melakukan proses pada motor A0
  ps2x.read_gamepad(false, vibrate);          //read controller and set large motor to spin at 'vibrate' speed
  if(ps2x.ButtonPressed(PSB_PAD_UP))             //will be TRUE if button was JUST pressed
    Serial.println("PAD_UP just pressed");
  if(ps2x.ButtonReleased(PSB_PAD_UP))             //will be TRUE if button was JUST pressed
    Serial.println("PAD_UP just released");

  if(ps2x.ButtonPressed(PSB_PAD_DOWN))             //will be TRUE if button was JUST pressed
    Serial.println("PAD_DOWN just pressed");
  if(ps2x.ButtonReleased(PSB_PAD_DOWN))             //will be TRUE if button was JUST pressed
    Serial.println("PAD_DOWN just released");

if(ps2x.ButtonPressed(PSB_PAD_LEFT))
  {             //will be TRUE if button was JUST pressed
   Serial.println("PAD_LEFT just pressed");
   Serial.println("menekan tombol untuk w");
  MotorANol.setGerak(true);
  MotorANol.setArahPositif(true);
  MotorANol.setArahNegatif(false);
  }
else if(ps2x.ButtonReleased(PSB_PAD_LEFT)){
  MotorANol.setGerak(true);
    MotorANol.setArahPositif(true);
    MotorANol.setArahNegatif(false);
  }
else if(ps2x.ButtonPressed(PSB_PAD_RIGHT))
{  //will be TRUE if button was JUST pressed
  MotorANol.setGerak(true);
  MotorANol.setArahPositif(false);
  MotorANol.setArahNegatif(true);
 Serial.println("PAD_RIGHT just pressed");
delay(100);
}
else if(ps2x.ButtonReleased(PSB_PAD_RIGHT)) {            //will be TRUE if button was JUST pressed
    Serial.println("PAD_RIGHT just released");
    MotorANol.setGerak(true);
    MotorANol.setArahPositif(false);
    MotorANol.setArahNegatif(true);
//
}
  if(ps2x.ButtonPressed(PSB_START))             //will be TRUE if button was JUST pressed
    Serial.println("START just pressed");
  if(ps2x.ButtonReleased(PSB_START))             //will be TRUE if button was JUST pressed
    Serial.println("START just released");

  if(ps2x.ButtonPressed(PSB_SELECT))             //will be TRUE if button was JUST pressed
    Serial.println("SELECT just pressed");
  if(ps2x.ButtonReleased(PSB_SELECT))             //will be TRUE if button was JUST pressed
    Serial.println("SELECT just released");

  if(ps2x.ButtonPressed(PSB_TRIANGLE)) {            //will be TRUE if button was JUST pressed
//    Serial.println("wajek just pressed");
//    digitalWrite(segitiga, HIGH); 
//    delay(50);
  }
  if(ps2x.ButtonReleased(PSB_TRIANGLE)) {            //will be TRUE if button was JUST pressed
//    Serial.println("wajek just released");
//  digitalWrite(segitiga, LOW); 
//  delay(50);
  }
  if(ps2x.ButtonPressed(PSB_SQUARE)){             //will be TRUE if button was JUST pressed
    digitalWrite(kotak, LOW);
    digitalWrite(x, HIGH);
    delay(150);
  }
if(ps2x.ButtonReleased(PSB_SQUARE)) {            //will be TRUE if button was JUST released
digitalWrite(kotak, HIGH);
delay (150);
digitalWrite(kotak, LOW);
digitalWrite(x, LOW);
delay(150);
}
  if(ps2x.ButtonPressed(PSB_CIRCLE)){             //will be TRUE if button was JUST pressed
  Serial.println("wajek just pressed");
  digitalWrite(segitiga, HIGH); //////mungah
  delay(500);
  Serial.println("kotak just released");///njepit     
  digitalWrite(kotak, HIGH);
  delay (500);
  Serial.println("wajek just pressed");
  digitalWrite(segitiga, LOW); //////mudun
  delay(500);
    MotorANol.setGerak(true);
    MotorANol.setArahPositif(true);
    MotorANol.setArahNegatif(false);
}

if(RX != RXold || RY != RYold)
  {  
  if (RX <= 127 && RY==128) // LY DARI 0 SAMPAI KE 127 UNTUK ATALOG TENGAH KE KE ATAS
  {
    MotorANol.setGerak(true);
    MotorANol.setArahPositif(true);
    MotorANol.setArahNegatif(false);
    Serial.print("KIRI "); //jika ` tepenuhi maka serial monitor maju
  }
else if(RX>=129 && RX<=255 && RY==128)/// analog tengah mundur
  {
    MotorANol.setGerak(true);
    MotorANol.setArahPositif(false);
    MotorANol.setArahNegatif(true);
    Serial.print(" KANAN "); 
}
   
}
//  if(ps2x.ButtonReleased(PSB_CIRCLE)){             //will be TRUE if button was JUST pressed
//    Serial.println("wajek just pressed");
//    digitalWrite(segitiga, LOW); 
//    delay();
//    Serial.println("kotak just released");     
//    digitalWrite(kotak, HIGH);
//  
//}
  if(ps2x.ButtonPressed(PSB_SQUARE)){ 

  
  Serial.println("X tekan");
    digitalWrite(x, LOW);
    delay (75);
Serial.println("kotak just released");     
    digitalWrite(kotak,HIGH);         

}
  if(ps2x.ButtonReleased(PSB_SQUARE)) {            //will be TRUE if button was JUST released
  Serial.println("X tekan");
    digitalWrite(x, LOW);
     delay(50);
  }
  if(ps2x.ButtonPressed(PSB_CROSS)) {            //will be TRUE if button was JUST pressed
//    Serial.println("X tekan");
//    digitalWrite(x, HIGH);
//     delay(50);
//     
  }
  if(ps2x.ButtonReleased(PSB_CROSS)) {            //will be TRUE if button was JUST released
//    Serial.println("X lepas");     
//    digitalWrite(x, LOW);
//     delay(50);
  }
  
  if(ps2x.ButtonPressed(PSB_L1)){             //will be TRUE if button was JUST pressed
  
}
  if(ps2x.ButtonReleased(PSB_L1)){             //will be TRUE if button was JUST released
   Serial.println("menekan tombol untuk s");
 
    Serial.println("L1 just released");    
  }
//  if(ps2x.ButtonPressed(PSB_R1)){             //will be TRUE if button was JUST pressed
//  }
//    Serial.println("R1 just pressed");
//  if(ps2x.ButtonReleased(PSB_R1))             //will be TRUE if button was JUST released
// {
//    Serial.println("R1 just released");
//
//}
  if(ps2x.ButtonPressed(PSB_L2))  {           //will be TRUE if button was JUST pressed
    Serial.println("L2 just pressed");
   digitalWrite(mtr1, LOW); //menunis pesan ke pin digital maju
   analogWrite(pwmka11, 255); //menulis nilai pwm ke driver untuk kecepatan
    digitalWrite(mtr2, HIGH); //menunis pesan ke pin digital maju
    analogWrite(pwmka12, 255); //menulis nilai pwm ke driver untuk kecepatan
   digitalWrite(mtr3, HIGH); //menunis pesan ke pin digital maju
    analogWrite(pwmka13, 255); //menulis nilai pwm ke driver untuk kecepatan
    digitalWrite(mtr4, HIGH); //menunis pesan ke pin digital maju
   analogWrite(pwmka14, 255); //menulis nilai pwm ke driver untuk kecepatan
 Serial.println(pwm); // pwm woutput ke srial monitor 
delay(50);
  }
  if(ps2x.ButtonReleased(PSB_L2)){             //will be TRUE if button was JUST released
   
  analogWrite(pwmka12,0);  
    analogWrite(pwmka11,0);  
    analogWrite(pwmka13,0);  
    analogWrite(pwmka14,0);  
    delay(50); 

  }
  if(ps2x.ButtonPressed(PSB_R2))  
{  //will be TRUE if button was JUST pressed
    Serial.println("L2 just released");   
     digitalWrite(mtr1, HIGH); //menunis pesan ke pin digital maju
   analogWrite(pwmka11, 255); //menulis nilai pwm ke driver untuk kecepatan
 
    digitalWrite(mtr2, LOW); //menunis pesan ke pin digital maju
    analogWrite(pwmka12, 255); //menulis nilai pwm ke driver untuk kecepatan
 
   digitalWrite(mtr3, LOW); //menunis pesan ke pin digital maju
    analogWrite(pwmka13, 255); //menulis nilai pwm ke driver untuk kecepatan
  
   digitalWrite(mtr4, LOW); //menunis pesan ke pin digital maju
   analogWrite(pwmka14, 255); //menulis nilai pwm ke driver untuk kecepatan
   Serial.println(pwm); // pwm woutput ke srial monitor 
  delay(50);
  
    Serial.println("R2 just pressed");
}
  if(ps2x.ButtonReleased(PSB_R2))             //will be TRUE if button was JUST released
 {
    Serial.println("R2 just released");
    analogWrite(pwmka12,0);  
    analogWrite(pwmka11,0);  
    analogWrite(pwmka13,0);  
    analogWrite(pwmka14,0);  
 
 }

  LY = (int) ps2x.Analog(PSS_LY);
  LX = (int) ps2x.Analog(PSS_LX);
  RY = (int) ps2x.Analog(PSS_RY);
  RX = (int) ps2x.Analog(PSS_RX);
 
if(LY != LYold || LX != LXold)
  { 
if (LY <= 127 && LX==128) // LY DARI 0 SAMPAI KE 127 UNTUK ATALOG TENGAH KE KE ATAS
  {
   Serial.print("MAJU "); //jika ` tepenuhi maka serial monitor maju
  //Serial.println(LY);
  if(LY==0) ///jika LY 0 MAKA PWM =255
   {
    pwm=255;
   }
  if(LY>=1 && LY<=127) //jika ly 1 sampai 127 maka pwm dari 254 sampai 1
    {
    pwm= ((127-LY)+1)*2;      
  }
  if(pwm<=15) //jika pwm kurang dari sama dengan 4 maka pwm di nol kan
   {
    pwm=0;
   }
  
  digitalWrite(mtr1, LOW); //menunis pesan ke pin digital maju
  analogWrite(pwmka11, pwm); //menulis nilai pwm ke driver untuk kecepatan
 
digitalWrite(mtr2, LOW); //menunis pesan ke pin digital maju
analogWrite(pwmka12, pwm); //menulis nilai pwm ke driver untuk kecepatan
// 
digitalWrite(mtr3, HIGH); //menunis pesan ke pin digital maju
 analogWrite(pwmka13, pwm); //menulis nilai pwm ke driver untuk kecepatan
//  
digitalWrite(mtr4, LOW); //menunis pesan ke pin digital maju
analogWrite(pwmka14, pwm); //menulis nilai pwm ke driver untuk kecepatan
 
 Serial.println(pwm); // pwm woutput ke srial monitor 

}
if(LY>=129 && LY<=255 && LX==128)/// analog tengah mundur
  {
    Serial.print("L MUNDUR "); 
  if(LY==255) ///jika ly sama dengan 255 maka pwm 255
   {
    pwm=255; 
   }
  if(LY>=1 && LY<=254) ///jika data lebih dari satu sampai 254 maka dikonversi
    {
  pwm=((LY-129)+1)*2;    //rumus
  }
  //pwm=((LY-129)+1)*2;
  if(pwm > 255) //data konversi lebih dari 255 maka data 255
  {
   pwm = 255; 
  }
  if(pwm<=15) //data konversi kurang dari sma dengan 4 aka pwm sama dengan 4
   {
    pwm=0;
   }
  digitalWrite(mtr2, HIGH);
  analogWrite(pwmka12,pwm);
  
  digitalWrite(mtr1, HIGH);
  analogWrite(pwmka11,pwm);
  
  digitalWrite(mtr3, LOW);
  analogWrite(pwmka13,pwm);
  
  digitalWrite(mtr4, HIGH);
  analogWrite(pwmka14,pwm);
  
  Serial.println(pwm);
}
if(LY==128 && LX==128)
  {
  Serial.println("L STOP ");
  //Serial.println(255);
  //digitalWrite(mtr, LOW);
  analogWrite(pwmka12,0);  
  analogWrite(pwmka11,0);  
  analogWrite(pwmka13,0);  
  analogWrite(pwmka14,0);  
}
///// DATA LX 
if (LX <= 127 && LY==128) // LY DARI 0 SAMPAI KE 127 UNTUK ATALOG TENGAH KE KE ATAS
  {
   Serial.print("KIRI "); //jika ` tepenuhi maka serial monitor maju
  //Serial.println(LY);
  if(LX==0) ///jika LY 0 MAKA PWM =255
   {
    pwm=255;
   }
  if(LX>=1 && LX<=127) //jika ly 1 sampai 127 maka pwm dari 254 sampai 1
    {
    pwm= ((127-LX)+1)*2;      
  }
  if(pwm<=10) //jika pwm kurang dari sama dengan 4 maka pwm di nol kan
   {
    pwm=0;
   } 
   nilai=pwm+30;
digitalWrite(mtr1, LOW); //menunis pesan ke pin digital maju
 analogWrite(pwmka11, pwm); //menulis nilai pwm ke driver untuk kecepatan
 
  digitalWrite(mtr2, HIGH); //menunis pesan ke pin digital maju
  analogWrite(pwmka12, pwm); //menulis nilai pwm ke driver untuk kecepatan
 
 
 digitalWrite(mtr3, LOW); //menunis pesan ke pin digital maju
  analogWrite(pwmka13, pwm); //menulis nilai pwm ke driver untuk kecepatan
  
 digitalWrite(mtr4, LOW); //menunis pesan ke pin digital maju
 analogWrite(pwmka14, pwm); //menulis nilai pwm ke driver untuk kecepatan
 Serial.println(pwm); // pwm woutput ke srial monitor 
//  //Serial.println("--");
}
if(LX>=129 && LX<=255 && LY==128)/// analog tengah mundur
  {
    Serial.print("L KANAN "); 
  //Serial.print(LY);
  //Serial.print(" ");
  if(LX==255) ///jika ly sama dengan 255 maka pwm 255
   {
    pwm=255;
   }
  if(LX>=1 && LX<=254) ///jika data lebih dari satu sampai 254 maka dikonversi
    {
  pwm=((LX-129)+1)*2;    //rumus
  }
  //pwm=((LY-129)+1)*2;
  if(pwm > 255) //data konversi lebih dari 255 maka data 255
  {
   pwm = 255; 
  }
  if(pwm<=10) //data konversi kurang dari sma dengan 4 aka pwm sama dengan 4
   {
    pwm=0;
   }
   nilai=pwm+30;
  digitalWrite(mtr2, LOW);
  analogWrite(pwmka12,pwm);
  
  digitalWrite(mtr1, HIGH);
  analogWrite(pwmka11,pwm);
  
  digitalWrite(mtr3, HIGH);
  analogWrite(pwmka13,pwm);
  
  digitalWrite(mtr4, HIGH);
  analogWrite(pwmka14,pwm);
  
  Serial.println(pwm);
}
//////////////////////////////////////////////////////////PUTAR KIRI

//////
//////////////////////////////////////////////////////////PUTAR KIRI 1
if (LY <= 127 && LX<=127) // LY DARI 0 SAMPAI KE 127 UNTUK ATALOG TENGAH KE KE ATAS
  {
   Serial.print("MAJU-kiri "); //jika ` tepenuhi maka serial monitor maju
  //Serial.println(LY);
  if(LY==0) ///jika LY 0 MAKA PWM =255
  {
  pwm=255;
   }
   if(LX==0) ///jika LY 0 MAKA PWM =255
   {
   pwm1=255;
   }
  if(pwm<=5 ) //jika pwm kurang dari sama dengan 4 maka pwm di nol kan
   {
    pwm=0;
   }
  
  if(pwm1<=5 ) //jika pwm kurang dari sama dengan 4 maka pwm di nol kan
   {
    pwm1=0;
   }
  
  
  digitalWrite(mtr1, LOW); //menunis pesan ke pin digital maju
  analogWrite(pwmka11, 0); //menulis nilai pwm ke driver untuk kecepatan
 
  digitalWrite(mtr2, LOW); //menunis pesan ke pin digital maju
  analogWrite(pwmka12, 255); //menulis nilai pwm ke driver untuk kecepatan
 
 digitalWrite(mtr3, HIGH); //menunis pesan ke pin digital maju
  analogWrite(pwmka13, 255); //menulis nilai pwm ke driver untuk kecepatan
  
 digitalWrite(mtr4, LOW); //menunis pesan ke pin digital maju
  analogWrite(pwmka14, 0); //menulis nilai pwm ke driver untuk kecepatan
 Serial.println(pwm); // pwm woutput ke srial monitor 
  Serial.println(pwm1); // pwm woutput ke srial monitor 
  
}
//////

if(LX>=129 && LX<=255 && LY<=127)/// MAJU KANAN mundur 2
  {
    Serial.print("maju KANAN "); 
  if(LY==0) ///jika LY 0 MAKA PWM =255
  {
  pwm=255;
   }
   if(LX==255) ///jika LY 0 MAKA PWM =255
   {
   pwm1=255;
   }
  digitalWrite(mtr1, LOW); //menunis pesan ke pin digital maju
  analogWrite(pwmka11, 255); //menulis nilai pwm ke driver untuk kecepatan
 
  digitalWrite(mtr2, HIGH); //menunis pesan ke pin digital maju
  analogWrite(pwmka12, 0); //menulis nilai pwm ke driver untuk kecepatan
 
 digitalWrite(mtr3, HIGH); //menunis pesan ke pin digital maju
  analogWrite(pwmka13, 0); //menulis nilai pwm ke driver untuk kecepatan
  
 digitalWrite(mtr4, LOW); //menunis pesan ke pin digital maju
  analogWrite(pwmka14, 255); //menulis nilai pwm ke driver untuk kecepatan
 Serial.println(pwm); // pwm woutput ke srial monitor 
  Serial.println(pwm1); // pwm woutput ke srial monitor 
  
  //
}
/////
if(LX>=129 && LX<=255 && LY>=129 && LY<=255)/// analog tengah mundur
  {
    Serial.print("BAWAH KANAN "); 

    //digitalWrite(mtr1, LOW); //menunis pesan ke pin digital maju
  analogWrite(pwmka11, 0); //menulis nilai pwm ke driver untuk kecepatan
 
  digitalWrite(mtr2, HIGH); //menunis pesan ke pin digital maju
  analogWrite(pwmka12, 255); //menulis nilai pwm ke driver untuk kecepatan
 
// digitalWrite(mtr3, LOW); //menunis pesan ke pin digital maju
  analogWrite(pwmka13, 255); //menulis nilai pwm ke driver untuk kecepatan
  
 //digitalWrite(mtr4, LOW); //menunis pesan ke pin digital maju
  analogWrite(pwmka14, 0); //menulis nilai pwm ke driver untuk kecepatan
 Serial.println(pwm); // pwm woutput ke srial monitor 
  Serial.println(pwm1); // pwm woutput ke srial monitor  //      
}
///////
if(LY>=129 && LY<=255 && LX<=127)/// analog tengah mundur
  {

  //Serial.print(LY);
  //Serial.print(" ");
  //Serial.println(LY);
  if(LY==255) ///jika LY 0 MAKA PWM =255
  {
  pwm=255;
   }
   if(LX==255) ///jika LY 0 MAKA PWM =255
   {
   pwm1=255;
   }
 Serial.print("bawah Kiri "); 

    digitalWrite(mtr1, HIGH); //menunis pesan ke pin digital maju
  analogWrite(pwmka11, 255); //menulis nilai pwm ke driver untuk kecepatan
 
  digitalWrite(mtr2, LOW); //menunis pesan ke pin digital maju
  analogWrite(pwmka12, 0); //menulis nilai pwm ke driver untuk kecepatan
 
 digitalWrite(mtr3, LOW); //menunis pesan ke pin digital maju
  analogWrite(pwmka13, 0); //menulis nilai pwm ke driver untuk kecepatan
  
 digitalWrite(mtr4, HIGH); //menunis pesan ke pin digital maju
  analogWrite(pwmka14, 255); //menulis nilai pwm ke driver untuk kecepatan
 Serial.println(pwm); // pwm woutput ke srial monitor 
  Serial.println(pwm1); // pwm woutput ke srial monitor
    
 
}
///////
}
///////////////////////////////////
  if(RX != RXold || RY != RYold)
  {  
  if (RX <= 127 && RY==128) // LY DARI 0 SAMPAI KE 127 UNTUK ATALOG TENGAH KE KE ATAS
  {
    MotorANol.setGerak(true);
    MotorANol.setArahPositif(true);
    MotorANol.setArahNegatif(false);
    Serial.print("KIRI "); //jika ` tepenuhi maka serial monitor maju
  }
else if(RX>=129 && RX<=255 && RY==128)/// analog tengah mundur
  {
    MotorANol.setGerak(true);
    MotorANol.setArahPositif(false);
    MotorANol.setArahNegatif(true);
    Serial.print(" KANAN "); 
}
   
}
  LYold = LY;
  LXold = LX;
  RYold = RY;
  RXold = RX;
  delay(50);
}
