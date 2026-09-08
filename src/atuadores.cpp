#include "atuadores.h"

int tempo_led = 500;

void config_gpio() {
    pinMode(LED_BUILTIN, OUTPUT);
}

void led_btin_erro(){
    digitalWrite(LED_BUILTIN, LOW);
    delay(100);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
}

void led_btin_wifi(bool wifi){
    if (wifi){
        digitalWrite(LED_BUILTIN, LOW);
    } else {
        digitalWrite(LED_BUILTIN, HIGH);
    }
}//a