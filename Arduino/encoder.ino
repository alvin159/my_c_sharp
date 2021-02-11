#include <LiquidCrystal.h>
const float pi = 3.14;

const float R = 3.25;
const int N = 400;

float distance = 0;float distancel = 0;
const int LeftPWM = 9;
const int LeftDir = 7;
const int RightPWM = 10;
const int RightDir = 8;
const int LeftVal = 0;
const int RightVal = 0;
int xPin = A8;
int yPin = A9;
int xPosition = 0;
int yPosition = 0;
int i = 0;int l=0;
int Contrast=10;
int buttonPin = 19;
int buttonState = 0;
LiquidCrystal lcd(37,36,35,34,33,32);
void setup()
{
Serial.begin(9600);  lcd.clear();
  lcd.begin(20, 4);
pinMode(25, INPUT);
digitalWrite(25, HIGH);
pinMode(24, INPUT);
digitalWrite(24, HIGH);

attachInterrupt(digitalPinToInterrupt(2), forwRight, RISING);
attachInterrupt(digitalPinToInterrupt(3), forwLeft, RISING);

}

        void forwLeft(void())
  {
lcd.clear();lcd.println("forward");lcd.println(l++); distancel = ((2*pi*R)/N) * l ;

  lcd.setCursor(6,2);
  lcd.print( distancel);
  Serial.print(distancel);
  Serial.println("cm");
  lcd.setCursor(6,3);
  lcd.print("cm  ");
  Serial.print("left =");
  Serial.println(l);
    } 
void forwRight(void())
  {
lcd.clear();lcd.println("backward");lcd.println(i++); distance = ((2*pi*R)/N) * i ;

  lcd.setCursor(0,2);
  lcd.print( distance);

  lcd.setCursor(0,3);
  lcd.print("cm  ");  
  Serial.print("right =");
  Serial.println(i);
    }
          
    
void loop()
{
  xPosition = analogRead(xPin);

yPosition = analogRead(yPin);

buttonState = digitalRead(buttonPin);
if (yPosition > 520){
    if(xPosition > 520){
  while (distancel < 0.3 && distance < 0.3){
analogWrite(RightPWM, 255/4);
analogWrite(RightDir,1);
analogWrite(LeftPWM, 255/6);
analogWrite(LeftDir,1);}

  if (distancel > 0.5 && distance > 0.5){
 analogWrite(RightPWM, 255/255);
analogWrite(RightDir,1);
analogWrite(LeftPWM, 255/255);
analogWrite(LeftDir,1);
}}

else if(xPosition < 510){
while (distancel < 0.3 && distance < 0.3){
   
analogWrite(RightPWM, 255/6);
analogWrite(RightDir,1);
analogWrite(LeftPWM, 255/4);
analogWrite(LeftDir,1);}
if (distancel > 0.5 && distance > 0.5){
 //  distance = 0; i=0;distance == 0; i==0;
 analogWrite(RightPWM, 255/255);
analogWrite(RightDir,1);
analogWrite(LeftPWM, 255/255);
analogWrite(LeftDir,1);
}}
 else{
while (distancel < 0.03 && distance < 0.03){
   
analogWrite(RightPWM, 255/4);
analogWrite(RightDir,1);
analogWrite(LeftPWM, 255/4);
analogWrite(LeftDir,1);}
if (distancel > 0.5 && distance > 0.5){
 //  distance = 0; i=0;distance == 0; i==0;
 analogWrite(RightPWM, 255/255);
analogWrite(RightDir,1);
analogWrite(LeftPWM, 255/255);
analogWrite(LeftDir,1);}
}
}

else if (yPosition < 510){
    
    if(xPosition > 520){
while (distance < 0.3 && distancel < 0.3){
analogWrite(RightPWM, 255/4);
analogWrite(RightDir,-1);
analogWrite(LeftPWM, 255/6);
analogWrite(LeftDir,-1);}
if (distance >0.5 && distancel >0.5){
  // distance = 0; i=0;distance == 0; i==0;
  analogWrite(RightPWM, 255/255);
analogWrite(RightDir,1);
analogWrite(LeftPWM, 255/255);
analogWrite(LeftDir,1);
}
  }   
  
  else if(xPosition < 510){
  while (distance < 0.3 && distancel < 0.3){
analogWrite(RightPWM, 255/6);
analogWrite(RightDir,-1);
analogWrite(LeftPWM, 255/4);
analogWrite(LeftDir,-1);}
if (distance > 0.5 && distancel > 0.5){
  // distance = 0; i=0;distance == 0; i==0;
  analogWrite(RightPWM, 255/255);
analogWrite(RightDir,1);
analogWrite(LeftPWM, 255/255);
analogWrite(LeftDir,1);
}}
else{
while (distance < 0.03 && distancel < 0.03){
analogWrite(RightPWM, 255/4);
analogWrite(RightDir,-1);
analogWrite(LeftPWM, 255/4);
analogWrite(LeftDir,-1);}
if (distance > 0.5 && distancel > 0.5){
  // distance = 0; i=0;distance == 0; i==0;
  analogWrite(RightPWM, 255/255);
analogWrite(RightDir,1);
analogWrite(LeftPWM, 255/255);
analogWrite(LeftDir,1);
}}}

else {
  distance = 0; i=0;distance == 0; i==0;
   distancel = 0; l=0;distancel == 0; l==0;
analogWrite(RightPWM, 255/255);
analogWrite(RightDir,1);
analogWrite(LeftPWM, 255/255);
analogWrite(LeftDir,1);
delay(1000);
}

}
