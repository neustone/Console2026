#include "SciexFridge.h"

#include <iostream>
//#include <chrono>
//#include <thread>

CSciexFridge::CSciexFridge(void)
	: m_bInitialized(false)
	, m_bWorking(false)
	, m_bDoorOpened(false)
	, m_lTemperature(0)
	, m_lTargetTemperature(0)
	, m_pObserver(nullptr)
{
}


CSciexFridge::~CSciexFridge(void)
{
}

void CSciexFridge::setWorking(bool bWorking)
{
	m_bWorking = bWorking;
}

bool CSciexFridge::isWorking()const
{
	return m_bWorking;
}

void CSciexFridge::setObserver(CObserver* pObserver)
{
	m_pObserver = pObserver;
}

long CSciexFridge::getCurrentTemperature()const
{
	///. Displays current temperature
	return m_lTemperature;
}

void CSciexFridge::setTargetTemperature(long lTemperature)
{
	///. Allows user to setup target temperature of Sciex Fridge
	m_lTargetTemperature = lTemperature;
}

long CSciexFridge::getTargetTemperature()const
{
	return m_lTargetTemperature;
}

bool CSciexFridge::isDoorOpened()const
{
	///. get door status from Sciex Fridge
	return m_bDoorOpened;
}

/////.
//int CSciexFridge::interactWithPump()
//{
//	int nError = 0;
//	while (m_bWorking)
//	{
//		try
//		{
//			//. check if power is off
////			m_bWorking =false;
////			if (m_pObserver && m_bWorking)
////				m_pObserver->notify(CSciexMessage_Crash, fTemp);
//
//			///. Displays current temperature
//			long lTemp = (long)(getCurrentTemperature() * 100);
//			if (m_pObserver && m_bWorking)
//				m_pObserver->notify(CSciexMessage_Temperature, lTemp);
//
//			///. Alarms user if fridge is open longer than a minute
//			bool bDoorOpened = isDoorOpened();
//			if (m_pObserver && m_bWorking)
//				m_pObserver->notify(CSciexMessage_Door_Opened, bDoorOpened ? 1 : -1);
//
////			//Sleep(500);
////			std::this_thread::sleep_for(std::chrono::milliseconds(500));
//		}
//		catch (...)
//		{
//			if (m_pObserver && m_bWorking)
//				m_pObserver->notify(CSciexMessage_Crash, nError);
//		}
//
//	}///. end of while (m_bWorking)
//
//	///.
////	m_bWorking = false;
//	return 0l;
//}

int CSciexFridge::turnOn()
{
	int nRet = 0, nCmd = 0;
	if (m_pObserver)
	{
		m_pObserver->notify(CSciexMessage_Initialize, 0);
//		m_pObserver->notify(CSciexMessage_Target_Temperature, (long)(m_fTargetTemperature * 100));
//		m_pObserver->notify(CSciexMessage_Temperature, (long)(m_fTargetTemperature * 100));
//		m_pObserver->notify(CSciexMessage_Door_Opened, m_bDoorOpened ? 1 : -1);
	}

	bool bContinue = true;
	do
	{
		std::cin >> nCmd;
		switch (nCmd)
		{
		case 0:
			bContinue = false;
			break;
		case 1:
			m_lTemperature += 1;
			if (m_pObserver)
				m_pObserver->notify(CSciexMessage_Temperature, m_lTemperature);
			break;
		case 2:
			m_lTemperature -= 1;
			if (m_pObserver)
				m_pObserver->notify(CSciexMessage_Temperature, m_lTemperature);
			break;
		case 3:
			m_lTargetTemperature += 1;
			if (m_pObserver)
				m_pObserver->notify(CSciexMessage_Target_Temperature, m_lTargetTemperature);
			break;
		case 4:
			m_lTargetTemperature -= 1;
			if (m_pObserver)
				m_pObserver->notify(CSciexMessage_Target_Temperature, m_lTargetTemperature);
			break;
		case 5:
			m_bDoorOpened = !m_bDoorOpened;
			if (m_pObserver)
				m_pObserver->notify(CSciexMessage_Door_Opened, m_bDoorOpened ? 1 : -1);
			break;
		default:
			break;
		} //end of switch( nCmd )

	} while (bContinue);

//	system("pause");
	return nRet;
}
