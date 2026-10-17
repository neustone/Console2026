#pragma once

class TInfo
{
public:
	TInfo();
	virtual ~TInfo(void);
};

class INFO_LUT_
{
public:
	///.
	signed short nPixelPadding;
	///. WLWidth	/* Window Width for display.*/
	///. WLCenter	/* Defines a Window Center for display.*/
	double fInterceptOrWLWidth;
	double fSlopeOrWLCenter;
	///.
	char strLutType[32];
	unsigned short nLutDescriptor[3];
	char strPhotometricInterpretation[16];

	INFO_LUT_();
	INFO_LUT_& operator =(const INFO_LUT_& infoLUT);
};

///. Patient Infomation
struct INFO_PATIENT_
{
	//. Patient Info
	char strPatientID[48];	//PatientDB
	char strPatientName[48];
	char chSex;
	char strComment[255];
	TIMESTAMP_STRUCT dtRgstTime;
	TIMESTAMP_STRUCT dtBirthday;
	char strPatientEthnicGroup[16];//VR_SH 16

	//. Study Info
	char strAge[16];
	char strTel[48];
	char strAddress[48];
	char strHeight[8]; //unit
	char strWeight[8];
	char strReferPhysician[48];
	char strAccessNumber[48];
	char strStudyInstanceUID[64];
	char strStudyID[32];//VR_SH 16
	char strStudyDesc[64];//VR_LO 64
	TIMESTAMP_STRUCT dtStudyDate;

	//. Series Info
	char strPerformPhysician[48];
	char strBodyPartExamed[48];
	char strModality[16];			//VR_CS 16	
	char strSeriesInstanceUID[64];	//VR_UI 64
	long lSeriesNumber;		//VR_IS 12
	long lImageCount;
	TIMESTAMP_STRUCT dtSeriesDate;

	//. Image Info
	char strTransferSyntaxUID[64];
	char strSOPClassUID[64];	//VR_UI 64
	char strSOPInstanceUID[64];//VR_UI 64
	long lInstanceNumber;

	//. Saved Info
	long lDicomStatus;
	long lFileStatus;

	INFO_PATIENT_();

};

///. Grey Image Infomation
struct INFO_GREY_IMG_
{
	float fVersion;
	int	nImageUID, nImgCount;/* Number of frames in IMG*/
	char  strPatientPos[8];/* Patient position descriptor relative to the equipment.*/
	int nAllocBit, nUsingBit, nDispBit, nWidth, nHeight;
	unsigned short	nPixelRepresentation;/*Data representation of the pixel samples.
										 Each sample shall have the same pixel
										 representation. Enumerated Values:
										 0000H = unsigned integer.
										 0001H = 2's complement, though if the pixel data is signed,
										 i.e. Pixel Representation (0028,0103) is 0001H,*/
	unsigned short nMaxValueInPixel;
	signed short nMinValueInPixel;
	double fSliceThickness	/* Nominal slice thickness, in mm.*/
		, fSliceLocation;	/* Relative position of exposure, expressed in mm.*/
	double fImagePositon[3]	/* The x, y, and z coordinates, in mm.*/
		, fImageOrientation[6];/* The direction cosines.*/
	double fCoeffPixel2MM;	/* Physical distance in the patient between the center of each pixel, in mm.*/

	unsigned short nInverted;	/* intended interpretation of the pixel data. */
	//if (strcmp(LutInfo.LUT_Photometric_Interpretation,"MONOCHROME1") != 0) 
	//	nInverted = 0;
	//else
	//	nInverted = (1<<GII.nUsingBit)-1;
	//.

	char chDirectChar;//R or L 
	char chDirectPos;// 0,1,2,3,4 -->CW //0 : 

	int nDICOMStatus; //0:others; 1:DICOM image
	double CollimSx, CollimEx, CollimSy, CollimEy;

	INFO_GREY_IMG_();

};

///. Ex Grey Image Information
struct INFO_GREY_IMG_EX_
{
	int nUIDBodyPart;
	long lExpTime;
	char strImgType[32];
	char strImgDesc[512];

	INFO_GREY_IMG_EX_();

};