#include "thermistor.h"
#include <math.h>

/* ---- Circuit / thermistor constants: adjust to match your actual parts ---- */
#define THERM_FIXED_RESISTOR_OHMS   10000.0f   /* fixed resistor value in the divider */
#define THERM_NOMINAL_RESISTANCE    10000.0f   /* thermistor resistance at 25C (check datasheet) */
#define THERM_NOMINAL_TEMP_C        25.0f
#define THERM_BETA_COEFFICIENT      3950.0f    /* common default; check your thermistor's datasheet */
#define ADC_MAX_VALUE               4095.0f    /* 12-bit ADC */

void Thermistor_Init(Thermistor_HandleTypeDef *therm, ADC_HandleTypeDef *hadc, uint32_t interval_ms)
{
    therm->hadc         = hadc;
    therm->interval_ms  = interval_ms;
    therm->last_read    = HAL_GetTick();
    therm->last_raw     = 0;
    therm->last_celsius = 0.0f;
}

static float RawToCelsius(uint16_t raw)
{
    /* Voltage divider: thermistor on top (3.3V side), fixed resistor on bottom (GND side).
       ADC reads the midpoint, so raw value is proportional to voltage across the fixed resistor. */
    float resistance = THERM_FIXED_RESISTOR_OHMS * ((ADC_MAX_VALUE / (float)raw) - 1.0f);

    float steinhart = resistance / THERM_NOMINAL_RESISTANCE;
    steinhart = logf(steinhart);
    steinhart /= THERM_BETA_COEFFICIENT;
    steinhart += 1.0f / (THERM_NOMINAL_TEMP_C + 273.15f);
    steinhart = 1.0f / steinhart;
    steinhart -= 273.15f; /* back to Celsius */

    return steinhart;
}

void Thermistor_Update(Thermistor_HandleTypeDef *therm)
{
    uint32_t now = HAL_GetTick();
    if ((now - therm->last_read) < therm->interval_ms)
    {
        return;
    }
    therm->last_read = now;

    HAL_ADC_Start(therm->hadc);
    if (HAL_ADC_PollForConversion(therm->hadc, 10) == HAL_OK)
    {
        therm->last_raw     = HAL_ADC_GetValue(therm->hadc);
        therm->last_celsius = RawToCelsius(therm->last_raw);
    }
    HAL_ADC_Stop(therm->hadc);
}

float Thermistor_GetCelsius(Thermistor_HandleTypeDef *therm)
{
    return therm->last_celsius;
}