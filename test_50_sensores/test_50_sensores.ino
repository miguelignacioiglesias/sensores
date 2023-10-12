#include <Wire.h>   // i2C library
#include <AHTxx.h>    // AHT10 library for relative humidity and temperature sensor. 



AHTxx aht10_0x38(AHTXX_ADDRESS_X38, AHT1x_SENSOR);
AHTxx aht10_0x39(AHT10_ADDRESS_X39, AHT1x_SENSOR);

/* Mux (HP4067) control pins. */ 
const int s0 = 7;
const int s1 = 6;
const int s2 = 5;
const int s3 = 4;

float temp;
float humidity;

/* Mux in "Enable pin". High means Disable */ 


const int MUXA = 9;
const int MUXB = 10;

// 74
const int BUFFER = 11;
//Mux in "SIG" to Atmega328p SDA pin.
const int SIG_pin = A4;  // SDA pin.

void setup() {
  
  Serial.begin(9600);
  Wire.setClock(10000);// clock speed I2C
  Wire.begin();
  Wire.setClock(10000);// clock speed I2C
  // clock speed I2C
  //digitalWrite(SDA, 0);
  //digitalWrite(SCL, 0);
  pinMode(s0, OUTPUT); 
  pinMode(s1, OUTPUT); 
  pinMode(s2, OUTPUT); 
  pinMode(s3, OUTPUT);

  pinMode(BUFFER, OUTPUT);
  digitalWrite(BUFFER, HIGH);
  pinMode(MUXB, OUTPUT);
  digitalWrite(MUXB, HIGH);
  pinMode(MUXA, OUTPUT);
  digitalWrite(MUXA, HIGH);
  aht10_0x38.begin();
  aht10_0x39.begin();  
}
void loop() {
  // put your main code here, to run repeatedly:
  
  //Serial.print(millis()/1000.0);
  //Serial.print(",");
  mux0();
  delay(2000);
  Serial.println();
  mux1();
  delay(2000);
  Serial.println();
}
/* channel selection function */
void SetMuxChannel(byte channel)
{
  digitalWrite(s0, bitRead(channel ,0 ));
  digitalWrite(s1, bitRead(channel ,1 ));
  digitalWrite(s2, bitRead(channel ,2 ));
  digitalWrite(s3, bitRead(channel ,3 ));
}
// para poner canal 5 "SetMuxChannel(5);"
void mux0()
{
  digitalWrite(MUXA, LOW);  // Enable Mux0
  for(int i=0; i<10; i++)
  {
    SetMuxChannel(i);
    humidity = aht10_0x38.readHumidity();
    temp = aht10_0x38.readTemperature();
    //Serial.print(humidity);
    //Serial.print(",");
    Serial.print(temp);
    Serial.print(",");
    humidity = aht10_0x39.readHumidity();
    temp = aht10_0x39.readTemperature();
    //Serial.print(humidity);
    //Serial.print(",");
    Serial.print(temp);
    if(i !=9)
    {
      Serial.print(",");
    }
    delay(10);
  }
  digitalWrite(MUXA, HIGH);  // Disable MUXB
}

void mux1()
{
  digitalWrite(MUXB, LOW);  // Enable MUXB
  for(int i=0; i<15; i++)
  {
    SetMuxChannel(i);
    humidity = aht10_0x38.readHumidity();
    temp = aht10_0x38.readTemperature();
    //Serial.print(humidity);
    //Serial.print(",");
    Serial.print(temp);
    Serial.print(",");
    humidity = aht10_0x39.readHumidity();
    temp = aht10_0x39.readTemperature();
    //Serial.print(humidity);
    //Serial.print(",");
    Serial.print(temp);
    if(i !=14)
    {
      Serial.print(",");
    }
    delay(200);
  }
  digitalWrite(MUXB, HIGH);  // Disable MUXB
}
