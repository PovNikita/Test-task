#include "message_handl.h"

uint8_t CalculateCheckSum(const uint8_t* data, uint8_t len)
{
    uint8_t check_sum = 0;
    for(uint8_t i = 0;i < len; ++i)
    {
        check_sum += data[i]; //& 0b00001111;
        //check_sum += (data[i] >> 4);
    }
    return check_sum;
}

uint8_t CalculateCheckSumFromMsg(const Message* msg)
{
    uint8_t data[] = {(msg->pack >> 8), msg->pack, msg->data};
    return CalculateCheckSum(data, sizeof(data)/sizeof(data[0]));
}

void SendUART(uint8_t* data, size_t len)
{
	HAL_UART_Transmit(&huart1, data, len, 1);
}

void SendMsg(const Message* msg)
{
    uint8_t tx_buffer[] = {msg->title >> 8, msg->title, msg->pack >> 8, msg->pack, msg->data, CalculateCheckSumFromMsg(msg)};
    SendUART(tx_buffer, sizeof(tx_buffer)/sizeof(tx_buffer[0]));
}

void SendGoodAnsMes(const Message* received_msg)
{
    Message AnsMsg = {
        .title = BASETITLE,
        .pack = received_msg->pack,
        .data = 0
    };
    SendMsg(&AnsMsg);
}

void SendFailAnsMes(const Message* received_msg)
{
    Message AnsMsg = {
        .title = BASETITLE,
        .pack = received_msg->pack,
        .data = 1
    };
    SendMsg(&AnsMsg);
}

uint8_t ParseAndCheckData(const uint8_t* data, Message* msg)
{
    msg->title = (data[0] << 8) | data[1];
    msg->pack = (data[2] << 8) | data[3];
    msg->data = data[4];
    uint8_t crc = data[5];
    if(msg->title != BASETITLE)
    {
        SendFailAnsMes(msg);
        return 1;
    }
    else if(crc != CalculateCheckSumFromMsg(msg))
    {
        SendFailAnsMes(msg);
        return 1;
    }
    else if(msg->pack == SETPIN && (msg->data == SETPIN1 || msg->data == RESETPIN1))
    {
        SendGoodAnsMes(msg);
        return 0;
    }
    else if(msg->pack == SETPWM50_100 && (msg->data == SETPWM50PIN2 || msg->data == SETPWM100PIN2))
    {
        SendGoodAnsMes(msg);
        return 0;
    }
    else if(msg->pack == SETPWMX && (msg->data >= 1 && msg->data <= 10))
    {
        SendGoodAnsMes(msg);
        return 0;
    }
    else
    {
        SendFailAnsMes(msg);
        return 1;
    }

}
