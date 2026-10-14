#pragma once
#include "WndAurora.h"

class CWndOpengl : public CWndAurora
{
public:
	CWndOpengl();
	virtual ~CWndOpengl(void);

protected:
	///. Opengl
	HGLRC m_hRC;
	CRect m_rtViewPort;

	virtual int onWndCreate();
	virtual void onWndDestroy();
	virtual int onWndRender(CDC* pDC);
	virtual void onWndSize(UINT nType, int cx, int cy);

	/// <summary>
	///
	/// </summary>
	/// <returns></returns>
	int onInitializeOpengl();
	void onReleaseOpengl();
	void resetScene();

};

