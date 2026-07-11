#ifndef THERMISTOR_H
#define THERMISTOR_H

#include "main.h"

typedef struct {
    ADC_HandleTypeDef *hadc;
    uint32_t            interval_ms;
    uint32_t            last_read;
    uint16_t             last_raw;
    float                last_celsius;
} Thermistor_HandleTypeDef;

void  Thermistor_Init(Thermistor_HandleTypeDef *therm, ADC_HandleTypeDef *hadc, uint32_t interval_ms);
void  Thermistor_Update(Thermistor_HandleTypeDef *therm);
float Thermistor_GetCelsius(Thermistor_HandleTypeDef *therm);

#endif /* THERMISTOR_H */