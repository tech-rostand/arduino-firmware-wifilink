
/*
 * Firmware version and build date
 */

#define BUILD_DATE  __DATE__ " " __TIME__
#define FW_VERSION  "1.0.1"
#define FW_NAME     "wifilink"

/*
 * Define board model name
 */

//#define STAROTTO
//#define PRIMO
#define UNOWIFIDEVED
//#define UNOWIFI
//#define GENERIC_ESP8266

#ifdef UNOWIFIDEVED
#define UNOWIFIDEVED_STRAIGHT_SERIAL
#endif

/*
 * Enable/Disable Debug
 */

//#define DEBUG
//#define BAUDRATE_DEBUG 115200

/*
 * Define board hostname
 */

#define DEF_HOSTNAME "arduino"

/*
 * Defines the communication channel between microcontroller
 * and esp82266, with concerning parameters
 */

//#define HOSTNAME "arduino" //used by mdns protocol

#if defined(STAROTTO)
  //Arduino STAR OTTO configuration parameters
  #define BOARDMODEL "STAROTTO"
  #define ARDUINO_BOARD "star_otto" //mdns
  #define ESP_CH_UART
  #define BAUDRATE_COMMUNICATION 460800
  #define WIFI_LED 14
  #define SSIDNAME "Arduino-Star-Otto"
#elif defined(PRIMO)
  //Arduino PRIMO configuration parameters
  #define BOARDMODEL "PRIMO"
  #define ARDUINO_BOARD "primo"     //mdns
  #define ESP_CH_SPI
  #define WIFI_LED 2
  #define SSIDNAME "Arduino-Primo"
#elif defined(UNOWIFI)
  //Arduino UNOWIFI configuration parameters
  #define BOARDMODEL "UNOWIFI"
  #define ARDUINO_BOARD "unowifi"     //mdns
  #define ESP_CH_SPI
  #define WIFI_LED 2
  #define SSIDNAME "Arduino-Uno-WiFi"
#elif defined(UNOWIFIDEVED)
  //Arduino UNO WIFI DEV. EDITION configuration parameters
  #define BOARDMODEL "UNOWIFIDEVED"
  #define ARDUINO_BOARD "unowifi"   //mdns
  #define ESP_CH_UART
#if defined(UNOWIFIDEVED_STRAIGHT_SERIAL)
  #define BAUDRATE_COMMUNICATION 115200
#else
  #define BAUDRATE_COMMUNICATION 19200
#endif
  #define WIFI_LED 14
  #define MCU_RESET_PIN 12
  #define SSIDNAME "Arduino-Uno-WiFi"
#elif defined(GENERIC_ESP8266)
  #define BOARDMODEL "GENERIC_ESP8266"
  #define ARDUINO_BOARD "esp8266"   //mdns
  #define ESP_CH_UART
  #define BAUDRATE_COMMUNICATION 115200
  #define WIFI_LED 14
  #define MCU_RESET_PIN 0
  #define SSIDNAME "ESP8266-Module"
#endif
