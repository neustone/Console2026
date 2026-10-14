#include "StdAfx.h"
#include "OmahaHand.h"
#include "OmahaAlgorithm.h"
#include <iostream>

namespace COmahaBoard_Pri
{
	void print(std::vector<std::wstring>& vCards, std::wstring& strCards)
	{
		strCards += L"[ ";
		auto it = vCards.begin();
		while (it != vCards.end())
		{
			strCards += *it;
			strCards += L" ";
			++ it;
		}
		strCards += L"]";
	}
}

COmahaBoard::COmahaBoard(
	const std::wstring& strId, const std::wstring& strInput)
	: COmahaCards(strId, strInput)
{
	///. In this document we will use a two-character notation 
	///. for cards that will show the card rank and the card suit.
	//
	//	HandA:Ac-Kd-Jd-3d
	//  HandB:5c-5d-6c-7d
	//  Board:Ah-Kh-5s-2s-Qd
	int nSize = m_cards.size(), nNum = 3;
	std::vector<std::wstring> vCards;
	COmahaCards::combine(0, nSize-1, nNum, vCards);
}


COmahaBoard::~COmahaBoard(void)
{
}

int COmahaBoard::omahaHiLo(
	COmahaHand& handA, COmahaHand& handB, std::wstring& strOutput)
{
	int nError = 0;
	///. get HI and LO cards for A
	std::vector<std::wstring> vHiA, vLoA;
	COmahaAlgorithm::getOmahaHiLo(handA.m_vCombs, m_vCombs, vHiA, vLoA);

	///. get HI and LO cards for B
	std::vector<std::wstring> vHiB, vLoB;
	COmahaAlgorithm::getOmahaHiLo(handA.m_vCombs, m_vCombs, vHiB, vLoB);
	
	/*which one of the two OMAHA Hi/Lo poker hands is the winning hand for High*/
	COmahaAlgorithm_Type type = COmahaAlgorithm_None;
	if (vHiA.empty() && vHiB.empty())
	{
		strOutput += L" no Hi; ";
	}
	else if (COmahaAlgorithm::isHi(vHiA, vHiB, type))
	{
		strOutput += handA.m_strId;
		strOutput += L" win Hi ";
		COmahaBoard_Pri::print(vHiA, strOutput);
		strOutput += L"; ";
	}
	else
	{
		strOutput += handB.m_strId;
		strOutput += L" win Hi ";
		COmahaBoard_Pri::print(vHiB, strOutput);
		strOutput += L"; ";
	}
	/*which one is the winning hand for Low (if any).*/
	if (vLoA.empty() && vLoB.empty())
	{
		strOutput += L" no Lo; ";
	}
	else if (COmahaAlgorithm::isLo(vLoA, vLoB, type))
	{
		strOutput += handA.m_strId;
		strOutput += L" win Lo ";
		COmahaBoard_Pri::print(vLoA, strOutput);
		strOutput += L" ;";
	}
	else
	{
		strOutput += handB.m_strId;
		strOutput += L" win Lo ";
		COmahaBoard_Pri::print(vLoB, strOutput);
		strOutput += L" ;";
	}
	//.
	return nError;
}
