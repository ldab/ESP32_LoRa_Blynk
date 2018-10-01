/*Copyright (c) 2018 Leonardo Bispo.  All right reserved.
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE. */

#include <Arduino.h>
#include <RH_RF95.h>
#include <RHEncryptedDriver.h>
#include <Speck.h>

RH_RF95 rf95;     // Instanciate a LoRa driver
Speck myCipher;   // Instanciate a Speck block ciphering
RHEncryptedDriver myDriver(rf95, myCipher); // Instantiate the driver with those two

float frequency = 868.0; // Change the frequency here. 
unsigned char encryptkey[16] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16}; // The very secret key
char HWMessage[] = "Hello World ! I'm happy if you can read me";
uint8_t HWMessageLen;

void setup()
{
  HWMessageLen = strlen(HWMessage);
  Serial.begin(9600);
  while (!Serial) ; // Wait for serial port to be available
  Serial.println("LoRa Simple_Encrypted Client");
  if (!rf95.init())
    Serial.println("LoRa init failed");
  // Setup ISM frequency
  rf95.setFrequency(frequency);
  // Setup Power,dBm
  rf95.setTxPower(13);
  myCipher.setKey(encryptkey, sizeof(encryptkey));
  Serial.println("Waiting for radio to setup");
  delay(1000);
  Serial.println("Setup completed");
}

void loop()
{
  uint8_t data[HWMessageLen+1] = {0};
  for(uint8_t i = 0; i<= HWMessageLen; i++) data[i] = (uint8_t)HWMessage[i];
  myDriver.send(data, sizeof(data)); // Send out ID + Sensor data to LoRa gateway
  Serial.print("Sent: ");
  Serial.println((char *)&data);
  delay(4000);
}
