#include "pch.h"
#include "WndCoverPage.h"

#include "MemDC.h"
#include "resource.h"

CWndCoverPage::CWndCoverPage()
	:CWndAurora()
	, m_bmpLogo()
{

}

CWndCoverPage::~CWndCoverPage()
{

}

int CWndCoverPage::onWndRender(CDC* pDC)
{
	TRACE(_T("CWndCoverPage::onWndRender\n"));
	int nRet = -1;
	if (pDC)
	{
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetStretchBltMode(COLORONCOLOR);
		pDC->FillSolidRect(m_rtClient, m_rgbBkColor);

		BITMAP bm;
		if (m_bmpLogo.GetSafeHandle() != NULL && m_bmpLogo.GetObject(sizeof(bm), &bm) > -1)
		{
			CDC dcBmp;
			dcBmp.CreateCompatibleDC(m_pClientDC);
			dcBmp.SelectObject(&m_bmpLogo);

			float fRatioImage = static_cast<float>(bm.bmWidth) / bm.bmHeight;
			float fRatioWnd = static_cast<float>(m_rtClient.Width()) / m_rtClient.Height();
			int x, y, w, h;
			if (fRatioImage < fRatioWnd)
			{
				y = m_rtClient.top;
				h = m_rtClient.Height();
				w = static_cast<int>(m_rtClient.Height() * fRatioImage);
				x = m_rtClient.Width() / 2 - w / 2;
			}
			else
			{
				x = m_rtClient.left;
				w = m_rtClient.Width();
				h = static_cast<int>(m_rtClient.Width() / fRatioImage);
				y = m_rtClient.Height() / 2 - h / 2;
			}
			pDC->StretchBlt(
				x, y, w, h,
				&dcBmp, 0, 0, bm.bmWidth, bm.bmHeight,
				SRCCOPY );
			nRet = 0;
		}
	}
	return 0;
}

void CWndCoverPage::onWndSize(UINT nType, int cx, int cy)
{
	CWndAurora::onWndSize(nType, cx, cy);
}

void CWndCoverPage::onLButtonDown(UINT nFlags, int x, int y)
{
}

void CWndCoverPage::onLButtonUp(UINT nFlags, int x, int y)
{
//	postMessage(CWndAurora::WND_MSG_UNKNOWN_, (LPARAM)this);
}

void CWndCoverPage::onLButtonDblClk(UINT nFlags, int x, int y)
{
	postMessage(CWndAurora::WND_MSG_EXIT_, (LPARAM)this);
}

void CWndCoverPage::onWndDestroy()
{
	if (m_bmpLogo.GetSafeHandle())
	{
		m_bmpLogo.DeleteObject();
	}

	CWndAurora::onWndDestroy();
}

int CWndCoverPage::onWndCreate()
{
	int nError = CWndAurora::onWndCreate();

	if (m_bmpLogo.GetSafeHandle() == NULL)
	{
		m_bmpLogo.LoadBitmap(IDB_BITMAP1);
	}
	return 0;
}
