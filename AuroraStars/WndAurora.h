
// WndAurora.h : interface of the CWndAurora class
//
#pragma once

// CWndAurora window
class CWndAurora : public CWnd
{
public:
	CWndAurora();
	virtual ~CWndAurora();
	int render();
	void getClientRect(CRect& clientRect);
	CDC* getClientDC();

	bool createWnd(CWnd* pParent, UINT nID = 0);
	void destroyWnd();
	bool showWnd(bool bShown);
	void moveWnd(int x, int y, int nWidth, int nHeight, bool bRepaint);
	void setWndFocus();
	int sendMessage(WPARAM wParam = 0, LPARAM lParam = 0);
	int postMessage(WPARAM wParam = 0, LPARAM lParam = 0);

protected:

	CClientDC* m_pClientDC = nullptr;
	/// The coordinates of a window's client area
	CRect m_rtClient;
	/// The color of background, edge, title and value
	COLORREF m_rgbBkColor, m_rgbRectColor, m_rgbItemTitle, m_rgbItemValue;
	/// The font property
	CString m_strFont;

	virtual int onWndCreate();
	virtual void onWndDestroy();
	virtual void onWndSize(UINT nType, int cx, int cy);
	virtual int onWndRender(CDC* pDC);
	virtual int onMsgWndRequest(WPARAM wParam, LPARAM lParam);
	virtual void onLButtonDown(UINT nFlags, int x, int y);
	virtual void onLButtonUp(UINT nFlags, int x, int y);
	virtual void onLButtonDblClk(UINT nFlags, int x, int y);

	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//{{AFX_MSG(CWndAbaris)	
	afx_msg LRESULT OnMsgWndRequest(WPARAM wParam, LPARAM lParam);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	DECLARE_DYNAMIC(CWndAurora)
public:
};

//
//class CWndAurora : public CWnd
//{
//public:
//	CWndAurora();
//	virtual ~CWndAurora();
//
//
//protected:
//
//

//
//	// Generated message map functions
//	//{{AFX_MSG(CWndAbaris)	
//	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
//	afx_msg void OnDestroy();
//	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
//	afx_msg void OnPaint();
//	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
//	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
//	afx_msg void OnSize(UINT nType, int cx, int cy);
//	//}}AFX_MSG
//public:
//};
//
