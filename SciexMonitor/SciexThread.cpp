#include "StdAfx.h"
#include "SciexThread.h"


CSciexThread::CSciexThread(void)
	: m_ThreadCtx()
	, m_pThreadFunc(CSciexThread::EntryPoint)
	, m_bRunning(false)
{
}


CSciexThread::~CSciexThread(void)
{
	stop(true);
}

bool CSciexThread::isRunning()const
{
	return m_bRunning;
}

DWORD CSciexThread::start(void* arg)
{
	m_ThreadCtx.m_pUserData = arg;
	m_ThreadCtx.m_hThread = CreateThread(
		NULL, 0, m_pThreadFunc, this, 0, &m_ThreadCtx.m_dwTID);
	m_ThreadCtx.m_dwExitCode = (DWORD)-1;

	return GetLastError();

}

DWORD CSciexThread::stop(bool bForceKill)
{
	const DWORD dwCode = CSciexThread::getExitCode();
	if (STILL_ACTIVE == dwCode && bForceKill )
	{
		TerminateThread(m_ThreadCtx.m_hThread, DWORD(-1));
	}

	m_ThreadCtx.m_hThread = NULL;
	m_ThreadCtx.m_dwExitCode = 0;

	return dwCode;
}

DWORD CSciexThread::getExitCode() const 
{ 
	if (m_ThreadCtx.m_hThread)
	{
		GetExitCodeThread(
			m_ThreadCtx.m_hThread, (LPDWORD)&m_ThreadCtx.m_dwExitCode);
	}
	return m_ThreadCtx.m_dwExitCode;
}

//LPVOID CSciexThread::GetUserData()
//{
//	return m_ThreadCtx.m_pUserData;
//}

DWORD WINAPI CSciexThread::EntryPoint(LPVOID pArg)
{
	CSciexThread* pParent = reinterpret_cast<CSciexThread*>(pArg);

	pParent->m_bRunning = true;
	pParent->run(
		pParent->m_ThreadCtx.m_pUserData);
	pParent->m_bRunning = false;

	return STILL_ACTIVE;
}
