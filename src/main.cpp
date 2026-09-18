#include <Arduino.h>
#include "wifi.h"
#include "atuadores.h"
#include "mqtt.h"
#include "sensores.h"

bool wifi_conectado = false;
unsigned long u_tempo_luminosidade;

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
  //Serial.println("Rotina!");
  unsigned long agora = millis();
  if (agora - u_tempo_luminosidade > 1000){
      state_machine_luminosidade();
      u_tempo_luminosidade = agora;
  } 
  check_reconectar_mqtt();
  buzzer();
  yield();
  
}