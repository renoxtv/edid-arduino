#include <Wire.h>

#define eeprom 0x54 //Address of 24LC256 eeprom chip
#define WP_PIN 4 //Write protect pin

void setup() 
{
    pinMode(WP_PIN, OUTPUT);
    digitalWrite(WP_PIN, HIGH); //ENABLE write protect
    Wire.begin();
    Serial.begin(9600);
    
    unsigned int address = 0; //first address of the EEPROM
    for(address = 0; address< 128; address++) {
      Serial.print(readEEPROM(eeprom, address), HEX);
      Serial.print(' ');
      if (address % 16 == 0) Serial.println();
    }
}

void loop() 
{
  /*there's nothing in the loop() function because we don't want the arduino to 
  repeatedly write the same thing to the EEPROM over and over. 
  We just want a one-time write, so the loop() function is avoided with EEPROMs.*/
}


//defines readEEPROM
byte readEEPROM(int deviceaddress, unsigned int eeaddress ) {
  byte rdata = 0xFF;
  Wire.beginTransmission(deviceaddress);
  Wire.write((int)(eeaddress >> 8));
  Wire.write((int)(eeaddress & 0xFF));
  Wire.endTransmission();
  Wire.requestFrom(deviceaddress,1);
  if (Wire.available())
    rdata = Wire.read();
  return rdata;
}