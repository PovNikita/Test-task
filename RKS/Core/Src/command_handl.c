#include "command_handl.h"

uint32_t SetPin(uint8_t *data)
{
	if(*data == 11)
	{
		//Set
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, SET);
	}
	else
	{
		//Reset
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, RESET);
	}
	return 0;
}
uint32_t SetPWM(uint8_t *data)
{
	if(*data == 3)
	{
		HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
		HAL_Delay(50);
		HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_2);
	}
	else if (*data == 7)
	{
		HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
		HAL_Delay(100);
		HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_2);
	}

	return 0;
}
uint32_t SetPWMX(uint8_t *data)
{
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
	HAL_Delay(50 * (*data));
	HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_1);
	return 0;
}
