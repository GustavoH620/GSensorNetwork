#include "sensores.h"
#include <Arduino.h>
#include <gpio.h>

//luminosidade
static rotina_dados estado_leitura_luminosidade = LEITURA_SENSOR;
int leitura_luminosidade = 0;
int n_leituras = 1;
int media;


void state_machine_luminosidade(){
    switch(estado_leitura_luminosidade){
        case LEITURA_SENSOR:
            leitura_luminosidade += analogRead(A0);
            n_leituras++;
            if (n_leituras >= 5) estado_leitura_luminosidade = MEDIA_LEITURA;
            break;
        case MEDIA_LEITURA: {
            media = leitura_luminosidade / 5;
            estado_leitura_luminosidade = POSTAR_MEDIA;
            break;
        }
        case POSTAR_MEDIA:
            n_leituras = 0;
            leitura_luminosidade = 0;
            Serial.print(media);
            Serial.println("Media postada!");
            estado_leitura_luminosidade = LEITURA_SENSOR;
            break;

    }

}