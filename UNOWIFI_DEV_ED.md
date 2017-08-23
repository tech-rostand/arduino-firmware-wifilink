# Content
 * [Arduino Uno WiFi Developer Edition](#arduino-uno-wifi-developer-edition) 
    * [Hardware](#hardware)
    * [Firmware](#firmware)
        * [Preparing for flashing](#preparing-for-flashing)
        * [esptool](#esptool)
        * [Firmware as a sketch](#firmware-as-a-sketch)
 * [ESP8266 Firmwares overview](#esp8266-firmwares-overview)
     * [Uno WiFi Developer Edition factory firmware](#uno-wifi-developer-edition-factory-firmware)
     * [ESP-link](#esp-link)
     * [WiFi Link](#wifi-link)
     * [SDK firmware](#sdk-firmware)
 * [Pin 4](#pin-4)
 * [WiFi Link firmware](#wifi-link-firmware)
     * [Initial serial flashing](#initial-serial-flashing)
     * [Building from source code](#building-from-source-code)
       * [Install esp8266 packages](#install-esp8266-packages)
       * [Download the source code](#download-the-source-code)
       * [Board selection and Verify](#board-selection-and-verify)
       * [OTA upload](#ota-upload)
       * [Serial upload](#serial-upload)
       * [SPIFFS](#spiffs)
       * [config.json](#configjson)
 
# Arduino Uno WiFi Developer Edition 

## Hardware

Arduino Uno WiFi Developer Edition is an Arduino UNO R3 with ESP8266 integrated on the board. It was developed and manufactured by Arduino.org.

ESP8266 is a ‘WiFi chip’  often used in combination with Arduino microcontrollers. Classic way is to connect the AVR or other microcontroller with ESP8266 using UART (Serial). The serial connection is then not available for communication with a computer (USB). Modern way of connecting AVR with ESP uses SPI connection. *It looks like the non ‘Dev Ed’ Uno WiFi will use SPI.* 

Arduino Uno WiFi Developer Edition connects ATmega328 microcontroller with ESP8266 using IO expander SC16IS750. ESP8266 is connected to IO expander with Serial, but the ATmega328 is to IO expander connected using analog ports A4 and A5 with TWI protocol. The IO expander converts the protocol. Speed is limited to 19200 baud, which is very slow.

With ESP8266 on board it is desired to use it to write into microcontroller a sketch send ‘over the air’. ‚Over the air‘ or OTA upload means the sketch is send from IDE to the board using WiFi.

To write an AVR program received over WiFi into AVR, the ESP must be connected to AVR’s serial pins. For this to work there is a direct serial to serial connection on Uno WiFi Developer Edition.  The electronic switch which connects this serial to serial is controlled with pin 4 of the ESP8266.

![Connection schema from arduino.org](doc/ArduinoUNOWIFI_drawing2.jpg)

## Firmware

The program of a device installed in the factory is called a firmware. In case of Uno WiFi the firmware is the program in the ESP8266. The purpose is to serve as a network interface for the program (sketch) in the AVR microcontroller and provide Web Panel for setup of the WiFi connection.

### Preparing for flashing

The firmware can be updated or changed. Two things are necessary to prepare Uno WiFi Dev Ed for writing the firmware to the ESP8266 flash memory (flashing). 

1. First step is bridging the USB serial of the AVR microcontroller to ESP8266 serial pins. It is a software thing. A simple sketch called EspRecovery.
2. Second step is to put the ESP8266 into so called DFU mode pushing a dedicated button while powering the board on.  

These steps are described in detail and with pictures in [Uno Wifi Dev Ed documentation](https://web.archive.org/web/20170711173532/http://www.arduino.org/learning/tutorials/advanced-guides/how-to-change-the-firmware-on-an-arduino-uno-wifi).

### esptool

All firmware binaries available for Uno Wifi Dev Ed can be flashed with esptool. The Arduino IDE plugin for upgrading the preinstalled firmware version installs esptool under the tools folder of the sketch folder - Arduino/tools/UnoWiFi/tool/bin

The connection thru the IO expander limits the speed of flashing. Recommended baudrate is 9600. Other esptool parameters for the Uno WiFi Dev Ed are *-b 9600 write_flash -ff 80m -fm qio -fs 32m* 

The exe version of the esptool is a packaged version of the python script esptool.py

* [esptool.py GitHub repository and reference](https://github.com/espressif/esptool)
 
Warning: don't use the erase command. Without some bootloader in the ESP8266 it could be a problem flashing the firmware of the Uno Wifi Dev Ed. 
 
### Firmware as a sketch
 
ESP8266 is supported in Arduino IDE with Arduino esp8266 core. It means that arduino sketch can be uploaded into ESP8266. The WiFi Link firmware is a sketch which can be build and uploaded with the Arduino IDE upload button. It works only as an OTA upload. The  tools for serial upload have a problem with the way the ESP is wired on Uno Wifi Dev Ed.

## ESP8266 Firmwares overview

### Uno WiFi Developer Edition factory firmware

The Arduino.org team did use a JeeLabs ESP-link fork (source code copy) with minor changes for the firmware of the Uno WiFi Developer Edition. They changed the design to Arduino and made sketch OTA upload work activating pin 4 before writing the sketch’s binary to AVR.

With IDE 1.8.x the library for the AVR side of this firmware is “Arduino Uno WiFi Dev Ed Library”. The network communication possibilities are limited to port 80 and MQTT. The library can be installed with Library Manager in IDE. 

This firmware can be installed or reinstalled with [firmware updater with GUI](https://web.archive.org/web/20170711173532/http://www.arduino.org/learning/tutorials/advanced-guides/arduino-uno-wifi-firmware-updater).

* [UnoWiFi-FirmwareUpdater-Plugin](https://github.com/arduino-libraries/UnoWiFi-FirmwareUpdater-Plugin/releases)
* [Source code GitHub repository](https://github.com/arduino-org/Esp-Link)

### ESP-link

Then version of ESP-link was used for the preinstalled firmware. JeeLabs develops the ESP-link further and it is compatible with Uno WiFi Developer Edition, except of sketch OTA upload.

The library for the AVR side is called EL-link and for the Uno WiFi Developer Edition it must use SC16IS750 interface.

* [ESP-link firmware GitHub repository](https://github.com/jeelabs/esp-link)
* [EL-link library GitHub repository](https://github.com/jeelabs/el-client)

### WiFi Link

The WiFi Link firmware is an ESP8266 arduino sketch developed by Arduino.org in Arduino IDE using Arduino esp8266 core. It is developed for the Arduino Star Otto, Arduino Primo and Uno WiFi and is compatible with Uno WiFi Developer Edition.

Sketch OTA upload is in WiFi Link firmware for now implemented only in the 'ota' branch.

The corresponding library is WiFi Link and it has a familiar API similar to WiFi and Ethernet library.

* [WiFi Link firmware GitHub repository](https://github.com/arduino-org/arduino-firmware-wifilink)
* [WiFi Link library GitHub repository](https://github.com/arduino-org/arduino-library-wifilink)

### SDK firmware

Theoretically it should work. It receives AT commands over serial line.

The AVR side must use SC16IS750 like other Uno WiFi libraries or the firmware must be modified to put pin 4 LOW for using direct serial connection. Possible library is WifiEsp. 

## Pin 4

Pin GPIO4 of the ESP8266 is on Uno WiFi Dev Ed connected to an electronic switch which opens the direct serial communication between ATmega328 and ESP8266.

This direct connection can be set to higher baudrate then the path thru IO expander. Tested is 115200 baud. 

The pin 4 must be set LOW to activate the serial line. *It remains a mystery for now, why the pin is in HIGH state at boot. Not one of the firmwares sets it HIGH.  Perhaps the bootloader does it.*

With the serial of AVR connected to ESP8266 it can’t be used for USB sketch uploading and Serial Monitor as it is the case with other equipment connecting to UART serial connection.

Alternative to uploading sketch over USB is OTA upload. Alternative to Serial Monitor is Telnet.

# WiFi Link firmware

## Initial serial flashing

The GitHub repository of the WiFi Link firmware contains [binaries of version 1.0.0](https://github.com/arduino-org/arduino-firmware-wifilink/releases/tag/1.0.0). There are two files:

* `ArduinoFirmwareWiFiLink-UNO_WIFI_DEV_ED-1.0.0.bin` - to write from address 0, contains bootloader and the firmware functions. 
* `ArduinoFirmwareWiFiLink-WEB_PANEL-1.0.0.bin` - to write from flash address 0x300000. It is an image of ESP file system SPIFFS, containing static file for the Web Panel. The file is 1 MB big.

For flashing you need the esptool. You can use the python script or if you installed "Arduino Uno WiFi Dev Ed Library", then you can use packaged esptool from tools/UnoWiFi/tool/bin in your sketches folder Arduino/.

If you didn't install the "Arduino Uno WiFi Dev Ed Library", install the WiFi Link library. You will need the EspRecovery sketch from examples of one of these libraries.

1. Create a folder ArduinoFirmwareWiFiLink in tools subfolder of your sketches folder (Arduino/tools). 
2. Download the release 1.0.0 .bin files into folder Arduino/tools/ArduinoFirmwareWiFiLink
3. In Arduino IDE open the sketch EspRecovery from Examples of "Arduino Uno WiFi Dev Ed Library" or WiFi Link library
4. Connect the board and upload the EspRecovery sketch
5. Put the ESP on Uno WiFi into DFU mode - disconnect the board from power and then hold the DFU button while connecting the USB cable. This step is described in detail and with pictures in [Uno Wifi Dev Ed documentation](https://web.archive.org/web/20170711173532/http://www.arduino.org/learning/tutorials/advanced-guides/how-to-change-the-firmware-on-an-arduino-uno-wifi).
6. open the command line and go to folder Arduino/tools/ArduinoFirmwareWiFiLink. (on Windows `cd %USERPROFILE%\Documents\Arduino\tools\ArduinoFirmwareWiFiLink`)
7. execute esptool with parameters. The first parameter -p should be the serial port where the Arduino is connected. All other parameters are the same for all setups: `-b 9600 write_flash -ff 80m -fm qio -fs 32m 0x000000 ArduinoFirmwareWiFiLink-UNO_WIFI_DEV_ED-1.0.0.bin 0x300000 ArduinoFirmwareWiFiLink-WEB_PANEL-1.0.0.bin`

Windows example with "Arduino Uno WiFi Dev Ed Library" esptool:
```
C:\Users\Duro\Documents\Arduino\tools\ArduinoFirmwareWiFiLink>..\UnoWiFi\tool\bin\esptool-windows -p COM4: -b 9600 write_flash -ff 80m -fm qio -fs 32m 0x000000 ArduinoFirmwareWiFiLink-UNO_WIFI_DEV_ED-1.0.0.bin 0x300000 ArduinoFirmwareWiFiLink-WEB_PANEL-1.0.0.bin 
```

It takes to 20 minutes to write the bin files at 9600 baud. Limitation is the connection between microcontroller and ESP8266 over IO expander. 

After successful flashing of the firmware you can connect to AP created by the ESP8266 and setup the connection to your WiFi network. The process is very **similar** to [first configuration with factory firmware](https://web.archive.org/web/20170711173532/http://www.arduino.org/learning/getting-started/getting-started-with-arduino-uno-wifi#First_Configuration).

Use [WiFi Link library](https://github.com/arduino-org/arduino-library-wifilink) in sketches.

## Building from source code

The WiFi Link firmware is an Arduino sketch so you can build it in Arduino IDE and upload it to ESP from Arduino IDE. There is no need for some linux toolchains like is the case with other ESP firmwares.

Building WiFi Link firmware from source files gives you possibility to build the newest version, build a branch version, build some fork version or change something in source code you need.

### Install esp8266 packages

Arduino Uno Wifi Dev Ed is supported from version 2.4 of the esp8266 core for Arduino IDE. For now, the version 2.4 is only a release candidate.

To install this pre-release using boards manager, follow the [instructions](https://github.com/esp8266/Arduino#installing-with-boards-manager), with the package URL replaced with the following one:
```
https://github.com/esp8266/Arduino/releases/download/2.4.0-rc1/package_esp8266com_index.json
```

Additionally, install the [Arduino ESP8266 filesystem uploader IDE plugin](https://github.com/esp8266/arduino-esp8266fs-plugin#arduino-esp8266-filesystem-uploader-)

### Download the source code

For start use the source code from the [master repository from Arduino.org](https://github.com/arduino-org/arduino-firmware-wifilink). Every GitHub repository has a green "Clone or download" button which opens a small menu. Choose "Download ZIP".

Open or extract the downloaded zip and copy the folder ArduinoFirmwareEsp from zip to your sketches folder.

Start Arduino IDE and open the ArduinoFirmwareEsp.ino sketch. It opens additional files as tabs in IDE.

**Go to config.h tab and uncomment `#define UNOWIFIDEVED`.**

### Board selection and Verify

In tools menu select board options. 

1. Choose Arduino from the ESP8266 section of the Boards menu. 
2. Next choose Model Uno Wifi. 
3. Flash Size selection should be "4M (1M SPIFFS)"  

Now verify the sketch with the Verify button. The first compilation after changing the board will take time.

From now on always check the selected board in the right bottom corner of the IDE window. For AVR sketch it should show "Arduino Uno Wifi on ...", for the ESP sketch "Arduino, Uno WiFi, 9600, 4M (1MB SPIFFS) on...".

### OTA upload 

The WiFi Link firmware supports OTA upload of new version of the firmware binary. OTA upload will only work if some version of WiFi Link is working in the ESP8266 of your Uno WiFi Dev Ed and is configured to STA or STA+AP mode.

After configuring the board to WiFi STA or STA+AP mode, the IDE will detect your board on network using mdns. The network 'port' will be accessible in Port submenu of Tools menu. Choose the network port for the OTA upload and use the Upload button in IDE.

The upload of the ArduinoFirmwareEsp.ino will overwrite the bootloader+firmware binary at address 0x0 and leave the SPIFFS part of the flash unchanged.

*Notes: Do not put the board in DFU mode. Do not search for some special programmer in Tools menu.*

### Serial upload

**Skip this if OTA upload works.**
 
For the serial upload you must prepare the board with EspRecovery sketch and DFU mode. 

Choose the serial port in Tools menu Port and try to upload with the Upload button, but it is possible it ends with an error.

Other option is to use command "Export compiled binary" from Sketch menu. It creates file named ArduinoFirmwareEsp.ino.arduino_uart.bin in sketch source code folder Arduino/ArduinoFirmwareEsp.

To flash with esptool:
1. Create a folder ArduinoFirmwareWiFiLink in tools subfolder of your sketches folder (Arduino/tools), if it doesn't exist.
2. move Arduino/ArduinoFirmwareEsp/ArduinoFirmwareEsp.ino.arduino_uart.bin to Arduino/tools/ArduinoFirmwareWiFiLink
3. In Arduino IDE open the sketch EspRecovery from Examples of "Arduino Uno WiFi Dev Ed Library" or WiFi Link library
4. Connect the board and upload the EspRecovery sketch (don't forget to set the board to Arduino Uno Wifi)
5. Put the ESP on Uno WiFi into DFU mode - disconnect the board from power and then hold the DFU button while connecting the USB cable.
6. open the command line and go to folder Arduino/tools/ArduinoFirmwareWiFiLink. (on Windows `cd %USERPROFILE%\Documents\Arduino\tools\ArduinoFirmwareWiFiLink`)
7. execute esptool with parameters. The first parameter -p should be the serial port where the Arduino is connected. All other parameters are the same for all setups: `-b 9600 write_flash -ff 80m -fm qio -fs 32m 0x000000 ArduinoFirmwareEsp.ino.arduino_uart.bin`

The procedure is basically the same as described in "Initial serial flashing". The name of the bin file is different and we don't provide the SPIFFS binary for address 0x300000 because it is already flashed from initial flashing. **The flashing without the 1 MB SPIFFS binary is much quicker and doesn't erase the setup for your wifi network.**

Windows example with "Arduino Uno WiFi Dev Ed Library" esptool:
```
C:\Users\Duro\Documents\Arduino\tools\ArduinoFirmwareWiFiLink>..\UnoWiFi\tool\bin\esptool-windows -p COM4: -b 9600 write_flash -ff 80m -fm qio -fs 32m 0x000000 ArduinoFirmwareEsp.ino.arduino_uart.bin 
```

If you didn't do the initial flashing of WiFi Link firmware 1.0.0 binaries, then you need to flash the SPIFFS binary to address 0x300000. You can use the release 1.0.0 binary ArduinoFirmwareWiFiLink-WEB_PANEL-1.0.0.bin. Add it to the command above or execute it separately. Flashing the SPIFFS erases the settings made in Web Panel and the board returns to AP mode.

### SPIFFS
 
SPIFFS is the file system for ESP8266. 
 
In subfolder data of the source codes of the WiFi Link firmware are the static web files (html, css, js) for the Web Panel. You can add your own files and they will be accessible on expected url.
 
We installed a plugin tool in chapter "Install esp8266 packages". This plugin creates a "ESP8266 Sketch Data upload" command in Tools menu.
 
The tool builds the SPIFFS binary and uploads it to selected port. **With network port it will use OTA and it is fast.** 

With serial port you must use EspRecovery sketch and put the board in DFU mode. If you must do a serial flashing and the IDE upload doesn't work, find the created binary and flash it with esptool on address 0x300000. The path to the binary file is in 'verbose' output mode on IDE console.

Flashing the SPIFFS erases the WiFi settings made in Web Panel and the board starts in AP mode.

### config.json

WiFi Link firmware writes WiFi settings into SPIFFS file config.json. SPIFFS upload overrides the SPIFFS content and the setting are lost. After restart WiFi Link firmware goes to AP mode and you must once again connect to this AP, choose the WiFi network, enter the password and connect back to your WiFi. 

If you often upload the SPIFFS, add your config.json file into data subfolder of the WiFi Link firmware source codes. The basic content is `{"ssid":"yourwifi","password":"yourpassword"}.` 
