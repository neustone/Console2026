
// SciexMonitorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SciexMonitor.h"
#include "SciexMonitorDlg.h"
#include "SciexThread.h"
#include <time.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

////////////////////////////////////////////////////////

class CThreadFridge : public CSciexThread
{
protected:
	virtual DWORD run(LPVOID arg)
	{
		DWORD dwRet = 0;
		CSciexFridge* pSciexFridge = reinterpret_cast<CSciexFridge*>(arg);
//		CSciexFridge* pSciexFridge = (CSciexFridge*)(arg);
		if (pSciexFridge)
		{
			dwRet = pSciexFridge->interactWithPump();
		}
		return dwRet;
	}

};

////////////////////////////////////////////////////////

// CSciexMonitorDlg dialog

CSciexMonitorDlg::CSciexMonitorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSciexMonitorDlg::IDD, pParent)
	, m_pThreadIneract(new CThreadFridge)
	, m_Timer(0)
	, m_SciexFridge()
	, m_fTemperature(0.0f)
	, m_fTarget(10.0f)
	, m_tDoorOpen(time(0))
	, m_bDoorOpened(false)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	///.
	m_SciexFridge.setObserver(this);
}


void CSciexMonitorDlg::OnBnClickedButtonStart()
{
	DWORD dwRet = m_pThreadIneract->getExitCode();
	if (STILL_ACTIVE == dwRet)//(m_threadIneract.isRunning())
	{
		m_SciexFridge.setWorking(false);
		Sleep(500);
		dwRet = m_pThreadIneract->stop();
	}
	else
	{
		m_SciexFridge.setWorking(true);
		dwRet = m_pThreadIneract->start(&m_SciexFridge);
	}
}


void CSciexMonitorDlg::OnBnClickedButtonConfirm()
{
	UpdateData(TRUE);
	
	///. Allows user to setup target temperature
	m_SciexFridge.setTargetTemperature(m_fTarget);
	
	///. just for testing
	m_SciexFridge.m_fTemperature = m_fTarget;
}

int CSciexMonitorDlg::notify(CSciexMessage_ nMsg, long lData)
{
	int nError = 0;
	CWnd* pWnd = nullptr;
	switch (nMsg)
	{
	case CSciexMessage_Crash:
		///.
		break;
	case CSciexMessage_Temperature:
		m_fTemperature = lData/100.0f;
		break;
	case CSciexMessage_Door_Opened:
		///. Alarms user if fridge is open longer than a minute
		if (0 < lData && false==m_bDoorOpened)
		{
			///. turn on timer, and present;
			m_tDoorOpen = time(0);
			m_bDoorOpened = true;
		}
		else if (0 > lData)
		{
			///. turn off timer;
			m_bDoorOpened = false;
		}
		else
		{
			///. nothing
		}
		break;
	default:
		break;
	}
	return nError;
}

void CSciexMonitorDlg::OnTimer(UINT_PTR nIDEvent)
{
	//CTime t = CTime::GetCurrentTime();
	time_t tCurrent = time(0);
	bool bWorking = m_SciexFridge.isWorking();

	///. display door
	CWnd* pWnd = GetDlgItem(IDC_EDIT_FRIDGE_DOOR);
	if (pWnd && m_SciexFridge.isDoorOpened())
	{
		double fDoorOpened = difftime(tCurrent, m_tDoorOpen);
		CString str;
		str.Format(_T("%.2lf"), fDoorOpened);
		pWnd->SetWindowText(str);
	}

	///. Alarms user if fridge is open longer than a minute
	//After one minutue, we will start alarm
	pWnd = GetDlgItem(IDC_EDIT_FRIDGE_DATE);
	if (pWnd)
	{
		struct tm tmCurrent;
		localtime_s(&tmCurrent, &tCurrent);
		TCHAR buf[128] = {};
		// Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
		// for more information about date/time format
		_tcsftime(buf, sizeof(buf), _T("%Y-%m-%d.%X"), &tmCurrent);
		pWnd->SetWindowText(buf);
	}

	///. Displays current temperature in real time
	pWnd = GetDlgItem(IDC_EDIT_CURRENT_TEMPERATURE);
	ASSERT(pWnd);
	if (bWorking)
	{
		CString str;
		str.Format(_T("%.2f"), m_fTemperature);
		pWnd->SetWindowText(str);
	}
	else 
	{
		pWnd->SetWindowText(_T(""));
	}

	__super::OnTimer(nIDEvent);
}

void CSciexMonitorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_TARGET_TEMPERATURE, m_fTarget);
}


BEGIN_MESSAGE_MAP(CSciexMonitorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(ID_BUTTON_START, &CSciexMonitorDlg::OnBnClickedButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_CONFIRM, &CSciexMonitorDlg::OnBnClickedButtonConfirm)
	ON_WM_TIMER()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_OPEN_DOOR, &CSciexMonitorDlg::OnBnClickedButtonOpenDoor)
END_MESSAGE_MAP()


// CSciexMonitorDlg message handlers

BOOL CSciexMonitorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	m_Timer = CWnd::SetTimer(m_Timer, 500, nullptr); // one event every 500 ms

//	m_threadIneract.start();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSciexMonitorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
//		CAboutDlg dlgAbout;
//		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSciexMonitorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
		//CRect rect;
		//GetClientRect(rect);
		//dc.Draw3dRect(rect.left,);
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSciexMonitorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CSciexMonitorDlg::OnClose()
{
	if (m_pThreadIneract)
	{
		delete m_pThreadIneract;
		m_pThreadIneract = nullptr;
	}
	if (m_Timer)
	{
		CWnd::KillTimer(m_Timer);
		m_Timer = 0;
	}

	///.
	__super::OnClose();
}


void CSciexMonitorDlg::OnBnClickedButtonOpenDoor()
{
	// TODO: Add your control notification handler code here

	///. Just for test 
	m_SciexFridge.m_bDoorOpened = ! m_SciexFridge.m_bDoorOpened;
}
