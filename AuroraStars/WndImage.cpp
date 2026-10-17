#include "pch.h"
#include "WndImage.h"
#include "InfoImage.h"

CWndImage::CWndImage()
	: CWndAurora()
	, m_bmpInfo()
	, m_pInfoImage(new TInfoImage)
{
	m_pInfoImage->loadFile(L"..\\Data\\infoImage.IMG");
}

CWndImage::~CWndImage()
{
	if (m_pInfoImage)
	{
		delete m_pInfoImage;
		m_pInfoImage = nullptr;
	}
}

int CWndImage::onWndRender(CDC* pDC)
{
	TRACE(_T("CWndImage::onWndRender\n"));
	int nRet = -1;
	if (pDC && m_pInfoImage && m_pInfoImage->getDispBits())
	{
		pDC->FillSolidRect(m_rtClient, m_rgbBkColor);

		const INFO_GREY_IMG_& infoGreyImage = m_pInfoImage->getImageInfo();
		m_bmpInfo.bmiHeader.biWidth = infoGreyImage.nWidth;
		m_bmpInfo.bmiHeader.biHeight = infoGreyImage.nHeight;
		m_bmpInfo.bmiHeader.biBitCount = infoGreyImage.nDispBit;
		m_bmpInfo.bmiHeader.biSizeImage = infoGreyImage.nWidth * infoGreyImage.nHeight * infoGreyImage.nDispBit / 8;

		nRet = ::StretchDIBits(
			//destination 
			pDC->m_hDC, m_nViewOrgX, m_nViewOrgY, m_nViewWidth, m_nWiewHeight,
			//source 	
			0, 0, infoGreyImage.nWidth, infoGreyImage.nHeight, m_pInfoImage->getDispBits(),
			&m_bmpInfo,
			DIB_RGB_COLORS, SRCCOPY	);

		nRet = 0;
	}
	return nRet;
}

void CWndImage::onWndSize(UINT nType, int cx, int cy)
{
	CWndAurora::onWndSize(nType, cx, cy);
	if (m_pInfoImage)
	{
		const INFO_GREY_IMG_& infoGreyImage = m_pInfoImage->getImageInfo();
		float fRatioImage = static_cast<float>(infoGreyImage.nWidth);
		float fRatioWnd = static_cast<float>(m_rtClient.Width());
		fRatioImage = fRatioImage / infoGreyImage.nHeight;
		fRatioWnd = fRatioWnd / m_rtClient.Height();
		if (fRatioImage < fRatioWnd)
		{
			m_nViewOrgY = m_rtClient.top;
			m_nWiewHeight = m_rtClient.Height();
			m_nViewWidth = static_cast<int>(m_rtClient.Height() * fRatioImage);
			m_nViewOrgX = m_rtClient.Width() / 2 - m_nViewWidth / 2;
		}
		else
		{
			m_nViewOrgX = m_rtClient.left;
			m_nViewWidth = m_rtClient.Width();
			m_nWiewHeight = static_cast<int>(m_rtClient.Width() / fRatioImage);
			m_nViewOrgY = m_rtClient.Height() / 2 - m_nWiewHeight / 2;
		}
	}
}