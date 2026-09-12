#ifndef MQTT_H
#define MQTT_H

#include <ESP8266WiFi.h>
#include <PubSubClient.h>



void iniciar_mqtt();
void check_reconectar_mqtt();
void publicar_alarme(bool m);

#endif