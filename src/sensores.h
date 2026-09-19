#ifndef SENSORES_H
#define SENSORES_H

void state_machine_luminosidade();
void state_machine_temperatura();
void configurar_gpio_sensores();

typedef enum {
    LEITURA_SENSOR,
    MEDIA_LEITURA,
    POSTAR_MEDIA
} rotina_dados;

#endif