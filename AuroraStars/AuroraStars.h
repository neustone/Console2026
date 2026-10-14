
// AuroraStars.h : main header file for the AuroraStars application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CAuroraStarsApp:
// See AuroraStars.cpp for the implementation of this class
//

class CAuroraStarsApp : public CWinApp
{
public:
	CAuroraStarsApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CAuroraStarsApp theApp;
