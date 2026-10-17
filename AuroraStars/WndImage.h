#pragma once
#include "WndAurora.h"

class TInfoImage;
class CWndImage : public CWndAurora
{
	class TInfoDIB : public BITMAPINFO
	{
	public:
		RGBQUAD	 arColors[255];
		///.
		TInfoDIB() :BITMAPINFO()
		{
			bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
			bmiHeader.biWidth = 0;
			bmiHeader.biHeight = 0;
			bmiHeader.biPlanes = 1; // Must always be 1 according to docs
			bmiHeader.biBitCount = 8;
			bmiHeader.biCompression = BI_RGB;

			bmiHeader.biSizeImage = 0;
			bmiHeader.biXPelsPerMeter = 0;
			bmiHeader.biYPelsPerMeter = 0;
			bmiHeader.biClrUsed = 0;
			bmiHeader.biClrImportant = 0;
			///.
			for (UINT iColor = 0; iColor < 256; iColor++)
			{
				bmiColors[iColor].rgbReserved = 0;
				bmiColors[iColor].rgbBlue = iColor;
				bmiColors[iColor].rgbRed = iColor;
				bmiColors[iColor].rgbGreen = iColor;
			}
		}
		operator LPBITMAPINFO()
		{
			return (LPBITMAPINFO)this;
		}
		operator LPBITMAPINFOHEADER()
		{
			return &bmiHeader;
		}
		RGBQUAD* ColorTable()
		{
			return bmiColors;
		}

	} m_bmpInfo;

	TInfoImage* m_pInfoImage;
	int m_nViewOrgX, m_nViewOrgY, m_nViewWidth, m_nWiewHeight;

public:
	CWndImage();
	virtual ~CWndImage();

protected:
	virtual int onWndRender(CDC* pDC);
	virtual void onWndSize(UINT nType, int cx, int cy);
};

