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
	//CPaintDC dc(this); // device context for painting
	if (pDC)
	{
		CAuroraDC memDC(pDC, &m_rtClient);
		memDC.SetBkMode(TRANSPARENT);
		memDC.SetStretchBltMode(COLORONCOLOR);
		memDC.FillSolidRect(m_rtClient, m_rgbBkColor);

		BITMAP bm;
		if (m_bmpLogo.GetSafeHandle() != NULL && m_bmpLogo.GetObject(sizeof(bm), &bm) > -1)
		{
			CDC dcBmp;
			dcBmp.CreateCompatibleDC(m_pClientDC);
			dcBmp.SelectObject(&m_bmpLogo);
			memDC.StretchBlt(
				10, 10, 20, 20,
				&dcBmp, 0, 0, bm.bmWidth, bm.bmHeight,
				SRCCOPY
			);
		}
	}
	return 0;
}

void CWndCoverPage::onLButtonDown(UINT nFlags, int x, int y)
{
	postMessage(2);
}

void CWndCoverPage::onLButtonUp(UINT nFlags, int x, int y)
{
	sendMessage(1);
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
