/*
 * circle_buffer.h
 *
 *  Created on: 14 апр. 2025 г.
 *      Author: 1213779
 */
#pragma once
#ifndef INC_CIRCLE_BUFFER_H_
#define INC_CIRCLE_BUFFER_H_

#include "stdint.h"

typedef struct
{
    uint8_t *data_;
    uint32_t head_;
    uint32_t tail_;
    uint32_t max_len_;
} CircleBuffer;


void ConstructCircleBuffer(CircleBuffer* buffer, uint8_t *data_buf, uint32_t size);
void ClearCircleBuffer(CircleBuffer* buffer);
uint32_t GetDataSizeCircleBuffer(CircleBuffer* buffer);
uint8_t PushDataCircleBuffer(CircleBuffer* buffer, uint8_t data);
uint8_t PopDataCircleBuffer(CircleBuffer* buffer, uint8_t *data);

#endif /* INC_CIRCLE_BUFFER_H_ */
