#include "circle_buffer.h"

void ConstructCircleBuffer(CircleBuffer* buffer, uint8_t *data_buf, uint32_t size)
{
    buffer->data_ = data_buf;
    buffer->head_ = 0;
    buffer->tail_ = 0;
    buffer->max_len_ = size;

}

void ClearCircleBuffer(CircleBuffer* buffer)
{
    buffer->head_ = 0;
    buffer->tail_ = 0;
}

uint32_t GetDataSizeCircleBuffer(CircleBuffer* buffer)
{
    if(buffer->head_ == buffer->tail_)
    {
        return 0;
    }
    else if(buffer->head_ > buffer->tail_)
    {
        return buffer->head_ - buffer->tail_;
    }
    else
    {
        return (buffer->max_len_ - buffer->tail_) + buffer->head_;
    }
}

uint8_t PushDataCircleBuffer(CircleBuffer* buffer, uint8_t data)
{
    uint32_t next = buffer->head_ + 1;
    if(next >= buffer->max_len_)
    {
        next = 0;
    }

    if(next == buffer->tail_)
    {
        return 1; //The buffer is full
    }
    else
    {
        buffer->data_[buffer->head_] = data;
        buffer->head_ = next;
        return 0;
    }
}

uint8_t PopDataCircleBuffer(CircleBuffer* buffer, uint8_t *data)
{
    if(buffer->head_ == buffer->tail_)
    {
        return 1; //The buffer is empty
    }
    else
    {
        uint32_t next = buffer->tail_ + 1;
        if(next >= buffer->max_len_)
        {
            next = 0;
        }
        *data = buffer->data_[buffer->tail_];
        buffer->tail_ = next;
        return 0;
    }
}
