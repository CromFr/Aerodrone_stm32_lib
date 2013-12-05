#ifndef STM32LIB_HPP_INCLUDED
#define STM32LIB_HPP_INCLUDED

//#include "Vector3D.hpp"
#include <stm32f4xx.h>
#include <stm32f4xx_gpio.h>
#include <stm32f4xx_rcc.h>
#include <stm32f4xx_tim.h>
#include <stm32f4_discovery_lis302dl.h>

#include "Vector3D.hpp"


#include <utility>
typedef std::pair<GPIO_TypeDef*, unsigned short> Pin;





class STM32
{
public://Existing pins
	static constexpr Pin PinMotor0={GPIOE, 0};
	static constexpr Pin PinMotor1={GPIOE, 1};
	static constexpr Pin PinMotor2={GPIOE, 2};
	static constexpr Pin PinMotor3={GPIOE, 3};
	static constexpr Pin PinLedGreen={GPIOD, 12};
	static constexpr Pin PinLedOrange={GPIOD, 13};
	static constexpr Pin PinLedRed={GPIOD, 14};
	static constexpr Pin PinLedBlue={GPIOD, 15};
	static constexpr Pin PinButton={GPIOA, 0};
private://Pinout
	STM32()
	{
		SystemInit();

		//Start clocks for GPIO
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);

		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);

		SetPinType(PinLedBlue, DigitalOutput);
		SetPinType(PinLedGreen, DigitalOutput);
		SetPinType(PinLedOrange, DigitalOutput);
		SetPinType(PinLedRed, DigitalOutput);
		SetPinType(PinButton, DigitalInput);

		InitAccelero();
		InitTim1PWM();
	}


public:
	/**
	@brief Returns the current instance of the class
	**/
	static STM32* Get()
	{
		static STM32* inst = nullptr;
		if(inst==nullptr)
			inst = new STM32;
		return inst;
	}

	enum PinType
	{
		DigitalOutput,
		DigitalInput,
		Analog,
		Special
	};

	/**
	@brief Sets the type of the pin
	@param type DigitalOutput, DigitalInput, Analog or Special
	**/
	void SetPinType(const Pin& pin, PinType type);

	/**
	@brief Reads the value of one pin
	**/
	bool GetPinDigitalValue(const Pin& pin)
	{
		return (pin.first->IDR & (0b1 << pin.second))>0;
	}

	/**
	@brief Sets the value of one pin
	**/
	void SetPinDigitalValue(const Pin& pin, bool val)
	{
		if(val==true)
			pin.first->BSRRL = 0b1<<pin.second;
		else
			pin.first->BSRRH = 0b1<<pin.second;
	}

	/**
	@brief Work for some milliseconds
	**/
	void WorkForMS(const uint32_t& ms)
	{
		for(uint32_t i=0 ; i<ms*2700 ; i++);
	}

	/**
	@brief Play a given code using leds
	@param cCode Succession of r, g, b, o to light red, green, blue and orange leds
	**/
	void PlayCode(const char* cCode);

	/**
	@brief Infinitly loop on playing given code using leds
	@param cCode Succession of r, g, b, o to light red, green, blue and orange leds
	**/
	void ExitWithCode(const char* cCode);

	/**
	@brief Returns the value of the accelerometer in a 3d vector. The values goes from -128 to +128
	**/
	Vector3D<int8_t> GetAccelerometerValue()
	{
		Vector3D<int8_t> vRet;
		LIS302DL_Read((uint8_t*)&vRet.x, LIS302DL_OUT_X_ADDR, 1);
		LIS302DL_Read((uint8_t*)&vRet.y, LIS302DL_OUT_Y_ADDR, 1);
		LIS302DL_Read((uint8_t*)&vRet.z, LIS302DL_OUT_Z_ADDR, 1);
		return vRet;
	}

	void SetTim1PWM(int nChannel, float fDutyCycle)
	{
		switch(nChannel)
		{
			case 1: TIM_SetCompare1(TIM1, 200*(1.0-fDutyCycle)); return;
			case 2: TIM_SetCompare2(TIM1, 200*(1.0-fDutyCycle)); return;
			case 3: TIM_SetCompare3(TIM1, 200*(1.0-fDutyCycle)); return;
			case 4: TIM_SetCompare4(TIM1, 200*(1.0-fDutyCycle)); return;
		}
	}

private:
	void InitAccelero();
	void InitTim1PWM();

};





#endif // STM32LIB_HPP_INCLUDED
