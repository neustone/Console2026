#pragma once
#include "WndAurora.h"

class CWndCoverPage : public CWndAurora
{
public:
	CWndCoverPage();
	virtual ~CWndCoverPage();

protected:
	CBitmap m_bmpLogo;

	virtual int onWndCreate();
	virtual void onWndDestroy();
	virtual int onWndRender(CDC* pDC);
	virtual void onWndSize(UINT nType, int cx, int cy);
	virtual void onLButtonDown(UINT nFlags, int x, int y);
	virtual void onLButtonUp(UINT nFlags, int x, int y);
	virtual void onLButtonDblClk(UINT nFlags, int x, int y);
};

