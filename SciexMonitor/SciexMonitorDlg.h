
// SciexMonitorDlg.h : header file
//

#pragma once

#include "SciexFridge.h"

// CSciexMonitorDlg dialog
class CSciexThread;
class CSciexMonitorDlg : public CDialogEx, CObserver
{
public:
	CSciexMonitorDlg(CWnd* pParent = NULL);	// standard constructor

	virtual int notify(CSciexMessage_ nMsg, long lData);

protected:

	///. Interacts with heat pump to control the temperature inside the fridge
	CSciexThread* m_pThreadIneract;
	UINT_PTR m_Timer;

	///. Sciex Fridge
	CSciexFridge m_SciexFridge;
	float m_fTemperature, m_fTarget;
	time_t m_tDoorOpen;
	bool m_bDoorOpened;

	///.
	HICON m_hIcon;
	enum { IDD = IDD_SCIEXMONITOR_DIALOG };

	/////////////////////////////////////////////////

	// Generated message map functions
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual BOOL OnInitDialog();
	///.
	afx_msg void OnBnClickedButtonStart();
	afx_msg void OnBnClickedButtonConfirm();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnClose();
	///.
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedButtonOpenDoor();
};
