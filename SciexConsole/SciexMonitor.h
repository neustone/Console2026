#pragma once
#include "SciexFridge.h"
#include <thread>

class CSciexFridge;
class CSciexMonitor : public CObserver
{
	std::thread* m_pThread;
	bool m_bRunning;
	CSciexFridge* m_pFridge;

//	bool m_bDoorOpened;
//	float m_fTemperature, m_fTargetTemperature;

public:
	CSciexMonitor();
	~CSciexMonitor();

	void setFridge(CSciexFridge* pFridge)
	{
		m_pFridge = pFridge;
	}

protected:
	virtual int notify(CSciexMessage_ nMsg, long lData);
	void updateData();

	static void startThread(CSciexMonitor* pt);
};

