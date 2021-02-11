#include <Arduino.h>
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
int xPosition = 0;
int yPosition = 0;
int i = 0;int l=0;
int Contrast=10;
int buttonPin = 19;
int buttonState = 0;
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
  
  #include <ESP8266WiFi.h>
  #include <ESPAsyncTCP.h>

#include <ESPAsyncWebServer.h>

AsyncWebServer server(80);
    String inputMessage;
    String inputParam;
// REPLACE WITH YOUR NETWORK CREDENTIALS
const char* ssid = "SW";
const char* password = "12344566";

const char* PARAM_INPUT_1 = "input1";
const char* PARAM_INPUT_2 = "input2";

// HTML web page to handle 3 input fields (input1, input2, input3)
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html><head>
  <title>ESP Input Form</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  </head><body>
  <form action="/get">
    input1: <input type="text" name="distance">
    <input type="submit" value="Submit">
  </form><br>
  <form action="/get">
    input2: <input type="text" name="direction">
    <input type="submit" value="Submit">
  </form>
</body></html>)rawliteral";

void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}

void setup() {
  Serial.begin(115200);
  //attachInterrupt(digitalPinToInterrupt(2), forwRight, RISING);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("WiFi Failed!");
    return;
  }
  Serial.println();
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // Send web page with input fields to client
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html);
  });

  // Send a GET request to <ESP_IP>/get?input1=<inputMessage>
  server.on("/get", HTTP_GET, [] (AsyncWebServerRequest *request) {

    // GET input1 value on <ESP_IP>/get?input1=<inputMessage>
    if (request->hasParam(PARAM_INPUT_1)) {
      inputMessage = request->getParam(PARAM_INPUT_1)->value();
      inputParam = PARAM_INPUT_1;
    }
    // GET input2 value on <ESP_IP>/get?input2=<inputMessage>
    else if (request->hasParam(PARAM_INPUT_2)) {
      inputMessage = request->getParam(PARAM_INPUT_2)->value();
      inputParam = PARAM_INPUT_2;
    }
    else {
      inputMessage = "No message sent";
      inputParam = "none";
    }
    Serial.println(inputMessage);
    request->send(200, "text/html", "HTTP GET request sent to your ESP on input field (" 
                                     + inputParam + ") with value: " + inputMessage +
                                     "<br><a href=\"/\">Return to Home Page</a>");
  });
  
  server.onNotFound(notFound);
  server.begin();
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
    
void loop() {
  if(inputParam = PARAM_INPUT_1){
    if (inputMessage.toInt()>0){int g = distance + inputMessage.toInt();
          lcd.clear();
            lcd.println(g);
  Serial.println(g); 
  lcd.println(distance);
  Serial.println(distance);
while (distance < g){
          lcd.clear();
  lcd.println(distance);
  Serial.println(distance);
analogWrite(RightPWM, 255/4);
analogWrite(RightDir,1);
analogWrite(LeftPWM, 255/4);
analogWrite(LeftDir,1);
  }
  analogWrite(RightPWM, 255/255);
analogWrite(RightDir,1);
analogWrite(LeftPWM, 255/255);
analogWrite(LeftDir,-1);}
else if (inputMessage.toInt()<0){int g = distance - inputMessage.toInt();
          lcd.clear();
            lcd.println(g);
  Serial.println(g); 
  lcd.println(distance);
  Serial.println(distance);
while (distance < g){
          lcd.clear();
  lcd.println(distance);
  Serial.println(distance);
analogWrite(RightPWM, 255/4);
analogWrite(RightDir,-1);
analogWrite(LeftPWM, 255/4);
analogWrite(LeftDir,-1);
  }
  analogWrite(RightPWM, 255/255);
analogWrite(RightDir,1);
analogWrite(LeftPWM, 255/255);
analogWrite(LeftDir,1);}
  }
   else if(inputParam = PARAM_INPUT_2){
                                         if (inputMessage.toInt()>0){int g = bearing + inputMessage.toInt();
ReadCompass(); 
          lcd.clear();
            lcd.println(g);
  Serial.println(g); 
  lcd.println(bearing);
while (bearing < g){
  ReadCompass(); 
          lcd.clear();
  lcd.println(bearing);
analogWrite(RightPWM, 255/4);
analogWrite(RightDir,1);
analogWrite(LeftPWM, 255/4);
analogWrite(LeftDir,-1);
  }
  analogWrite(RightPWM, 255/255);
analogWrite(RightDir,1);
analogWrite(LeftPWM, 255/255);
analogWrite(LeftDir,-1);}

else if (inputMessage.toInt()<0){int g = bearing + inputMessage.toInt();
ReadCompass(); 
          lcd.clear();
            lcd.println(g);
  Serial.println(g); 
  lcd.println(bearing);
while (bearing > g){
  ReadCompass(); 
          lcd.clear();
  lcd.println(bearing);
analogWrite(RightPWM, 255/4);
analogWrite(RightDir,-1);
analogWrite(LeftPWM, 255/4);
analogWrite(LeftDir,1);
  }
  analogWrite(RightPWM, 255/255);
analogWrite(RightDir,1);
analogWrite(LeftPWM, 255/255);
analogWrite(LeftDir,-1);}}
}
