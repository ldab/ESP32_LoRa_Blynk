# ESP32 LoRa Blynk

**This code aims to communicate locally via LoRa (868 or 915Mhz) and forward readings to Blynk.**

Inspired by the "Guy with Swiss Accent": [#169 LoRa one-to-one Connection for a Mailbox Notifier with an Arduino and a Wemos Shield](https://www.youtube.com/watch?v=WV_VumvI-0A)

**Devices used:**

* [Wemos Lolin32 (Retired)](https://wiki.wemos.cc/products:lolin32:lolin32)
* <a href="http://s.click.aliexpress.com/e/cXBb67Os" target="_parent">TTGO LORA32 868/915Mhz SX1276 ESP32 Oled-display Bluetooth WIFI Lora</a>
* <a href="http://s.click.aliexpress.com/e/OteMO24" target="_parent">Lithium Polymer 3.7V 200mAh LiPo Rechargeable Battery with JST PH 2.0mm 2p</a>
* <a href="http://s.click.aliexpress.com/e/cmPF8fkG" target="_parent">Solar Panel 5V Mini Solar System 0.15W 0.6W 1W 1.25W 1.5W </a>
* <a href="http://s.click.aliexpress.com/e/bVt2JM6U" target="_parent">RFM95 LoRa transceiver module 868MHz | 915MHz | SX1276</a>
* <a href="http://s.click.aliexpress.com/e/b7GpcEfm" target="_parent">D1 mini Pro - ESP8266 WIFI</a>
* <a href="http://s.click.aliexpress.com/e/bT5Ujrws" target="_parent">BME280 I2C Humidity Temperature and Barometric Pressure Sensor Module</a>

___

The firmware has been written using PlatformIO which is a nice, neat IDE, check it out: [Learn how to install PlatformIO IDE](https://platformio.org/platformio-ide)

If you're feeling brave and want to customize or improve the Firmware Over the Air (OTA), check this link: [Over-the-Air (OTA)](http://docs.platformio.org/en/latest/platforms/espressif8266.html#over-the-air-ota-update) update basically you change your sketch and upload it by running the following line on PlatformIO terminal:

```platformio run --target upload --upload-port IP_ADDRESS_HERE```

Download Blynk App: [Getting Started with Blynk](https://www.blynk.cc/getting-started/)

1. Download Blynk App: [Android](http://j.mp/blynk_Android) or [Apple](http://j.mp/blynk_iOS)
2. Touch the QR-code icon and point the camera to the code below

    ![](https://camo.githubusercontent.com/00a959c0f6b0c46ac7ad030483dc2d848edcdc35/68747470733a2f2f696d6167652e6962622e636f2f67785a46447a2f556e7469746c65642e706e67)

3. Enjoy my app!
