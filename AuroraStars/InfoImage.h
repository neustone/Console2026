#pragma once
#include "Info.h"

class TInfoImage
{
public:

	TInfoImage(void);
	virtual ~TInfoImage(void);

	bool loadFile(const LPCTSTR fileName);
	void resetImage();
	BYTE* getDispBits();
	const INFO_GREY_IMG_& getImageInfo() const
	{
		return m_InfoGreyImage;
	}

private:
	std::wstring m_strFileName;
	INFO_PATIENT_ m_InfoPatient;
	INFO_GREY_IMG_ m_InfoGreyImage;
	INFO_GREY_IMG_EX_ m_InfoGreyImageEx;
	INFO_LUT_ m_InfoLutVOI;
	INFO_LUT_ m_InfoLutModality;
	///. Procecced Bits.
	BYTE* m_pPrcBits;
	///. Displayed Bits: valued by LupMapTo256Level(), displayed in Image Wnd      
	BYTE* m_pDispBits;
	///. 
	BYTE* m_pLookupTable;
};

