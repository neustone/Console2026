#include "pch.h"
#include "InfoImage.h"

namespace TInfoImage_Pri
{
	int createLut256(BYTE* pLUT, int nWLWidth, int nWLCenter, int nPixelRepresentation, int nUsingBits, int nAlloBits)
	{
		int nError(-1);
		if (pLUT == NULL || nWLWidth < 1)
			return nError;
		try
		{
			int nStartPixelValue(nWLCenter - nWLWidth / 2);
			int nStopPixelValue(nWLCenter + nWLWidth / 2);
			int nTableCount(1 << nAlloBits);//m_nUsingBits
			BYTE nMaxTableColor(255);
			if (nPixelRepresentation == 1)
			{	//OnSetLutOflevel255Signed(pLUT, infoGreyImage, infoLutVOI);
				int nMaxValue;
				if (nUsingBits /*== 12*/ < 16)
					nMaxValue = (1 << nUsingBits) - 1;//4095//8191
				else
					nMaxValue = (1 << (nUsingBits - nPixelRepresentation)) - 1;//32767
	//			int nMinValue = -nMaxValue;

				memset(pLUT, 0, sizeof(BYTE) * nTableCount);
				for (int nIndex = 0; nIndex < nTableCount; nIndex++)
				{
					if (nIndex < nStartPixelValue)
					{
						*(pLUT + nIndex) = 0;
					}
					else if (nIndex >= nStartPixelValue && nIndex < nStopPixelValue)
					{
						BYTE nTemp = static_cast<BYTE>(nMaxTableColor * (nIndex - nStartPixelValue) / nWLWidth);
						if (nTemp < 0)
							*(pLUT + nIndex) = 0;
						else if (nTemp > nMaxTableColor)
							*(pLUT + nIndex) = nMaxTableColor;
						else
							*(pLUT + nIndex) = nTemp;
					}
					else if (nIndex <= nMaxValue)
					{
						*(pLUT + nIndex) = nMaxTableColor;
					}
					else
					{
						signed short nTempIndex = static_cast<signed short>(nIndex);
						signed short nTempStartPixelValue = static_cast<signed short>(nStartPixelValue);
						if (nTempIndex > nTempStartPixelValue)
						{
							*(pLUT + nIndex) = static_cast<BYTE>(nMaxTableColor * (nTempIndex - nStartPixelValue) / nWLWidth);
						}
					}
				}///. End of for each table index
			}
			else
			{	//OnSetLutOflevel255Unsigned(pLUT, infoGreyImage, infoLutVOI);
				int nMaxValue((1 << nUsingBits) - 1);//4095//8191//65535
				memset(pLUT, 0, sizeof(BYTE) * nTableCount);
				for (int nIndex = 0; nIndex < nTableCount; nIndex++)
				{
					if (nIndex < nStartPixelValue)
					{
						*(pLUT + nIndex) = 0;
					}
					else if (nIndex >= nStartPixelValue && nIndex < nStopPixelValue)
					{
						BYTE nTemp = static_cast<BYTE>(nMaxTableColor * (nIndex - nStartPixelValue) / nWLWidth);
						if (nTemp < 0)
							*(pLUT + nIndex) = 0;
						else if (nTemp > nMaxTableColor)
							*(pLUT + nIndex) = nMaxTableColor;
						else
							*(pLUT + nIndex) = nTemp;
					}
					else if (nIndex <= nMaxValue)
					{
						*(pLUT + nIndex) = nMaxTableColor;
					}
					else
					{
					}
				}///. End of for each table index
			}// end of if (m_nPixelRepresentation == 1)
			nError = 0;
		}
		catch (...)
		{
		}
		return nError;
	}//. end of createLut256(...)

	int createImage8(const BYTE* pLUT, const BYTE* pBufferSrc, int nNumOfPixel, int nInverted, BYTE* pBufferDes)
	{
		int nError(-1);
		if (pBufferSrc == NULL || pBufferDes == NULL || pLUT == NULL)
			return nError;

		try
		{
#ifdef _DEBUG
			CFile fp;
			if (fp.Open(L"d:\\temp\\Transact16.raw", CFile::modeReadWrite | CFile::modeCreate))
			{
				fp.Write(pBufferSrc, sizeof(unsigned short) * nNumOfPixel);
				fp.Close();
			}
#endif
			memset(pBufferDes, 0, nNumOfPixel);
			//		int iter(0), r(0),g(0),b(0);
			unsigned short* pt = (unsigned short*)pBufferSrc;
			for (int i = 0; i < nNumOfPixel; i++, pt++)
			{
				if (nInverted > 0)
					*(pBufferDes + i) = nInverted - *(pLUT + *pt);
				else
					*(pBufferDes + i) = *(pLUT + *pt);
			}
#ifdef _DEBUG
			if (fp.Open(L"d:\\temp\\Transact8.raw", CFile::modeReadWrite | CFile::modeCreate))
			{
				fp.Write(pBufferDes, nNumOfPixel);
				fp.Close();
			}
#endif
			nError = 0;
		}
		catch (...)
		{
		}
		return nError;
	}//. end of createImage8(...)

}// end of namespace TInfoImage_Pri

