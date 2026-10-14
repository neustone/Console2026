#pragma once

class CSciexThread
{
	/*
	*	Info: Thread Context Inner Class
	*	
	*	Every thread object needs to be associated with a set of values.
	*	like UserData Pointer, Handle, Thread ID etc.
	*  
	*  NOTE: This class can be enhanced to varying functionalities
	*		  eg.,
	*				* Members to hold StackSize
	*				* SECURITY_ATTRIBUTES member.
	*/
	class CThreadContext
	{
	public:
		CThreadContext()
			:m_hThread(0)
			,m_dwTID(0)
			,m_pUserData(NULL)
			,m_pParent(NULL)
			,m_dwExitCode(0)
		{
		}

		/*
		*	Attributes Section
		*/
	public:
		HANDLE m_hThread;	//	The Thread Handle
		DWORD  m_dwTID;		//	The Thread ID
		LPVOID m_pUserData;	//	The user data pointer
		LPVOID m_pParent;	//	The this pointer of the parent CThread object
		DWORD  m_dwExitCode;//	The Exit Code of the thread
	};

public:

	CSciexThread(void);
	virtual ~CSciexThread(void);
	bool isRunning()const;

	// Info: Starts the thread.
	// This function starts the thread pointed by m_pThreadFunc
	// with default attributes
	DWORD start(void* arg = nullptr);
	// Info: Stops the thread.
	// This function stops the current thread. 
	// We can force kill a thread which results in a TerminateThread.
	DWORD stop(bool bForceKill = false);
	// Info: get the code of exit.
	DWORD getExitCode() const ;

//	LPVOID GetUserData();

protected:

	///. Info: Members of CThread
	CThreadContext m_ThreadCtx;				// The Thread Context member
	LPTHREAD_START_ROUTINE	m_pThreadFunc;	// The Worker Thread Function Pointer
	
	///. true when working thread function run(...) is performing.
	bool m_bRunning;

	/////////////////////////////////////////
	
	// Info: Override this method.
	// This function should contain the body/code of your thread.
	// Notice the signature is similar to that of any worker thread function
	// except for the calling convention.
	virtual DWORD run(LPVOID arg) = 0;

	// Info: DONT override this method.
	// This function is like a standard template. 
	// Override if you are sure of what you are doing.
	static DWORD WINAPI EntryPoint(LPVOID pArg);

};

