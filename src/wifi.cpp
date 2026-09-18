#include <ESP8266WiFi.h>
#include "wifi.h"
#include "atuadores.h"
const char* nome_rede = "Pedro";
const char* senha = "B856E97E0";

long unsigned tempo_reconexao = 2000;
int vezes_reconexao = 1;
long unsigned ultima_reconexao = 0;

void iniciar_wifi(){
    WiFi.mode(WIFI_STA);
}

void conectar_wifi(){
    WiFi.begin(nome_rede, senha);
    Serial.printf("Tentando conectar a rede...");
    while (WiFi.status() != WL_CONNECTED) {
        led_btin_piscar(2);
        Serial.print(". ");
        delay(300);
    }
    switch (WiFi.status()){
        case WL_CONNECTED:
            Serial.println("Conectado! IP: ");
            Serial.println(WiFi.localIP());
            break;
        case WL_CONNECT_FAILED:
            Serial.println("Falha ao conectar a rede...");
            break;
        default:
            Serial.print("Erro: ");
            Serial.println(WiFi.status());

    }
}

void reconexao(){
    
    unsigned long agora = millis();
    if (agora - ultima_reconexao >= tempo_reconexao * vezes_reconexao){
        conectar_wifi();
        ultima_reconexao = millis();
        if (vezes_reconexao < 20) vezes_reconexao++;
    }
    

}

int checar_wifi(){
        switch (WiFi.status()){
        case WL_CONNECTED:
            //Serial.println("Conectado!");
            return 0;
        case WL_CONNECT_FAILED:
            Serial.println("Falha ao conectar a rede...");
            led_btin_piscar(1);
            return 1;
        case WL_DISCONNECTED:
            Serial.println("Rede desconectada...");
            led_btin_piscar(1);
            return 2;
        case WL_NO_SSID_AVAIL:
            Serial.println("Rede não existente...");
            led_btin_piscar(1);
            return 2;
        default:
            Serial.print("Erro: ");
            Serial.println(WiFi.status());
            led_btin_piscar(1);
            return 3;

    }
}