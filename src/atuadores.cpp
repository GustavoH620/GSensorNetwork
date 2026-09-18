#include "atuadores.h"
#include "mqtt.h"

int tempo_led = 500;
volatile unsigned long tempo_anterior = 0;
volatile bool alarme_estado = false;

void IRAM_ATTR f_btn_intr(){
    unsigned long agora = millis();
    if (agora - tempo_anterior >= 300){
        tempo_anterior = agora;
        alarme_estado = !alarme_estado;
        publicar_alarme(alarme_estado);
        digitalWrite(LED_BTN, alarme_estado);
    }
    
}
void config_gpio() {
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(BUZZER, OUTPUT);
    pinMode(LED_BTN, OUTPUT);
    pinMode(BTN_INTR, INPUT_PULLUP);
    pinMode(A0, INPUT);
    attachInterrupt(digitalPinToInterrupt(BTN_INTR), f_btn_intr, FALLING); 

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
}

void buzzer(){
    if (alarme_estado){
        digitalWrite(LED_BTN, HIGH);
        for (int i = 1; i < 6; i++){
            digitalWrite(BUZZER, HIGH);
            delay(50);
            digitalWrite(BUZZER, LOW);
            delay(50);
        }

        
    } else {
        digitalWrite(BUZZER, LOW);
        digitalWrite(LED_BTN, LOW);
    }
}