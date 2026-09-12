#ifndef ATUADORES_H
#define ATUADORES_H

#include <Arduino.h>
#include <gpio.h>


#define LED_BTN 4
#define BUZZER 5
#define BTN_INTR 13




void config_gpio();
void led_btin_piscar(int m);
void led_btin_wifi(bool wifi);
void buzzer();

#endif