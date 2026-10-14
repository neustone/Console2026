#include "StdAfx.h"
#include "OmahaGenerator.h"
#include "OmahaHand.h"

COmahaGenerator::COmahaGenerator(void)
{
}


COmahaGenerator::~COmahaGenerator(void)
{
}

int COmahaGenerator::commit(const std::wstring& strInput, std::wstring& strOutput)
{
	int nError = -1, nInputSize = strInput.size();
	if (nInputSize > 0)
	{
		std::wstring strHandA, strHandB, strBoard;
		///. get data from input
		//	HandA:Ac-Kd-Jd-3d HandB:5c-5d-6c-7d Board:Ah-Kh-5s-2s-Qd
		std::size_t l = strInput.find(L"HandA:");
		if (l != std::string::npos)
		{
			std::size_t r = strInput.find(L" ", l+1);
			strHandA = strInput.substr(l+6, r-l-6);
		}
		l = strInput.find(L"HandB:");
		if (l != std::string::npos)
		{
			std::size_t r = strInput.find(L" ", l+1);
			strHandB = strInput.substr(l+6, r-l-6);
		}
		l = strInput.find(L"Board:");
		if (l != std::string::npos)
		{
			std::size_t r = strInput.find(L" ", l+1);
			strBoard = strInput.substr(l+6, r-l-6);
		}

		///. validation of inputs
		if (false == strHandA.empty() && 
			false == strHandB.empty() && 
			false == strBoard.empty())
		{
			COmahaHand handA(L"HandA", strHandA), handB(L"HandB", strHandB);
			COmahaBoard board(L"Board", strBoard);

			/* which one of the two OMAHA Hi/Lo poker hands
			is the winning hand for High and which one is 
			the winning hand for Low (if any)*/
			nError = board.omahaHiLo(handA, handB, strOutput);
		}
	}
	return nError;
}