#include <Arduino.h>
#include "wifi.h"
#include "atuadores.h"

bool wifi_conectado = false;


void setup() {

  Serial.begin(115200);
  config_gpio();
  iniciar_wifi();
  conectar_wifi();

}

void loop() {
  int check = checar_wifi();
  if (checar_wifi() == 0){
    Serial.printf("Rede conectada, prosseguindo com rotina...");
    wifi_conectado = true;
  }else{
      wifi_conectado = false;
      conectar_wifi();
  }
  led_btin_wifi(check);
  Serial.printf("Rotina!");
  delay(100);
  yield();
}