#include <Arduino.h>
#include "wifi.h"
#include "atuadores.h"
#include "mqtt.h"

bool wifi_conectado = false;


void setup() {

  Serial.begin(74880);
  config_gpio();
  iniciar_wifi();
  conectar_wifi();
  iniciar_mqtt();
  yield();

}

void loop() {
  check_reconectar_mqtt();
  if (checar_wifi() == 0){
    //Serial.printf("Rede conectada, prosseguindo com rotina...");
    wifi_conectado = true;
  }else{
      wifi_conectado = false;
      conectar_wifi();
  }
  led_btin_wifi(wifi_conectado);
  Serial.printf("Rotina!");
  check_reconectar_mqtt();
  buzzer();
  yield();
}