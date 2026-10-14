#pragma once
#include "WndAurora.h"

class CWndCoverPage : public CWndAurora
{
public:
	CWndCoverPage();
	virtual ~CWndCoverPage();

protected:
	CBitmap m_bmpLogo;

	virtual int onWndRender(CDC* pDC);
	virtual void onLButtonDown(UINT nFlags, int x, int y);
	virtual void onLButtonUp(UINT nFlags, int x, int y);
	virtual void onWndDestroy();
	virtual int onWndCreate();
};

