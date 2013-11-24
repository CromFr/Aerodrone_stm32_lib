#include "STM32Lib.hpp"

constexpr Pin STM32::PinMotor0;
constexpr Pin STM32::PinMotor1;
constexpr Pin STM32::PinMotor2;
constexpr Pin STM32::PinMotor3;
constexpr Pin STM32::PinLedGreen;
constexpr Pin STM32::PinLedOrange;
constexpr Pin STM32::PinLedRed;
constexpr Pin STM32::PinLedBlue;
constexpr Pin STM32::PinButton;


void STM32::SetPinType(const Pin& pin, PinType type)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	switch(type)
	{
		case DigitalInput:
			//Set Intput
			GPIO_InitStruct.GPIO_Pin = 0b1 << pin.second;
			GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
			GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
			GPIO_InitStruct.GPIO_OType = GPIO_OType_OD;
			GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN;
			GPIO_Init(pin.first, &GPIO_InitStruct);
//			pin.first->MODER &= ~((uint32_t)(0b11<<(pin.second*2)));//Set 00
//			//Set OpenDrain
//			pin.first->OTYPER |= ((uint16_t)(0b1<<(pin.second)));//Set 1
//			//Set medium speed
//			pin.first->OSPEEDR &= ~((uint32_t)(0b10<<(pin.second*2)));//Set 0x
//			pin.first->OSPEEDR |= ((uint32_t)(0b01<<(pin.second*2)));//Set x1
//			//Set PullDown
//			pin.first->PUPDR &= ~((uint32_t)(0b01<<(pin.second*2)));//Set x0
//			pin.first->PUPDR |= ((uint32_t)(0b10<<(pin.second*2)));//Set 1x
			break;

		case DigitalOutput:
			//Init output
			GPIO_InitStruct.GPIO_Pin = 0b1 << pin.second;
			GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
			GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
			GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
			GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
			GPIO_Init(pin.first, &GPIO_InitStruct);

//			//Init with manual register set
//			pin.first->MODER &= ~((uint32_t)(0b10<<(pin.second*2)));//Set 0x
//			pin.first->MODER |= ((uint32_t)(0b01<<(pin.second*2)));//Set x1
//			//Set push/pull
//			pin.first->OTYPER |= ~((uint16_t)(0b1<<(pin.second)));//Set 0
//			//Set medium speed
//			pin.first->OSPEEDR &= ~((uint32_t)(0b01<<(pin.second*2)));//Set x0
//			pin.first->OSPEEDR |= ((uint32_t)(0b10<<(pin.second*2)));//Set 1x
//			//Set no pullup/pulldown
//			pin.first->PUPDR &= ~((uint32_t)(0b11<<(pin.second*2)));//Set 00
			break;

		case Analog:
			//Set Analog
			pin.first->MODER |= ((uint32_t)(0b11<<(pin.second*2)));//Set 11
			//Set OpenDrain
			pin.first->OTYPER |= ((uint16_t)(0b1<<(pin.second)));//Set 1
			//Set medium speed
			pin.first->OSPEEDR &= ~((uint32_t)(0b10<<(pin.second*2)));//Set 0x
			pin.first->OSPEEDR |= ((uint32_t)(0b01<<(pin.second*2)));//Set x1
			//Set PullDown
			pin.first->PUPDR &= ~((uint32_t)(0b01<<(pin.second*2)));//Set x0
			pin.first->PUPDR |= ((uint32_t)(0b10<<(pin.second*2)));//Set 1x
			break;

		case Special:
			//Set Alternate
			pin.first->MODER &= ~((uint32_t)(0b01<<(pin.second*2)));//Set x0
			pin.first->MODER |= ((uint32_t)(0b10<<(pin.second*2)));//Set 1x
			//Set OpenDrain
			pin.first->OTYPER |= ((uint16_t)(0b1<<(pin.second)));//Set 1
			//Set medium speed
			pin.first->OSPEEDR &= ~((uint32_t)(0b10<<(pin.second*2)));//Set 0x
			pin.first->OSPEEDR |= ((uint32_t)(0b01<<(pin.second*2)));//Set x1
			//Set PullDown
			pin.first->PUPDR &= ~((uint32_t)(0b01<<(pin.second*2)));//Set x0
			pin.first->PUPDR |= ((uint32_t)(0b10<<(pin.second*2)));//Set 1x
			break;
//
//		case Spi:
//			static bool bSpiInit = false;
//			if(!bSpiInit)
//			{
//				bSpiInit=true;
//
//				//Init SPI-Pins
//				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
//				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
//				GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//				GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//				GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
//				GPIO_Init(GPIOA, &GPIO_InitStructure);
//				GPIO_PinAFConfig(GPIOA, GPIO_PinSource5 , GPIO_AF_SPI1);
//				GPIO_PinAFConfig(GPIOA, GPIO_PinSource6 , GPIO_AF_SPI1);
//				GPIO_PinAFConfig(GPIOA, GPIO_PinSource7 , GPIO_AF_SPI1);
//			}
//			GPIO_InitStructure.GPIO_Pin = 0b1 << pin.second;
//			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
//			GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//			GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
//			GPIO_Init(pin.first, &GPIO_InitStructure);
//			GPIO_SetBits(pin.first, pin.second);  //Set CS high
//
//			GPIO_PinAFConfig(pin.first, 0b1<<pin.second, GPIO_AF_SPI1);
//
//
//			break;
	}
}
bool STM32::GetPinDigitalValue(const Pin& pin)
{
	uint16_t valTrue = 0b1 << pin.second;

	return (pin.first->IDR & valTrue)>0;
}
void STM32::SetPinDigitalValue(const Pin& pin, bool val)
{
	if(val==true)
		pin.first->BSRRL = 0b1<<pin.second;
	else
		pin.first->BSRRH = 0b1<<pin.second;
}


void STM32::PlayCode(const char* cCode)
{
	for(int i=0 ; cCode[i]!=0 ; i++)
	{
		const Pin* p;
		switch(cCode[i])
		{
			case 'r': p=&PinLedRed;break;
			case 'g': p=&PinLedGreen;break;
			case 'b': p=&PinLedBlue;break;
			case 'o': p=&PinLedOrange;break;
		}
		SetPinDigitalValue(*p, true);
		WorkForMS(200);
		SetPinDigitalValue(*p, false);
		WorkForMS(100);

	}
}


void STM32::ExitWithCode(const char* cCode)
{
	while(true)
	{
		PlayCode(cCode);
		WorkForMS(300);
	}
}


Vector3D<int8_t> STM32::GetAccelerometerValue()
{
	uint8_t buf;
	Vector3D<int8_t> vRet;
	LIS302DL_Read(&buf, LIS302DL_OUT_X_ADDR, 1);
	vRet.x = buf;
	LIS302DL_Read(&buf, LIS302DL_OUT_Y_ADDR, 1);
	vRet.y = buf;
	LIS302DL_Read(&buf, LIS302DL_OUT_Z_ADDR, 1);
	vRet.z = buf;
	return vRet;
}
