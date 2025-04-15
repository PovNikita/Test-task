/*
 * command_handl.h
 *
 *  Created on: 14 апр. 2025 г.
 *      Author: 1213779
 */
#pragma once
#ifndef INC_COMMAND_HANDL_H_
#define INC_COMMAND_HANDL_H_
#include "stdint.h"
#include "stm32f4xx_hal.h"
//#include "stm32f4xx_hal_msp.h"

extern TIM_HandleTypeDef htim3;

uint32_t SetPin(uint8_t *data);
uint32_t SetPWM(uint8_t *data);
uint32_t SetPWMX(uint8_t *data);


#endif /* INC_COMMAND_HANDL_H_ */
