#pragma once

enum CSciexMessage_
{
	CSciexMessage_Unknown = 0,
	CSciexMessage_Initialize,
	CSciexMessage_Target_Temperature,
	CSciexMessage_Temperature,
	CSciexMessage_Door_Opened,
	CSciexMessage_Crash,
};

class CObserver
{
public:
	CObserver() {};
	~CObserver() {};
	virtual int notify(CSciexMessage_ nMsg, long lData) = 0;

};

class CSciexFridge
{
public:
	CSciexFridge(void);
	virtual ~CSciexFridge(void);
	void setObserver(CObserver* pObserver);
	int turnOn();

	///. Target Temperature
	void setTargetTemperature(long lTemperature);
	long getTargetTemperature()const;
	///.
	bool isDoorOpened()const;
	long getCurrentTemperature()const;

	///. 
	void setWorking(bool bWorking);
	bool isWorking()const;
//	int interactWithPump();

protected:

	///. Fridge status
	bool m_bInitialized, m_bWorking, m_bDoorOpened;
	long m_lTemperature, m_lTargetTemperature;
	///.
	CObserver* m_pObserver;

};

//extern void threadInteractWithPump(CSciexFridge* pSciexFridge);