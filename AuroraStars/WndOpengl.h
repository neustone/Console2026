#pragma once
#include "WndAurora.h"

class CWndOpengl : public CWndAurora
{
public:
	enum WND_STYLE_
	{
		WND_STYLE_3D = 0,
		WND_STYLE_TRANSVERSAL,
		WND_STYLE_SAGITTAL,
		WND_STYLE_CORONAL,
	};
	CWndOpengl(WND_STYLE_ wndStyle);
	virtual ~CWndOpengl(void);

protected:
	WND_STYLE_ m_wndStyle;
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