TInfoImage::TInfoImage(void)
	: m_strFileName()
	, m_InfoPatient()
	, m_InfoGreyImage()
	, m_InfoGreyImageEx()
	, m_InfoLutVOI()
	, m_InfoLutModality()
	, m_pPrcBits(nullptr)
	, m_pDispBits(nullptr)
	, m_pLookupTable(nullptr)
{

}

TInfoImage::~TInfoImage(void)
{
	resetImage();
}

bool TInfoImage::loadFile(const LPCTSTR fileName)
{
	if (0 == m_strFileName.compare(fileName))
		return true;

	resetImage();
	bool bRet = false;
	CFile fp;
	try
	{
		if (fp.Open(fileName, CFile::modeRead) == TRUE)
		{
			fp.Read(&m_InfoGreyImage, sizeof(INFO_GREY_IMG_));
			fp.Read(&m_InfoPatient, sizeof(INFO_PATIENT_));

			//.verify file values
			int nRawImageSize(m_InfoGreyImage.nHeight * m_InfoGreyImage.nWidth * m_InfoGreyImage.nAllocBit / 8);
			if (nRawImageSize > 0) //check m_Gii
			{
				//.m_Gii.CollimSx
				if (m_InfoGreyImage.CollimSx <= 0)
					m_InfoGreyImage.CollimSx = 0;
				else if (m_InfoGreyImage.CollimSx > m_InfoGreyImage.nWidth)
					m_InfoGreyImage.CollimSx = m_InfoGreyImage.nWidth;

				//.m_Gii.CollimSy
				if (m_InfoGreyImage.CollimSy <= 0)
					m_InfoGreyImage.CollimSy = 0;
				else if (m_InfoGreyImage.CollimSy > m_InfoGreyImage.nHeight)
					m_InfoGreyImage.CollimSy = m_InfoGreyImage.nHeight;

				//.m_Gii.CollimEx
				if (m_InfoGreyImage.CollimEx <= 0)
					m_InfoGreyImage.CollimEx = 0;
				else if (m_InfoGreyImage.CollimEx > m_InfoGreyImage.nWidth)
					m_InfoGreyImage.CollimEx = m_InfoGreyImage.nWidth;

				//.m_Gii.CollimEy
				if (m_InfoGreyImage.CollimEy <= 0)
					m_InfoGreyImage.CollimEy = 0;
				else if (m_InfoGreyImage.CollimEy > m_InfoGreyImage.nHeight)
					m_InfoGreyImage.CollimEy = m_InfoGreyImage.nHeight;

				//.get image buffer according to acquisition mode of image
				m_pPrcBits = new BYTE[nRawImageSize * m_InfoGreyImage.nImgCount];
				fp.Read(m_pPrcBits, nRawImageSize * m_InfoGreyImage.nImgCount);
				//.get other info of image file
				fp.Read(&m_InfoLutVOI, sizeof(INFO_LUT_));
				fp.Read(&m_InfoGreyImageEx, sizeof(INFO_GREY_IMG_EX_));
				fp.Read(&m_InfoLutModality, sizeof(INFO_LUT_));
				//...
				// bResult = CreateGrayImage(m_Gii, pImage, pImage);
				bRet = true;
			}
			fp.Close();
			m_strFileName = fileName;

			if (bRet)
			{
				if (m_pLookupTable == nullptr)
				{
					int nLen((1 << m_InfoGreyImage.nAllocBit) + 1);//m_InfoGreyImage.nUsingBit
					m_pLookupTable = new BYTE[nLen];
					memset(m_pLookupTable, 0, sizeof(BYTE) * nLen);
				}
				TInfoImage_Pri::createLut256(
					m_pLookupTable,
					static_cast<int>(m_InfoLutVOI.fInterceptOrWLWidth),
					static_cast<int>(m_InfoLutVOI.fSlopeOrWLCenter),
					m_InfoGreyImage.nPixelRepresentation, m_InfoGreyImage.nUsingBit, m_InfoGreyImage.nAllocBit );

				TInfoImage_Pri::createImage8(
					m_pLookupTable,
					m_pPrcBits, m_InfoGreyImage.nWidth * m_InfoGreyImage.nHeight, m_InfoGreyImage.nInverted,
					getDispBits());
			}

		}//end of if(fp.Open)
	}
	catch (...)
	{
		fp.Close();
	}
	return bRet;
}

void TInfoImage::resetImage()
{
	m_strFileName.clear();
	if (m_pPrcBits)
	{
		delete[] m_pPrcBits;
		m_pPrcBits = nullptr;
	}
	if (m_pDispBits)
	{
		delete[] m_pDispBits;
		m_pDispBits = nullptr;
	}
	//if (m_pHistogram)
	//{
	//	delete[] m_pHistogram;
	//	m_pHistogram = NULL;
	//}
	if (m_pLookupTable)
	{
		delete[] m_pLookupTable;
		m_pLookupTable = nullptr;
	}
}

BYTE* TInfoImage::getDispBits()
{
	if (m_pDispBits == nullptr)
	{
		int nLen(m_InfoGreyImage.nWidth * m_InfoGreyImage.nHeight * m_InfoGreyImage.nDispBit / 8 + 1);
		m_pDispBits = new BYTE[nLen];
		memset(m_pDispBits, 0, sizeof(BYTE) * nLen);
	}
	return m_pDispBits;
}
