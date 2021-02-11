#include <LiquidCrystal.h>
#include <Wire.h>
#include <LIDARLite.h>
LiquidCrystal lcd(37,36,35,34,33,32);
const int LeftPWM = 9;
const int LeftDir = 7;
const int RightPWM = 10;
const int RightDir = 8;
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
int distancecm;
int distancein;
LIDARLite lidarLite;

void setup() {
Serial.begin(9600);
lcd.begin(20,4);         //set 16 columns and 2 rows of 16x2 LCD
  lidarLite.begin(0, true);   //set config to default and I2C to 400kHz, starts I2C
  lidarLite.configure(0);     //there are 6 different configs available, 0 is default
  Wire.begin();
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
void loop() {
  String bear;
  ReadCompass();
  //assign bearing
  if(bearing >= 22 && bearing < 67) bear = "NE";
  else if(bearing >= 67 && bearing < 112) bear = "E";
  else if(bearing >= 112 && bearing < 157) bear = "SE";
  else if(bearing >= 157 && bearing < 202) bear = "S";
  else if(bearing >= 202 && bearing < 247) bear = "SW";
  else if(bearing >= 247 && bearing < 292) bear = "W";
  else if(bearing >= 292 && bearing < 337) bear = "NW";
  else bear = "N";
 
       
  
  distancecm = lidarLite.distance(false);    //without bias correction, faster distance measurements performed
  distancein = distancecm*0.3937;           //1cm = 0.3937in
   lcd.clear();
  lcd.print("Distance: ");
  lcd.print(distancecm);
  lcd.print("cm");
  lcd.setCursor(10,1);
  lcd.print(distancein);
  lcd.print("in");
  lcd.setCursor(0,2);
  lcd.print("Direction: ");
  lcd.print(bear);   lcd.print(bearing); 
  delay(1000); 
if (distancecm > 25){
analogWrite(RightPWM, 255/6);
analogWrite(RightDir,-1);
analogWrite(LeftPWM, 255/6);
analogWrite(LeftDir,-1);   
  lcd.setCursor(1,2);  
lcd.print("Motor status: RUN FW");   
}  
else if (distancecm < 24){
  int g = bearing - 135;
    ReadCompass();
  lcd.clear();
  lcd.println(g);
  Serial.println(g); 
  lcd.println(bearing);
  Serial.println(bearing);
while (bearing > g){
  ReadCompass(); 
          lcd.clear();
  lcd.println(bearing);
  Serial.println(bearing);
analogWrite(RightPWM, 255/4);
analogWrite(RightDir,1);
analogWrite(LeftPWM, 255/4);
analogWrite(LeftDir,-1);
  }
  analogWrite(RightPWM, 255/255);
analogWrite(RightDir,1);
analogWrite(LeftPWM, 255/255);
analogWrite(LeftDir,-1);     
  lcd.setCursor(1,1);
  lcd.print("Motor status: OFF");
  if (distancecm > 20){
analogWrite(RightPWM, 255/6);
analogWrite(RightDir,-1);
analogWrite(LeftPWM, 255/6);
analogWrite(LeftDir,-1);   
  lcd.setCursor(1,2);  
lcd.print("Motor status: RUN FW");   
}
else if (distancecm < 19){
  int g = bearing - 135;
    ReadCompass();
  lcd.clear();
  lcd.println(g);
  Serial.println(g); 
  lcd.println(bearing);
  Serial.println(bearing);
while (bearing > g){
  ReadCompass(); 
          lcd.clear();
  lcd.println(bearing);
  Serial.println(bearing);
analogWrite(RightPWM, 255/4);
analogWrite(RightDir,1);
analogWrite(LeftPWM, 255/4);
analogWrite(LeftDir,-1);
  }
  analogWrite(RightPWM, 255/255);
analogWrite(RightDir,-1);
analogWrite(LeftPWM, 255/255);
analogWrite(LeftDir,-1); delay(5000);    
  lcd.setCursor(1,1);
  lcd.print("Motor status: OFF");
}}}
