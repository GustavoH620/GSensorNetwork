#include "atuadores.h"

int tempo_led = 500;

void config_gpio() {
    pinMode(LED_BUILTIN, OUTPUT);
}

void led_btin_piscar(int m){
    digitalWrite(LED_BUILTIN, LOW);
    delay(100 * m);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100 * m);
}


void led_btin_wifi(bool wifi){
    if (wifi){
        digitalWrite(LED_BUILTIN, LOW);
    } else {
        digitalWrite(LED_BUILTIN, HIGH);
    }
}//a