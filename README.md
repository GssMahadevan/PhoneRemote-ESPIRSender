# PhoneRemote-ESPIRSender
ESP8266 Based IR code sender to Control IR based TV/Settop-Boxes/etc. 

Code is made generic so that Firmware of this ESP does not contain any detailed code for any TV/IR-Remote-Device.
This knowledge is kept with Linux based [Python-Server](https://github.com/GssMahadevan/PhoneRemote-Server). 
Based on model & button , a [TVRemote android-app](https://github.com/GssMahadevan/PhoneRemote-AndroidApp ) will send the information 
to  Python-Server.  Python-Server will send appropriate Raw-IR-Codes to this ESP module and frequency. 

This ESP module emits those IR codes to required device. In this way we can add more Remote codes in generic way to the Linux based server.

This has been tested with [9$ Chip Computer]( http://docs.getchip.com/chip.html). But code is generic it will run on any system that can
run python. So it can be tested with Raspberry (and other Linux, Windows and MAC boxes as well)


## Pre Requisitives
 * Install Arduino > 1.6.9
 * Install [ESP8266 for Arduino](https://github.com/esp8266/Arduino)
 * Ensure ESP8266 installed propely
 
 * Install [IRremoteESP8266 for ESP8266](https://github.com/markszabo/IRremoteESP8266)
 
 * Buy/prepare IR sending board
 * Connect the IR TX to D6 PIN (D6 pin on NodeMCU board, pin number might vary based on your configuration )
 * Change SSID and Password in IRServer_my.ino to suite your wifi network
 
## Dependent Projects
 * [PhoneRemote-Server](https://github.com/GssMahadevan/PhoneRemote-Server)
 * [PhoneRemote-AndroidApp](https://github.com/GssMahadevan/PhoneRemote-AndroidApp)
 

## UT
 * Test ESP working or not by using curl command like:
 
 ```
curl http://your_esp_board_aip_address/ir?code=2800,900,500,450,500,450,500,900,550,900,1450,900,500,450,500,450,500,450,500,450,500,450,500,450,500,450,500,450,1000,900,500,450,500,450,1000,450,500,900,500,450,500,450,500,450,500,450,500,450,500,450,500,450,500,450,500,450,500,450,500,450,1000,450,500,900,1000&hz=38&count=1
```

## Add new codes for new TV/IR-Appliance:
 * Use the ESP sketch to [dump IR codes](https://github.com/markszabo/IRremoteESP8266/tree/master/examples/IRrecvDumpV2 ) and burn in your ESP.
 * Buy/Prepare IR receiver board. Connect to your ESP to appropriate PIN
 * Connect to USB-Serial terminal using **screen**, **puty**, **cutecom** or **miniterm** to connect to your ESP board
 * For each button on your remote, capture the IR codes from your ESP board
 * Store the codes in a file and follow guide lines as in https://github.com/GssMahadevan/PhoneRemote-Server
 *
