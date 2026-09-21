#include "sensores.h"
#include "atuadores.h"
#include "mqtt.h"
#include <Arduino.h>
#include <gpio.h>
#include "DHT.h"


//luminosidade
#define PINO_LDR A0
static rotina_dados estado_leitura_luminosidade = LEITURA_SENSOR;
int leitura_luminosidade = 0;
int n_leituras = 1;
int media;
static unsigned long u_leitura_lum = 0;

//Temperatura
#define PINO_DHT 14
static rotina_dados estado_leitura_temperatura = LEITURA_SENSOR;
float leitura_temperatura = 0;
float media_temperatura = 0;
float leitura_humidade = 0;
float media_humidade = 0;
static unsigned long u_leitura_tu = 0;
int n_leitura_temp = 0;

//Presença
#define PINO_PIR 16 //D0
bool ultimo_estado = false;
float tempo_intr_anterior = 0;
extern bool alarme_estado;

void IRAM_ATTR f_presenca_intr(){
    if (millis() - tempo_intr_anterior > 400){
        tempo_intr_anterior = millis();
        alarme_estado = !alarme_estado;
        publicar_alarme(alarme_estado);
        digitalWrite(LED_BTN, alarme_estado);
    }
}


DHT dht(PINO_DHT, DHT22);


void configurar_gpio_sensores(){
    pinMode(PINO_LDR, INPUT);
    pinMode(PINO_DHT, INPUT);
    pinMode(PINO_PIR, INPUT);
    attachInterrupt(digitalPinToInterrupt(PINO_PIR), f_presenca_intr, RISING); 
    dht.begin();
}

void state_machine_luminosidade(){
    switch(estado_leitura_luminosidade){
        case LEITURA_SENSOR:
            if (millis() - u_leitura_lum > 1000){
                u_leitura_lum = millis();
                leitura_luminosidade += analogRead(PINO_LDR);
                n_leituras++;
                if (n_leituras >= 5) estado_leitura_luminosidade = MEDIA_LEITURA;
                break;
            } else {
                break;
            }
        case MEDIA_LEITURA: {
            media = leitura_luminosidade / 5;
            estado_leitura_luminosidade = POSTAR_MEDIA;
            break;
        }
        case POSTAR_MEDIA:
            n_leituras = 0;
            leitura_luminosidade = 0;
            Serial.println("Luminosidade: "+ String(media));
            estado_leitura_luminosidade = LEITURA_SENSOR;
            break;
        
        

    }

}

void state_machine_temperatura(){
    switch(estado_leitura_temperatura){
        case LEITURA_SENSOR:
            if (millis() - u_leitura_tu > 5000){
                u_leitura_tu = millis();
                leitura_temperatura = dht.readTemperature();
                leitura_humidade = dht.readHumidity();
                if (isnan(leitura_temperatura) || isnan(leitura_humidade)){
                    Serial.println("Leitura falhou");
                    break;
                }
                n_leitura_temp++;
                media_temperatura += leitura_temperatura;
                media_humidade += leitura_humidade;
                if (n_leitura_temp >= 10){
                    estado_leitura_temperatura = MEDIA_LEITURA;
                    break;
                }
                estado_leitura_temperatura = POSTAR_MEDIA;
                break;
                
            } else {
                break;
            }
            
        case MEDIA_LEITURA:{
            n_leitura_temp = 1;
            String media_string = "Temperatura >> " + String(media_temperatura / 10) + " ºC / Humidade >> " + String(media_humidade / 10) + " %";
            Serial.print("Média e leituras em 10 ciclos: ");
            Serial.println(media_string);
            estado_leitura_temperatura = POSTAR_MEDIA;
            media_humidade = 0;
            media_temperatura = 0;
            break;
        }
        case POSTAR_MEDIA:
            String string_temp_umid_atual = "Temperatura atual >> " + String(leitura_temperatura) + " ºC / Umidade: " + String(leitura_humidade) + " %";
            Serial.println(string_temp_umid_atual);
            estado_leitura_temperatura = LEITURA_SENSOR;
            break;
    }

}



