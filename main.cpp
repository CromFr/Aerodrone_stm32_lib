#include <optimizecpp.cpp>
#include "STM32Lib.hpp"
#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>

void BlinkBlue(void* param)
{
	while(1)
	{
		STM32::Get()->SetPinDigitalValue(STM32::PinLedBlue, true);
		vTaskDelay(500);
		STM32::Get()->SetPinDigitalValue(STM32::PinLedBlue, false);
		vTaskDelay(500);
	}
	vTaskDelete(0);
}
void BlinkRed(void* param)
{
	vTaskDelay(250);
	while(1)
	{
		STM32::Get()->SetPinDigitalValue(STM32::PinLedRed, true);
		vTaskDelay(500);
		STM32::Get()->SetPinDigitalValue(STM32::PinLedRed, false);
		vTaskDelay(500);
	}
	vTaskDelete(0);
}

int main(void)
{
	STM32* stm = STM32::Get();

	xTaskCreate(BlinkBlue, (const signed char*)"Coucou", 240, nullptr, 1, NULL);
	xTaskCreate(BlinkRed, (const signed char*)"Coucou", 240, nullptr, 1, NULL);

	vTaskStartScheduler();

	while(1);
}



















