#ifndef LED_EXT_H
#define LED_EXT_H

#include "main.h"

typedef struct {
    GPIO_TypeDef *port;
    uint16_t      pin;
    uint32_t      interval_ms;
    uint32_t      last_toggle;
} LedExt_HandleTypeDef;

void LedExt_Init(LedExt_HandleTypeDef *led, GPIO_TypeDef *port, uint16_t pin, uint32_t interval_ms);
void LedExt_Update(LedExt_HandleTypeDef *led);

#endif /* LED_EXT_H */