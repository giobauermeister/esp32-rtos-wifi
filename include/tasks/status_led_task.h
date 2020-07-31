#ifndef STATUS_LED_TASK_H
#define STATUS_LED_TASK_H

#include <Arduino.h>
#include <WiFi.h>

/**
 * Task: Blink status LED to indicate various status of device
 * 
 * Slow Blink = connecting to WiFi
 * Fast Blink = connecting to API
 * Intermittent = future use
 * Fixed = normal working mode * 
 * 
 */
void statusLedTask(void * parameter)
{
  while(1)
  {
    if(deviceStatus.IDLE)
    {
      digitalWrite(LED_STATUS, LOW);
      vTaskDelay(500 / portTICK_PERIOD_MS);
    }
    if(deviceStatus.UP && deviceStatus.WIFI_OK && deviceStatus.API_OK)
    {
      digitalWrite(LED_STATUS, HIGH);
      vTaskDelay(500 / portTICK_PERIOD_MS);
    }
    if(deviceStatus.WIFI_CONNECTING)
    {
      digitalWrite(LED_STATUS, HIGH);
      vTaskDelay(1000 / portTICK_PERIOD_MS);
      digitalWrite(LED_STATUS, LOW);
      vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    if(deviceStatus.API_CONNECTING)
    {
      digitalWrite(LED_STATUS, HIGH);
      vTaskDelay(500 / portTICK_PERIOD_MS);
      digitalWrite(LED_STATUS, LOW);
      vTaskDelay(500 / portTICK_PERIOD_MS);
    }
  }
}

#endif // STATUS_LED_TASK_H