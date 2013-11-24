#ifndef STM32LIB_HPP_INCLUDED
#define STM32LIB_HPP_INCLUDED

//#include "Vector3D.hpp"
#include <stm32f4xx.h>
#include <stm32f4xx_gpio.h>
#include <stm32f4xx_rcc.h>
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

		SetPinType(PinLedBlue, DigitalOutput);
		SetPinType(PinLedGreen, DigitalOutput);
		SetPinType(PinLedOrange, DigitalOutput);
		SetPinType(PinLedRed, DigitalOutput);
		SetPinType(PinButton, DigitalInput);

		//Accelerometer init
		LIS302DL_InitTypeDef inittype;
		inittype.Power_Mode = LIS302DL_LOWPOWERMODE_ACTIVE;
		inittype.Output_DataRate = LIS302DL_DATARATE_400;
		inittype.Axes_Enable = LIS302DL_XYZ_ENABLE;
		inittype.Full_Scale = LIS302DL_FULLSCALE_2_3;
		inittype.Self_Test = LIS302DL_SELFTEST_NORMAL;
		LIS302DL_Init(&inittype);
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
	bool GetPinDigitalValue(const Pin& pin);

	/**
	@brief Sets the value of one pin
	**/
	void SetPinDigitalValue(const Pin& pin, bool val);

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
	Vector3D<int8_t> GetAccelerometerValue();

private:


};




// http://hertaville.com/2012/07/28/stm32f0-gpio-tutorial-part-1/








#endif // STM32LIB_HPP_INCLUDED
