#include "led_ext.h"

void LedExt_Init(LedExt_HandleTypeDef *led, GPIO_TypeDef *port, uint16_t pin, uint32_t interval_ms)
{
    led->port        = port;
    led->pin         = pin;
    led->interval_ms = interval_ms;
    led->last_toggle = HAL_GetTick();
    HAL_GPIO_WritePin(port, pin, GPIO_PIN_RESET);
}

void LedExt_Update(LedExt_HandleTypeDef *led)
{
    uint32_t now = HAL_GetTick();
    if ((now - led->last_toggle) >= led->interval_ms)
    {
        led->last_toggle = now;
        HAL_GPIO_TogglePin(led->port, led->pin);
    }
}