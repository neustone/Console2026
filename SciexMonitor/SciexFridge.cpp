#include "StdAfx.h"
#include "SciexFridge.h"
//
//void threadInteractWithPump(CSciexFridge* pSciexFridge)
//{
//	if (pSciexFridge)
//		pSciexFridge->interactWithPump();
//}


///////////////////////////////////////


CSciexFridge::CSciexFridge(void)
	: m_bInitialized(false)
	, m_bWorking(false)
	, m_bDoorOpened(false)
	, m_fTemperature(0.00f)
	, m_pObserver(nullptr)
{
	initialize();
}


CSciexFridge::~CSciexFridge(void)
{
	release();
}

int CSciexFridge::initialize()
{
	return 0;
}

void CSciexFridge::release()
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

float CSciexFridge::getCurrentTemperature()const
{
	///. Displays current temperature
	return m_fTemperature;
}

void CSciexFridge::setTargetTemperature(float fTemperature)
{
	///. Allows user to setup target temperature of Sciex Fridge
	m_fTargetTemperature = fTemperature;
}

float CSciexFridge::getTargetTemperature()const
{
	return m_fTargetTemperature;
}

bool CSciexFridge::isDoorOpened()const
{
	///. get door status from Sciex Fridge
	return m_bDoorOpened;
}

///.
int CSciexFridge::interactWithPump()
{
	int nError = 0;
	while (m_bWorking) 
	{
		try
		{
			//. check if power is off
//			m_bWorking =false;
//			if (m_pObserver && m_bWorking)
//				m_pObserver->notify(CSciexMessage_Crash, fTemp);

			///. Displays current temperature
			long lTemp = (long)(getCurrentTemperature()*100);
			if (m_pObserver && m_bWorking)
				m_pObserver->notify(CSciexMessage_Temperature, lTemp);

			///. Alarms user if fridge is open longer than a minute
			bool bDoorOpened = isDoorOpened();
			if (m_pObserver && m_bWorking)
				m_pObserver->notify(CSciexMessage_Door_Opened, bDoorOpened? 1 : -1);

			Sleep(500);
		}
		catch (...)
		{
			if (m_pObserver && m_bWorking)
				m_pObserver->notify(CSciexMessage_Crash, nError);
		}

	}///. end of while (m_bWorking)
	
	///.
//	m_bWorking = false;
	return 0l;
}
