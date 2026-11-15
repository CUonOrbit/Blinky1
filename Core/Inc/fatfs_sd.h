#ifndef FATFS_SD_H
#define FATFS_SD_H

#include "main.h"

extern SPI_HandleTypeDef hspi1; 
#define HSPI_SDCARD   &hspi1
#define SD_CS_PORT    SD_CS_GPIO_Port
#define SD_CS_PIN     SD_CS_Pin

#endif