#ifndef WIFI_TASK_H
#define WIFI_TASK_H

#include <Arduino.h>
#include <WiFi.h>

/**
 * Task: monitor the WiFi connection and keep it alive
 */
void wifiConnectionTask(void * parameter)
{
  while(1)
  {
    serial_print("WiFi.status = ");
    serial_println(WiFi.status());
    
    if(WiFi.status() == WL_CONNECTED){
      deviceStatus.IDLE = false;
      deviceStatus.WIFI_CONNECTING = false;
      deviceStatus.WIFI_OK = true;
      deviceStatus.API_OK = true;
      deviceStatus.UP = true;
      vTaskDelay(500 / portTICK_PERIOD_MS);
      continue; // jumps all what is below and starts from begin of while loop
    }

    deviceStatus.IDLE = false;
    deviceStatus.WIFI_OK = false;
    deviceStatus.API_OK = false;
    deviceStatus.UP = false;
    deviceStatus.WIFI_CONNECTING = true;
    serial_println("[WIFI] Connecting");
    WiFi.mode(WIFI_STA);
    WiFi.setHostname(DEVICE_NAME);
    WiFi.begin(WIFI_SSID, WIFI_PASS);

    unsigned long startAttemptTime = millis();

    // Keep looping while we're not connected and haven't reached the timeout
    while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < WIFI_TIMEOUT_MS)
    {
      serial_print(".");
      vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    serial_println();

    // When we couldn't make a WiFi connection (or the timeout expired)
    // sleep for a while and then retry.
    if(WiFi.status() != WL_CONNECTED){
      serial_println("[WIFI] FAILED");
      vTaskDelay(WIFI_RECOVER_TIME_MS / portTICK_PERIOD_MS);
      serial_println("[WIFI] RETRY");
      continue;
    }

    serial_print("[WIFI] Connected: ");
    serial_println(WiFi.localIP());
  }
}

#endif // WIFI_TASK_H