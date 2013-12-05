#include <optimizecpp.cpp>
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

//#include "STM32Lib.hpp"
//
//int main()
//{
//	STM32* stm = STM32::Get();
//
//	stm->PlayCode("rogb");
//	while(1)
//	{
//		Vector3D<int8_t> vAcc(stm->GetAccelerometerValue());
//
//
//		if(!stm->GetPinDigitalValue(STM32::PinButton))
//		{
//			if(vAcc.x>0)
//			{
//				stm->SetPinDigitalValue(STM32::PinLedBlue, true);
//				stm->SetPinDigitalValue(STM32::PinLedOrange, false);
//			}
//			else if(vAcc.x<0)
//			{
//				stm->SetPinDigitalValue(STM32::PinLedBlue, false);
//				stm->SetPinDigitalValue(STM32::PinLedOrange, true);
//			}
//			else
//			{
//				stm->SetPinDigitalValue(STM32::PinLedBlue, false);
//				stm->SetPinDigitalValue(STM32::PinLedOrange, false);
//			}
//
//			if(vAcc.y>0)
//			{
//				stm->SetPinDigitalValue(STM32::PinLedRed, true);
//				stm->SetPinDigitalValue(STM32::PinLedGreen, false);
//			}
//			else if(vAcc.y<0)
//			{
//				stm->SetPinDigitalValue(STM32::PinLedRed, false);
//				stm->SetPinDigitalValue(STM32::PinLedGreen, true);
//			}
//			else
//			{
//				stm->SetPinDigitalValue(STM32::PinLedRed, false);
//				stm->SetPinDigitalValue(STM32::PinLedGreen, false);
//			}
//		}
//		else
//		{
//			stm->SetPinDigitalValue(STM32::PinLedGreen, false);
//			stm->SetPinDigitalValue(STM32::PinLedRed, false);
//			if(vAcc.z>0)
//			{
//				stm->SetPinDigitalValue(STM32::PinLedBlue, true);
//				stm->SetPinDigitalValue(STM32::PinLedOrange, false);
//			}
//			else if(vAcc.z<0)
//			{
//				stm->SetPinDigitalValue(STM32::PinLedBlue, false);
//				stm->SetPinDigitalValue(STM32::PinLedOrange, true);
//			}
//			else
//			{
//				stm->SetPinDigitalValue(STM32::PinLedBlue, false);
//				stm->SetPinDigitalValue(STM32::PinLedOrange, false);
//			}
//
//		}
//	}
//	stm->ExitWithCode("ror");
//	return 0;
//}
//
//
#include "STM32Lib.hpp"

int main(void)
{
	STM32* stm = STM32::Get();
	stm->SetTim1PWM(1, 0.9);
	stm->SetTim1PWM(2, 0.6);
	stm->SetTim1PWM(3, 0.3);
	stm->SetTim1PWM(4, 0.1);
}



















