//#include <optimizecpp.cpp>
//
//#include "STM32Lib.hpp"
//
////	B
////R		G
////	O
//
//int main()
//{
//	STM32* stm = STM32::Get();
//	stm->SetPinDigitalValue(STM32::PinLedGreen, true);
//	stm->SetPinDigitalValue(STM32::PinLedBlue, true);
//	stm->SetPinDigitalValue(STM32::PinLedOrange, true);
//	stm->SetPinDigitalValue(STM32::PinLedRed, true);
//
////	while(1){
////		if(stm->GetPinDigitalValue(STM32::PinButton))
////			stm->SetPinDigitalValue(STM32::PinLedGreen, true);
////		else
////			stm->SetPinDigitalValue(STM32::PinLedGreen, false);
////
////	}
////	stm->ExitWithCode("rgboobgr");
//	return 0;
//}

//#include <optimizecpp.cpp>
//
//#include "STM32Lib.hpp"
//
//#include <stm32f4xx.h>
//#include <stm32f4xx_gpio.h>
//#include <stm32f4xx_rcc.h>
//#include <stm32f4xx_spi.h>
//int main(void)
//
//
//{
//		//STM32* stm = STM32::Get();
//
//		SystemInit();
//
//        GPIO_InitTypeDef GPIO_InitStructure;
//        SPI_InitTypeDef  SPI_InitStructure;
//
//        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD | RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOE , ENABLE);
//        RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
//
//
//          //Init SPI-Pins
//          GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
//          GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
//          GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//          GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//          GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
//          GPIO_Init(GPIOA, &GPIO_InitStructure);
//          //Init CS-Pin
//          GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
//          GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
//          GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//          GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//          GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
//          GPIO_Init(GPIOE, &GPIO_InitStructure);
//
//          GPIO_SetBits(GPIOE, GPIO_Pin_3);  //Set CS high
//
//
//          GPIO_PinAFConfig (GPIOA, GPIO_PinSource5 , GPIO_AF_SPI1);
//          GPIO_PinAFConfig (GPIOA, GPIO_PinSource6 , GPIO_AF_SPI1);
//          GPIO_PinAFConfig (GPIOA, GPIO_PinSource7 , GPIO_AF_SPI1);
//
//
//          SPI_I2S_DeInit(SPI1);
//          SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
//          SPI_InitStructure.SPI_Mode = SPI_Mode_Master ;
//          SPI_InitStructure.SPI_DataSize = SPI_DataSize_16b ;
//          SPI_InitStructure.SPI_CPOL = SPI_CPOL_High    ;
//          SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
//          SPI_InitStructure.SPI_NSS = SPI_NSS_Soft ;
//          SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_32;
//          SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
//          SPI_InitStructure.SPI_CRCPolynomial = 0;
//          SPI_Init(SPI1, &SPI_InitStructure);
//
//
//
//          SPI_Cmd(SPI1, ENABLE);
//
//          GPIO_ResetBits(GPIOE, GPIO_Pin_3);
//
//
//          SPI_I2S_SendData(SPI1, 0x20C7);    //Sensor Config
//
//
//	uint16_t y=0;
//    while(1){
//        //Read Y-Axis
//        SPI_I2S_SendData(SPI1, 0xAB00);
//        y = SPI_I2S_ReceiveData(SPI1);
//
//        //stm->SetPinDigitalValue(stm->LedBlue, (y==0));
//    }
//}

#include <optimizecpp.cpp>

#include "STM32Lib.hpp"

int main()
{
	STM32* stm = STM32::Get();


	while(1)
	{
		Vector3D<int8_t> vAcc(stm->GetAccelerometerValue());



		if(vAcc.x>0)
		{
			stm->SetPinDigitalValue(STM32::PinLedBlue, true);
			stm->SetPinDigitalValue(STM32::PinLedOrange, false);
		}
		else if(vAcc.x<0)
		{
			stm->SetPinDigitalValue(STM32::PinLedBlue, false);
			stm->SetPinDigitalValue(STM32::PinLedOrange, true);
		}
		else
		{
			stm->SetPinDigitalValue(STM32::PinLedBlue, false);
			stm->SetPinDigitalValue(STM32::PinLedOrange, false);
		}


		if(vAcc.y>0)
		{
			stm->SetPinDigitalValue(STM32::PinLedRed, true);
			stm->SetPinDigitalValue(STM32::PinLedGreen, false);
		}
		else if(vAcc.y<0)
		{
			stm->SetPinDigitalValue(STM32::PinLedRed, false);
			stm->SetPinDigitalValue(STM32::PinLedGreen, true);
		}
		else
		{
			stm->SetPinDigitalValue(STM32::PinLedRed, false);
			stm->SetPinDigitalValue(STM32::PinLedGreen, false);
		}
	}


}
