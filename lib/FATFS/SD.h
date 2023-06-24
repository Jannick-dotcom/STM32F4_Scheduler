#pragma once
#include "fatfs.h"

void HAL_SD_MspInit(SD_HandleTypeDef *hsd);

void initSD_Card();