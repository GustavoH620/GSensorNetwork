#ifndef SENSORES_H
#define SENSORES_H

void state_machine_luminosidade();

typedef enum {
    LEITURA_SENSOR,
    MEDIA_LEITURA,
    POSTAR_MEDIA
} rotina_dados;

#endif