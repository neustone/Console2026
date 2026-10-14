#pragma once

enum CSciexMessage_
{
	CSciexMessage_Unknown = 0,
	CSciexMessage_Temperature,
	CSciexMessage_Door_Opened,
	CSciexMessage_Crash,
};

class CObserver
{
public:
	CObserver(){};
	~CObserver(){};
	virtual int notify(CSciexMessage_ nMsg, long lData) = 0;

};

class CSciexFridge
{
//#ifdef _DEBUG
	friend class CSciexMonitorDlg;
//#endif

public:
	CSciexFridge(void);
	virtual ~CSciexFridge(void);
	void setObserver(CObserver* pObserver);
	///. 
	///. Target Temperature
	void setTargetTemperature(float fTemperature);
	float getTargetTemperature()const;
	///.
	bool isDoorOpened()const;
	float getCurrentTemperature()const;

	///. 
	void setWorking(bool bWorking);
	bool isWorking()const;
	int interactWithPump();

protected:

	///. Fridge status
	bool m_bInitialized, m_bWorking, m_bDoorOpened;
	float m_fTemperature, m_fTargetTemperature;
	///.
	CObserver* m_pObserver;

	///////////////////////////////////

	///. set up the fridge
	int initialize();
	///. have the fridge released;
	void release();
};

//extern void threadInteractWithPump(CSciexFridge* pSciexFridge);