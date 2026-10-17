
// MainFrm.cpp : implementation of the CMainFrame class
//

#include "pch.h"
#include "framework.h"
#include "AuroraStars.h"

#include "MainFrm.h"
#include "WndCoverPage.h"
#include "WndImage.h"
#include "WndOpengl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_MESSAGE(WM_WND_ABARIS_MESSAGE, OnMsgWndAurora)
	///.
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
	ON_WM_SIZE()
	ON_WM_DESTROY()
END_MESSAGE_MAP()

// CMainFrame construction/destruction

CMainFrame::CMainFrame() noexcept
	: CFrameWnd()
{
	for (UINT32 i = 0; i < nNumOfViews; ++ i)
		m_pWndViews[i] = nullptr;
}

CMainFrame::~CMainFrame()
{
	onCleanUp();
}

void CMainFrame::onCleanUp()
{
	for (UINT32 i = 0; i < nNumOfViews; ++i)
	{
		if (nullptr != m_pWndViews[i])
		{
			m_pWndViews[i]->destroyWnd();
			delete m_pWndViews[i];
			m_pWndViews[i] = nullptr;
		}
	}
}

LRESULT CMainFrame::OnMsgWndAurora(WPARAM wParam, LPARAM lParam)
{
	CWndAurora* pWndSrc = reinterpret_cast<CWndAurora*>(lParam);
	switch (wParam)
	{
	case CWndAurora::WND_MSG_UNKNOWN_:
		if (pWndSrc)
		{
			CWndAurora::messageBox(
				pWndSrc, L"CMainFrame::OnMsgWndAurora, 1", L"AuroraStars");
		}
		break;
	case CWndAurora::WND_MSG_EXIT_:
		OnClose();
		break;
	default:
		break;
	}
	return 0;
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// create a view to occupy the client area of the frame
	int i = 0;
	if (nullptr == m_pWndViews[i])
	{
		m_pWndViews[i] = new CWndCoverPage();
		m_pWndViews[i]->createWnd(this, i);
		m_pWndViews[i]->showWnd(true);
	}
	++ i;
	if (nullptr == m_pWndViews[i])
	{
		m_pWndViews[i] = new CWndImage();
		m_pWndViews[i]->createWnd(this, i);
		m_pWndViews[i]->showWnd(true);
	}
	++i;
	if (nullptr == m_pWndViews[i])
	{
		m_pWndViews[i] = new CWndOpengl();
		m_pWndViews[i]->createWnd(this, i);
		m_pWndViews[i]->showWnd(true);
	}
	++i;
	if (nullptr == m_pWndViews[i])
	{
		m_pWndViews[i] = new CWndAurora();
		m_pWndViews[i]->createWnd(this, i);
		m_pWndViews[i]->showWnd(true);
	}
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;

	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	cs.hMenu = NULL;
#ifdef _DEBUG
	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.lpszClass = AfxRegisterWndClass(0);
#else
	cs.style = WS_BORDER | WS_OVERLAPPED | WS_POPUP | WS_VISIBLE;
	cs.cx = ::GetSystemMetrics(SM_CXSCREEN);
	cs.cy = ::GetSystemMetrics(SM_CYSCREEN);

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.lpszClass = AfxRegisterWndClass(
		CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS,
		::LoadCursor(NULL, IDC_ARROW), HBRUSH(COLOR_MENUTEXT), NULL
	);
#endif
	return TRUE;
}

// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame message handlers

void CMainFrame::OnSetFocus(CWnd* /*pOldWnd*/)
{
	// forward focus to the view window
	int i = 1;
	if (m_pWndViews[i])
	{
		m_pWndViews[i]->SetFocus();
	}
}

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	// let the view have first crack at the command
	int i = 1;
	if (m_pWndViews[i] && m_pWndViews[i]->OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
		return TRUE;

	// otherwise, do default handling
	return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}



void CMainFrame::OnSize(UINT nType, int cx, int cy)
{
	CFrameWnd::OnSize(nType, cx, cy);
	int posX = 0, posY = 0, width = cx/2, height = cy/2, i = 0; 
	if (m_pWndViews[i])
	{
		m_pWndViews[i]->moveWnd(posX, posY, width, height, true);
	}

	++ i;
	posX += width;
	if (m_pWndViews[i])
	{
		m_pWndViews[i]->moveWnd(posX, posY, width, height, true);
	}

	++i;
	posX = 0;
	posY += height;
	if (m_pWndViews[i])
	{
		m_pWndViews[i]->moveWnd(posX, posY, width, height, true);
	}

	++i;
	posX += width;
	if (m_pWndViews[i])
	{
		m_pWndViews[i]->moveWnd(posX, posY, width, height, true);
	}
}


void CMainFrame::OnDestroy()
{
	CFrameWnd::OnDestroy();

	onCleanUp();
}
