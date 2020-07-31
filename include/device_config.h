#ifndef DEVICE_CONFIG_H
#define DEVICE_CONFIG_H

#define WIFI_TIMEOUT_MS 6000
#define WIFI_RECOVER_TIME_MS 500

#define WIFI_SSID   "iPhone"
#define WIFI_PASS   "987654321"
#define DEVICE_NAME "ESP32_DA121"

#define LED_STATUS  23
#define BTN_CONFIG  32

#if SERIAL_DEBUG_ENABLE
  #define serial_print(x)  Serial.print (x)
  #define serial_println(x)  Serial.println (x)
#else
  #define serial_print(x)
  #define serial_println(x)
#endif

typedef struct device_status_t {
  bool IDLE             = false;
  bool CONFIG_MODE      = false;
  bool WIFI_CONNECTING  = false;
  bool API_CONNECTING   = false;
  bool WIFI_OK          = false;
  bool API_OK           = false;
  bool UP               = false;
} device_status_t;

device_status_t deviceStatus;

const uint8_t output[2] = {16,17};
const uint8_t input[4] = {33,25,26,27};

#endif // DEVICE_CONFIG_H