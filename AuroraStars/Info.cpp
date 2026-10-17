#include "pch.h"
#include "Info.h"

TInfo::TInfo()
{
}

TInfo::~TInfo(void)
{
}

/////////////////////////////////////////////////////////////////////

INFO_LUT_::INFO_LUT_()
	: nPixelPadding(0)
	, fInterceptOrWLWidth(0)
	, fSlopeOrWLCenter(0)
{
	memset(strLutType, NULL, 32 * sizeof(char));
	memset(nLutDescriptor, 0, 3 * sizeof(unsigned short));
	memset(strPhotometricInterpretation, NULL, 16 * sizeof(char));
}

INFO_LUT_& INFO_LUT_::operator =(const INFO_LUT_& infoLUT)
{
	nPixelPadding = infoLUT.nPixelPadding;
	fInterceptOrWLWidth = infoLUT.fInterceptOrWLWidth;
	fSlopeOrWLCenter = infoLUT.fSlopeOrWLCenter;

	memcpy(strLutType, infoLUT.strLutType, 32);

	nLutDescriptor[0] = infoLUT.nLutDescriptor[0];
	nLutDescriptor[1] = infoLUT.nLutDescriptor[1];
	nLutDescriptor[2] = infoLUT.nLutDescriptor[2];

	memcpy(strPhotometricInterpretation, infoLUT.strPhotometricInterpretation, 16);

	return *this;
}

INFO_PATIENT_::INFO_PATIENT_()
	: chSex('M')
	, lSeriesNumber(0)
	, lImageCount(0)
	, lInstanceNumber(-1)
	, lDicomStatus(0)
	, lFileStatus(0)
{
	//. Patient Info
	memset(strPatientID, NULL, 48 * sizeof(char));
	memset(strPatientName, NULL, 48 * sizeof(char));
	memset(strComment, NULL, 255 * sizeof(char));
	memset(strPatientEthnicGroup, NULL, 16 * sizeof(char));
	//.
	dtRgstTime.year = 1900;
	dtRgstTime.month = 1;
	dtRgstTime.day = 1;
	dtRgstTime.hour = 1;
	dtRgstTime.minute = 1;
	dtRgstTime.second = 1;
	dtRgstTime.fraction = 0;
	//.
	dtBirthday.year = 1900;
	dtBirthday.month = 1;
	dtBirthday.day = 1;
	dtBirthday.hour = 1;
	dtBirthday.minute = 1;
	dtBirthday.second = 1;
	dtBirthday.fraction = 0;

	//. Study Info
	memset(strAge, NULL, 16 * sizeof(char));
	memset(strTel, NULL, 48 * sizeof(char));
	memset(strAddress, NULL, 48 * sizeof(char));
	memset(strHeight, NULL, 8 * sizeof(char));
	memset(strWeight, NULL, 8 * sizeof(char));
	memset(strReferPhysician, NULL, 48 * sizeof(char));
	memset(strAccessNumber, NULL, 48 * sizeof(char));
	memset(strStudyInstanceUID, NULL, 64 * sizeof(char));
	memset(strStudyID, NULL, 32 * sizeof(char));
	memset(strStudyDesc, NULL, 64 * sizeof(char));
	///.
	dtStudyDate.year = 1900;
	dtStudyDate.month = 1;
	dtStudyDate.day = 1;
	dtStudyDate.hour = 1;
	dtStudyDate.minute = 1;
	dtStudyDate.second = 1;
	dtStudyDate.fraction = 0;

	//. Series Info
	memset(strPerformPhysician, NULL, 48 * sizeof(char));
	memset(strBodyPartExamed, NULL, 48 * sizeof(char));
	memset(strModality, NULL, 16 * sizeof(char));
	memset(strSeriesInstanceUID, NULL, 64 * sizeof(char));
	//.
	dtSeriesDate.year = 1900;
	dtSeriesDate.month = 1;
	dtSeriesDate.day = 1;
	dtSeriesDate.hour = 1;
	dtSeriesDate.minute = 1;
	dtSeriesDate.second = 1;
	dtSeriesDate.fraction = 0;

	//. Image Info
	memset(strTransferSyntaxUID, NULL, 64 * sizeof(char));
	memset(strSOPClassUID, NULL, 64 * sizeof(char));
	memset(strSOPInstanceUID, NULL, 64 * sizeof(char));
}

INFO_GREY_IMG_::INFO_GREY_IMG_()
	: fVersion(3.0f)
	, nImageUID(0)
	, nImgCount(1)
	, nWidth(0)
	, nHeight(0)
	, nAllocBit(16)
	, nUsingBit(16)
	, nDispBit(8)
	, nPixelRepresentation(0)
	, nMaxValueInPixel(0)
	, nMinValueInPixel(0)
	, fSliceThickness(1.0)
	, fSliceLocation(0.0)
	, fCoeffPixel2MM(1.0)
	, nInverted(0)
	, chDirectChar('L')
	, chDirectPos('0')
	, nDICOMStatus(0)
	, CollimSx(0)
	, CollimSy(0)
	, CollimEx(0)//RAW_IMAGE_WIDTH;
	, CollimEy(0)//RAW_IMAGE_HEIGHT;	
{
	memset(strPatientPos, NULL, 8);
	memset(fImagePositon, 0, 3 * sizeof(double));
	memset(fImageOrientation, 0, 6 * sizeof(double));
}

INFO_GREY_IMG_EX_::INFO_GREY_IMG_EX_()
	: nUIDBodyPart(0)
	, lExpTime(0)
{
	memset(strImgType, NULL, 32 * sizeof(char));
	memset(strImgDesc, NULL, 512 * sizeof(char));
}
