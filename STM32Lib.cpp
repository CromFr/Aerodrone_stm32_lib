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
			break;

		case DigitalOutput:
			//Init output
			GPIO_InitStruct.GPIO_Pin = 0b1 << pin.second;
			GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
			GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
			GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
			GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
			GPIO_Init(pin.first, &GPIO_InitStruct);
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
	}
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





void STM32::InitAccelero()
{
	//Accelerometer init
	LIS302DL_InitTypeDef inittype;
	inittype.Power_Mode = LIS302DL_LOWPOWERMODE_ACTIVE;
	inittype.Output_DataRate = LIS302DL_DATARATE_400;
	inittype.Axes_Enable = LIS302DL_XYZ_ENABLE;
	inittype.Full_Scale = LIS302DL_FULLSCALE_2_3;
	inittype.Self_Test = LIS302DL_SELFTEST_NORMAL;
	LIS302DL_Init(&inittype);
}

void STM32::InitTim1PWM()
{
	constexpr TIM_TypeDef* tim = TIM1;

	//Init pins to AF
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = (GPIO_Pin_9 | GPIO_Pin_11 | GPIO_Pin_13 | GPIO_Pin_14);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
	GPIO_Init(GPIOE, &GPIO_InitStructure);

	// Connect TIM1 pins to AF
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource9,  GPIO_AF_TIM1);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource11, GPIO_AF_TIM1);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource13, GPIO_AF_TIM1);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource14, GPIO_AF_TIM1);

	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;


	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	TIM_TimeBaseStructure.TIM_Period = (200-1);
	TIM_TimeBaseStructure.TIM_Prescaler = (42000-1);
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(tim, &TIM_TimeBaseStructure);

	/* PWM1 Mode configuration: Channel1 */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

	TIM_OC1Init(tim, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(tim, TIM_OCPreload_Enable);

	/* PWM1 Mode configuration: Channel2 */
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OC2Init(tim, &TIM_OCInitStructure);

	TIM_OC2PreloadConfig(tim, TIM_OCPreload_Enable);

	/* PWM1 Mode configuration: Channel3 */
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OC3Init(tim, &TIM_OCInitStructure);

	TIM_OC3PreloadConfig(tim, TIM_OCPreload_Enable);

	/* PWM1 Mode configuration: Channel4 */
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OC4Init(tim, &TIM_OCInitStructure);

	TIM_OC4PreloadConfig(tim, TIM_OCPreload_Enable);

	TIM_ARRPreloadConfig(tim, ENABLE);

	//required for timers 1 or 8
	TIM_CtrlPWMOutputs(tim, ENABLE);

	/* TIM1 enable counter */
	TIM_Cmd(tim, ENABLE);
}
