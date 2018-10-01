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

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

#include "Wire.h"   
#include <SPI.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

//----------------------RF LIB STUFF ----------------------------------
#include <RH_RF95.h>
#include "RHEncryptedDriver.h"
#include <Speck.h>

RH_RF95 rf95;     // Instances a LoRa driver
Speck myCipher;   // Instances a Speck block ciphering
RHEncryptedDriver myDriver(rf95, myCipher); // Instantiate the driver with those two

//--------------------------------------------------------

#define LED       5

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "YourAuthToken";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Aloha Wireless";
char pass[] = "aloha123";

// Keep this flag not to re-sync on every reconnection
bool isFirstConnect = true;

float frequency = 868.0; // Change the frequency here. 
unsigned char encryptkey[16]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16}; // The very secret key 

//Declare instances and functions

BlynkTimer timer;
void initRF(float f = 868.0);
void blinkLED(void);

void initRF(float f)
{
  Serial.println();
  Serial.println("LoRa Simple_Encrypted Server");
  if (!rf95.init()) Serial.println("LoRa init failed");
  // Setup ISM frequency
  rf95.setFrequency(f);
  // Setup Power,dBm
  rf95.setTxPower(14);
  myCipher.setKey(encryptkey, 16);
  delay(4000);
  Serial.println("Setup completed");
}

void blinkLED(void)
{
  digitalWrite(LED, !digitalRead(LED));
}

// This function will run every time Blynk connection is established
BLYNK_CONNECTED() {
  if (isFirstConnect) {
    // Request Blynk server to re-send latest values for all pins
    Blynk.syncAll();

    // You can also update individual virtual pins like this:
    //Blynk.syncVirtual(V0, V2);

    isFirstConnect = false;
  }

  // Let's write your hardware uptime to Virtual Pin 2
  int value = millis() / 1000;
  Blynk.virtualWrite(V2, value);
}

BLYNK_WRITE(V0)
{
  // Use of syncAll() will cause this function to be called
  // Parameter holds last slider value
  int sliderValue0 = param.asInt();
}

BLYNK_WRITE(V2)
{
  // You'll get uptime value here as result of syncAll()
  int uptime = param.asInt();
}

void setup()
{
  // Debug console
  Serial.begin(115200);

  pinMode(LED, OUTPUT);
  
  timer.setInterval(800, blinkLED);

  WiFi.begin(ssid, pass);
  if(WiFi.status());

  initRF(frequency);
  
  Blynk.config(auth);
}

void loop()
{
  Blynk.run();
  timer.run();

  if (myDriver.available()) {
    // Should be a message for us now   
    uint8_t buf[myDriver.maxMessageLength()];
    uint8_t len = sizeof(buf);
    if (myDriver.recv(buf, &len)) {
      Serial.print("Received: ");
      Serial.println((char *)&buf);
    }
    else
    {
        Serial.println("recv failed");
    }
  }
}