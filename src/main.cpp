#include <Arduino.h>
#include <WiFi.h>

#include "device_config.h"
#include "tasks/wifi_task.h"
#include "tasks/status_led_task.h"

// const uint8_t ouput[2];
// const uint8_t input[4];

void setup() {
#if SERIAL_DEBUG_ENABLE
  Serial.begin(115200);
  serial_println("serial_begin");
#endif
  serial_println("OK");

  // --------------------------
  // IO Configuration
  // --------------------------
  uint8_t i=0;
  for (i=0; i<4; i++) {
    pinMode(output[i], OUTPUT);
  }
  for (i=0; i<4; i++) {
    digitalWrite(output[i], LOW);
  }
  for (i=0; i<2;i++) {
    pinMode(input[i], INPUT);
  }
  pinMode(LED_STATUS, OUTPUT);
  pinMode(BTN_CONFIG, INPUT_PULLDOWN);  
  digitalWrite(LED_STATUS, LOW);

  deviceStatus.IDLE = true;
  if(deviceStatus.IDLE == true) serial_println("deviceStatus.IDLE");

  // ----------------------------------------------------------------
  // TASK: Control status LED indicator.
  // ----------------------------------------------------------------
  xTaskCreate(
    statusLedTask,
    "statusLedTask",  // Task name
    5000,            // Stack size (bytes)
    NULL,             // Parameter
    4,                // Task priority
    NULL             // Task handle
  );

  // ----------------------------------------------------------------
  // TASK: Connect to WiFi & keep the connection alive.
  // ----------------------------------------------------------------
  xTaskCreatePinnedToCore(
    wifiConnectionTask,
    "wifiConnectionTask",  // Task name
    5000,            // Stack size (bytes)
    NULL,             // Parameter
    1,                // Task priority
    NULL,             // Task handle
    1                 //Arduino sketch core 1
  );  

}

void loop() {
  vTaskDelay(1000 / portTICK_PERIOD_MS);
}