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
  configurar_gpio_sensores();
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
  state_machine_luminosidade();
  state_machine_temperatura();
  check_reconectar_mqtt();
  buzzer();
  yield();
  
}