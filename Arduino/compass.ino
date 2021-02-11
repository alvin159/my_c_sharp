#include <Wire.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(37,36,35,34,33,32);
  #define _i2cAddress 0x60
  #define BEARING_Register 2 
  #define COMMUNICATION_TIMEOUT 1000
  #define TIMEOUT_MICROSECONDS 1000
  #define ONE_BYTE   1
  #define TWO_BYTES  2
  #define FOUR_BYTES 4
  #define SIX_BYTES  6
  byte _byteHigh;
  byte _byteLow;
  int bearing;
  signed char pitch;
  signed char roll;
  const int LeftPWM = 9;
const int LeftDir = 7;
const int RightPWM = 10;
const int RightDir = 8;
  
void setup() {
  Serial.begin(9600);
lcd.clear();
  lcd.begin(20, 4);
  // Initialize i2c
  Wire.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
    String s1 = Serial.readStringUntil('\n');
  ReadCompass(); 
    lcd.clear();
  Serial.print("$CMP,");
  lcd.println(bearing);
  Serial.println(bearing);
         
         if (s1=="south"){
          while (bearing < 179){ReadCompass(); 
          lcd.clear();
  lcd.println(bearing);
  Serial.println(bearing);  Serial.println(s1);
analogWrite(RightPWM, 255/4);
analogWrite(RightDir,1);
analogWrite(LeftPWM, 255/4);
analogWrite(LeftDir,-1);}
while(bearing > 182){ReadCompass(); 
          lcd.clear();
  lcd.println(bearing);
  Serial.println(bearing);  Serial.println(s1);
analogWrite(RightPWM, 255/4);
analogWrite(RightDir,-1);
analogWrite(LeftPWM, 255/4);
analogWrite(LeftDir,1);}
  ReadCompass(); 
   analogWrite(RightPWM, 255/255);
analogWrite(RightDir,1);
analogWrite(LeftPWM, 255/255);
analogWrite(LeftDir,-1);
Serial.println("this is south"); }
else if (s1.toInt()>0){int g = bearing + s1.toInt();
ReadCompass(); 
          lcd.clear();
            lcd.println(g);
  Serial.println(g); 
  lcd.println(bearing);
  Serial.println(bearing);  Serial.println(s1);
while (bearing < g){
  ReadCompass(); 
          lcd.clear();
  lcd.println(bearing);
  Serial.println(bearing);  Serial.println(s1);
analogWrite(RightPWM, 255/4);
analogWrite(RightDir,1);
analogWrite(LeftPWM, 255/4);
analogWrite(LeftDir,-1);
  }
  analogWrite(RightPWM, 255/255);
analogWrite(RightDir,1);
analogWrite(LeftPWM, 255/255);
analogWrite(LeftDir,-1);}
else if (s1.toInt()<0){int g = bearing + s1.toInt();
ReadCompass(); 
          lcd.clear();
            lcd.println(g);
  Serial.println(g); 
  lcd.println(bearing);
  Serial.println(bearing);  Serial.println(s1);
while (bearing > g){
  ReadCompass(); 
          lcd.clear();
  lcd.println(bearing);
  Serial.println(bearing);  Serial.println(s1);
analogWrite(RightPWM, 255/4);
analogWrite(RightDir,-1);
analogWrite(LeftPWM, 255/4);
analogWrite(LeftDir,1);
  }
  analogWrite(RightPWM, 255/255);
analogWrite(RightDir,1);
analogWrite(LeftPWM, 255/255);
analogWrite(LeftDir,-1);}
else if (s1=="east"){
          while (bearing < 88){ReadCompass(); 
          lcd.clear();
  lcd.println(bearing);
  Serial.println(bearing);  Serial.println(s1);
analogWrite(RightPWM, 255/4);
analogWrite(RightDir,1);
analogWrite(LeftPWM, 255/4);
analogWrite(LeftDir,-1);}
while(bearing > 92){ReadCompass(); 
          lcd.clear();
  lcd.println(bearing);
  Serial.println(bearing);  Serial.println(s1);
analogWrite(RightPWM, 255/4);
analogWrite(RightDir,-1);
analogWrite(LeftPWM, 255/4);
analogWrite(LeftDir,1);}
  ReadCompass(); 
   analogWrite(RightPWM, 255/255);
analogWrite(RightDir,1);
analogWrite(LeftPWM, 255/255);
analogWrite(LeftDir,-1);
Serial.println("this is east"); }

else if (s1=="west"){
          while (bearing < 268){ReadCompass(); 
          lcd.clear();
  lcd.println(bearing);
  Serial.println(bearing);  Serial.println(s1);
analogWrite(RightPWM, 255/4);
analogWrite(RightDir,1);
analogWrite(LeftPWM, 255/4);
analogWrite(LeftDir,-1);}
while(bearing > 272){ReadCompass(); 
          lcd.clear();
  lcd.println(bearing);
  Serial.println(bearing);  Serial.println(s1);
analogWrite(RightPWM, 255/4);
analogWrite(RightDir,-1);
analogWrite(LeftPWM, 255/4);
analogWrite(LeftDir,1);}
  ReadCompass(); 
   analogWrite(RightPWM, 255/255);
analogWrite(RightDir,1);
analogWrite(LeftPWM, 255/255);
analogWrite(LeftDir,-1);
Serial.println("this is west"); }

else if (s1=="north"){
          while (bearing > 2){while(bearing < 359){ReadCompass(); 
          lcd.clear();
  lcd.println(bearing);
  Serial.println(bearing);  Serial.println(s1);
analogWrite(RightPWM, 255/4);
analogWrite(RightDir,1);
analogWrite(LeftPWM, 255/4);
analogWrite(LeftDir,-1);}
 ReadCompass(); 
 lcd.println(bearing);
  Serial.println(bearing);  Serial.println(s1);
   analogWrite(RightPWM, 255/255);
analogWrite(RightDir,1);
analogWrite(LeftPWM, 255/255);
analogWrite(LeftDir,-1);
Serial.println("this is north");
 }
}
else if (s1=="forward"){
analogWrite(RightPWM, 255/2);
analogWrite(RightDir,1);
analogWrite(LeftPWM, 255/2);
analogWrite(LeftDir,1); 
Serial.println("forward");lcd.clear();lcd.println("forward");     
}
    else if (s1=="backward"){
analogWrite(RightPWM, 255/2);
analogWrite(RightDir,-1);
analogWrite(LeftPWM, 255/2);
analogWrite(LeftDir,-1);      
Serial.println("backward"); lcd.clear();lcd.println("backward");}
  else if (s1=="left"){
analogWrite(RightPWM, 255/2);
analogWrite(RightDir,-1);
analogWrite(LeftPWM, 255/2);
analogWrite(LeftDir,1);      delay(1000);analogWrite(RightPWM, 255/255);
analogWrite(RightDir,1);
analogWrite(LeftPWM, 255/255);
analogWrite(LeftDir,1);Serial.println("left");lcd.clear();lcd.println("left");}
    else if (s1=="right"){
analogWrite(RightPWM, 255/2);
analogWrite(RightDir,1);
analogWrite(LeftPWM, 255/2);
analogWrite(LeftDir,-1);      delay(1000);analogWrite(RightPWM, 255/255);
analogWrite(RightDir,1);
analogWrite(LeftPWM, 255/255);
analogWrite(LeftDir,1);Serial.println("right");lcd.clear();lcd.println("right");}
  else if (s1=="stop"){
analogWrite(RightPWM, 255/255);
analogWrite(RightDir,1);
analogWrite(LeftPWM, 255/255);
analogWrite(LeftDir,1); Serial.println("stop");lcd.clear();lcd.println("stop");}
}
int16_t getBearing()
{
  // Setup timeout parameter
  int timeout = COMMUNICATION_TIMEOUT;

  // Begin communication with CMPS14
  Wire.beginTransmission(_i2cAddress);

  // Tell register you want some data
  Wire.write(BEARING_Register);

  // End the transmission
  int nackCatcher = Wire.endTransmission();

  // Return if we have a connection problem 
  if(nackCatcher != 0){return 0;}
  
  // Request 2 bytes from CMPS14
  Wire.requestFrom(_i2cAddress , TWO_BYTES);

  // Wait for the bytes to arrive.
  // Don't wait forever as this will hang the whole program
  while((Wire.available() < TWO_BYTES) && (timeout-- >0))
    delay(1);

  // Timed out so return
  if (timeout <= 0) return -1;

  // Read the values
  _byteHigh = Wire.read(); 
  _byteLow = Wire.read();

  // Calculate full bearing
  bearing = ((_byteHigh<<8) + _byteLow) / 10;
  
  return bearing;
}

void ReadCompass()
{
  // Setup timeout parameter
  int timeout = COMMUNICATION_TIMEOUT;

  // Begin communication with CMPS14
  Wire.beginTransmission(_i2cAddress);

  // Tell register you want some data
  Wire.write(BEARING_Register);

  // End the transmission
  int nackCatcher = Wire.endTransmission();

  // Return if we have a connection problem 
  if(nackCatcher != 0){bearing = 0; pitch = 0;  roll = 0; return;}
  
  // Request 4 bytes from CMPS14
  Wire.requestFrom(_i2cAddress , FOUR_BYTES);

  // Wait for the bytes to arrive.
  // Don't wait forever as this will hang the whole program
  while((Wire.available() < FOUR_BYTES) && (timeout-- >0))
    delay(1);

  // Timed out so return
  if (timeout <= 0) {bearing = 0; pitch = 0;  roll = 0; return;}
  
  // Read the values
  _byteHigh = Wire.read(); _byteLow = Wire.read();
  bearing = ((_byteHigh<<8) + _byteLow) / 10;

  // Read the values
  pitch = Wire.read();

  // Read the values
  roll = Wire.read();

}
