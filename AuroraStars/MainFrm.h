
// MainFrm.h : interface of the CMainFrame class
//

#pragma once

class CWndAurora;
class CMainFrame : public CFrameWnd
{
	
public:
	CMainFrame() noexcept;
	virtual ~CMainFrame();

	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	const static UINT32 nNumOfViews = 4;
	CWndAurora* m_pWndViews[nNumOfViews];

	//////////////////////////////////////////////////////////////////////////

	void onCleanUp();

	// virtual functions
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);

	// Generated message map functions
	afx_msg LRESULT OnMsgWndAurora(WPARAM wParam, LPARAM lParam);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();

	DECLARE_MESSAGE_MAP()
	DECLARE_DYNAMIC(CMainFrame)

};


