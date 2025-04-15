/*
 * message_handl.h
 *
 *  Created on: 14 апр. 2025 г.
 *      Author: 1213779
 */
#pragma once
#ifndef INC_MESSAGE_HANDL_H_
#define INC_MESSAGE_HANDL_H_

#include "stdio.h"
#include "stdint.h"
#include "stm32f4xx_hal.h"


typedef enum
{
    BASETITLE       = 0xA1A2
} Titles;

typedef enum
{
    SETPIN          = 0x0001,
    SETPWM50_100    = 0x001A,
    SETPWMX         = 0x0028
} Package;

typedef enum
{
    SETPIN1         = 11,
    RESETPIN1       = 15,

    SETPWM50PIN2    = 3,
    SETPWM100PIN2   = 7
}Commands;

typedef struct
{
    uint16_t title;
    Package pack;
    uint8_t data;
} Message;

extern UART_HandleTypeDef huart1;

uint8_t CalculateCheckSum(const uint8_t* data, uint8_t len);

uint8_t CalculateCheckSumFromMsg(const Message* msg);

void SendUART(uint8_t* data, size_t len);

void SendMsg(const Message* msg);

void SendGoodAnsMes(const Message* received_msg);

void SendFailAnsMes(const Message* received_msg);

uint8_t ParseAndCheckData(const uint8_t* data, Message* msg);

#endif /* INC_MESSAGE_HANDL_H_ */
