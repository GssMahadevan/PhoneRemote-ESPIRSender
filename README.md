# PhoneRemote-ESPIRSender
ESP8266 Based IR code sender to Control IR based TV/Settop-Boxes/etc. 

Code is made generic so that Firmware of this ESP does not contain any detailed code for any TV/IR-Remote-Device.
This knowledge is kept with Linux based Python-Server (https://github.com/GssMahadevan/PhoneRemote-Server). 
Based on model & button , a android-app ( https://github.com/GssMahadevan/PhoneRemote-AndroidApp ) will send the information 
to  Python-Server.  Python-Server will send appropriate Raw-IR-Codes to this ESP module and frequency. 

This ESP module emits those IR codes to required device. In this way we can add more Remote codes in generic way to the Linux based server.

This has been tested with 9$ Chip ( http://docs.getchip.com/chip.html). But code is generic it will run on any system that can
run python. So it can be tested with Raspberry (and other Linux, Windows and MAC boxes as well)


## Pre Requisitives
 * Install Arduino > 1.6.9
 * Install ESP8266 for Arduino from https://github.com/esp8266/Arduino
 * Ensure ESP8266 installed propely
 
 * Install IRremoteESP8266 for ESP8266 from https://github.com/markszabo/IRremoteESP8266
 
 * Buy/prepare IR sending board
 * Connect the IR TX to D6 PIN (D6 pin on NodeMCU board )
 
## Dependent Projects
 * https://github.com/GssMahadevan/PhoneRemote-Server
 * https://github.com/GssMahadevan/PhoneRemote-AndroidApp
 

