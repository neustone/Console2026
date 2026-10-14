// omahacomp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "OmahaGenerator.h"

/*
To design the algorithm and write a C++ program that will determine 
which one of the two OMAHA Hi/Lo poker hands is the winning hand 
for High and which one is the winning hand for Low (if any).

The applicant is expected to design the algorithm and necessary 
data / class structures to provide implementation that is robust, 
logical and easy to understand. It is not necessary to validate
the input or provide any other error handling in the implementation.
*/
int _tmain(int argc, _TCHAR* argv[])
{
	///. omahacomp input.txt output.txt
	if (argc >= 3) 
    {
		std::wstring strInput = argv[1];
		std::wstring strOutput = argv[2];

		std::wifstream fInput(strInput);
		std::wofstream fOutput(strOutput);
		if (fInput.is_open() && fOutput.is_open())
		{
			int nLines = 0;
			///. load each line from input file
			//	HandA:Ac-Kd-Jd-3d HandB:5c-5d-6c-7d Board:Ah-Kh-5s-2s-Qd
			std::wstring strLine;
			while (std::getline(fInput, strLine))
			{
				///. calculate the result
				std::wstring strResult;
				if (0 == COmahaGenerator::commit(strLine,  strResult))
				{
					///. write the result to output file
					fOutput << nLines << L": " << strLine << std::endl;
					//	=> HandB wins Hi (3-of-a-Kind); HandB wins Lo (7652A)
					fOutput << L"=> " << strResult << std::endl;
				}
				++ nLines;
			}
		}
		else
		{
			///. bad case
			std::cout << "Unable to open files" << std::endl;
		}

		///. close both files
		if (fInput.is_open())
			fInput.close();
		if (fOutput.is_open())
			fOutput.close();

	}///. end of if ( argc == 3 ) 
	return 0;
}

