
// WndAurora.cpp : implementation of the CWndAurora class
//

#include "pch.h"
#include "framework.h"
#include "AuroraStars.h"
#include "WndAurora.h"
#include "MemDC.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CWndAurora

IMPLEMENT_DYNAMIC(CWndAurora, CWnd)


CWndAurora::CWndAurora()
	: CWnd()
	, m_pClientDC(nullptr)
	, m_rtClient()
	, m_rgbBkColor(RGB(0, 0, 0))
	, m_rgbRectColor(RGB(0, 64, 0))
	, m_rgbItemTitle(RGB(204, 204, 204))
	, m_rgbItemValue(RGB(107, 186, 192))
	, m_strFont("Verbana")
{
}

CWndAurora::~CWndAurora()
{
}

int CWndAurora::render()
{
	return onWndRender(m_pClientDC);
}

void CWndAurora::getClientRect(CRect& clientRect)
{
	CWnd::GetClientRect(clientRect);
}

CDC* CWndAurora::getClientDC()
{
	return m_pClientDC;
}

int CWndAurora::messageBox(CWndAurora* pWnd, LPCWSTR lpText, LPCWSTR lpCaption)
{
//	return MessageBox(lpText, lpCaption, 0);
	return ::MessageBox(
		pWnd ? pWnd->GetSafeHwnd() : NULL, lpText, lpCaption, 0);
}

bool CWndAurora::createWnd(CWnd* pParent, UINT nID)
{
	BOOL bFlag = CWnd::Create(
		nullptr, nullptr,
		WS_CHILD | WS_VISIBLE | WS_OVERLAPPED,
		CRect(0, 0, 0, 0), pParent, nID/*AFX_IDW_PANE_FIRST*/, nullptr);
	//	SetLayeredWindowAttributes(0,128,LWA_ALPHA);

	return bFlag;
}

void CWndAurora::destroyWnd()
{
	CWnd::DestroyWindow();
}

bool CWndAurora::showWnd(bool bShown)
{
	return CWnd::ShowWindow(bShown ? SW_SHOW : SW_HIDE);
}

void CWndAurora::moveWnd(int x, int y, int nWidth, int nHeight, bool bRepaint)
{
	CWnd::MoveWindow(x, y, nWidth, nHeight, bRepaint?1:0);
}

void CWndAurora::setWndFocus()
{
	CWnd::SetFocus();
}

int CWndAurora::sendMessage(WPARAM wParam, LPARAM lParam)
{
	LRESULT ret = GetParent()->SendMessage(WM_WND_ABARIS_MESSAGE, wParam, lParam);
	return 0;
}

int CWndAurora::postMessage(WPARAM wParam, LPARAM lParam)
{
	LRESULT ret = GetParent()->PostMessage(WM_WND_ABARIS_MESSAGE, wParam, lParam);
	return 0;
}

////////////////////////////////////////////////////////


int CWndAurora::onWndCreate()
{
	if (m_pClientDC == nullptr)
	{
		m_pClientDC = new CClientDC(this);
	}
	return 0;
}

void CWndAurora::onWndDestroy()
{
	if (m_pClientDC)
	{
		delete m_pClientDC;
		m_pClientDC = nullptr;
	}
}

void CWndAurora::onWndSize(UINT nType, int cx, int cy)
{
	CWnd::GetClientRect(m_rtClient);
}

int CWndAurora::onWndRender(CDC* pDC)
{
	TRACE(_T("CWndAurora::onWndRender\n"));
	if (pDC)
	{
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetStretchBltMode(COLORONCOLOR);
		pDC->FillSolidRect(m_rtClient, m_rgbBkColor);
	}
	return 0;
}

int CWndAurora::onMsgWndRequest(WPARAM wParam, LPARAM lParam)
{
	TRACE(_T("CWndAurora::onMsgWndRequest\n"));
	return 0;
}

void CWndAurora::onLButtonDown(UINT nFlags, int x, int y)
{
	TRACE(_T("CWndAurora::onLButtonDown\n"));
}

void CWndAurora::onLButtonUp(UINT nFlags, int x, int y)
{
	TRACE(_T("CWndAurora::onLButtonUp\n"));
}

void CWndAurora::onLButtonDblClk(UINT nFlags, int x, int y)
{
	TRACE(_T("CWndAurora::onLButtonDblClk\n"));
}

////////////////////////////////////////////////////////

BOOL CWndAurora::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Add your specialized code here and/or call the base class
	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(
		CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW | CS_SAVEBITS | CS_NOCLOSE | CS_OWNDC,
		AfxGetApp()->LoadStandardCursor(IDC_ARROW), 0,
		AfxGetApp()->LoadStandardIcon(IDI_APPLICATION));

	return CWnd::PreCreateWindow(cs);
}

// CWndAurora message handlers

BEGIN_MESSAGE_MAP(CWndAurora, CWnd)
	ON_MESSAGE(WM_WND_ABARIS_MESSAGE, OnMsgWndRequest)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
//	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

LRESULT CWndAurora::OnMsgWndRequest(WPARAM wParam, LPARAM lParam)
{
	return onMsgWndRequest(wParam, lParam);
}

int CWndAurora::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO: Add your message handler code here
	onWndCreate();
	return 0;
}

void CWndAurora::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	// TODO: Add your message handler code here
	// Do not call CWnd::OnPaint() for painting messages
	onWndRender(m_pClientDC);
}

void CWndAurora::OnDestroy()
{
	CWnd::OnDestroy();

	// TODO: Add your message handler code here
	onWndDestroy();
}

void CWndAurora::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	onWndSize(nType, cx, cy);
}

void CWndAurora::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	onLButtonDblClk(nFlags, point.x, point.y);

	CWnd::OnLButtonDblClk(nFlags, point);
}

void CWndAurora::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	onLButtonDown(nFlags, point.x, point.y);

	CWnd::OnLButtonDown(nFlags, point);
}

void CWndAurora::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	onLButtonUp(nFlags, point.x, point.y);

	CWnd::OnLButtonUp(nFlags, point);
}

//BOOL CWndAurora::OnEraseBkgnd(CDC* pDC)
//{
////	onWndRender(pDC);
//	return CWnd::OnEraseBkgnd(pDC);
//}


