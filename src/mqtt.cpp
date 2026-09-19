#include "mqtt.h"
#include "atuadores.h"

extern bool alarme_estado;
const char* server_mqtt = "broker.hivemq.com";
const char* topico_alarme = "gSN/alarme";
const int porta_mqtt = 1883;
unsigned long tempo_anterior_mqtt = 0;
String clientId = "G_ESP8266" + String (ESP.getChipId(), HEX) + "-" + String(random(1000, 9999));
String nome_comodo = "escritório";

WiFiClient espClient;
PubSubClient client(espClient);

void callback(char* topic, byte* payload, unsigned int lenght){
    String mensagem;
    for (unsigned int i = 0; i < lenght; i++) {
        mensagem += (char)payload[i];
    }
    Serial.print("Msg alarme: ");
    Serial.println(mensagem);
    if (mensagem == "1") alarme_estado = true;
    if (mensagem == "0") alarme_estado = false;
    buzzer();
}

void iniciar_mqtt(){
    client.setServer(server_mqtt, porta_mqtt);
    client.setCallback(callback);
    Serial.println("Conectanddo ao server MQTT...");

}
void check_reconectar_mqtt(){
    unsigned long agora = millis();
    client.loop();
    if (!client.connected() && agora - tempo_anterior_mqtt >= 5000){
        tempo_anterior_mqtt = agora;
        Serial.printf("Conexão MQTT perdida, reconectando...");
        
        if (client.connect(clientId.c_str())){
            Serial.printf("Reconectado!");
            client.subscribe(topico_alarme);
            client.loop();
        } else {
            Serial.printf("Reconexão falhou, tentando no próximo loop...");
            Serial.print(client.state());
        }

    } else {
        client.loop(); 
    }
}

void publicar_alarme(bool m){
    if (m) {
        client.publish(topico_alarme, "1");
    } else {
        client.publish(topico_alarme, "0");
    }
}

void publicar_dados(String topico, int dados);


