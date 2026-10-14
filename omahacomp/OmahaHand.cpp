#include "StdAfx.h"
#include "OmahaHand.h"


COmahaCards::COmahaCards(
	const std::wstring& strId, const std::wstring& strInput)
	: m_strId(strId)
	, m_cards()
	, m_vCombs()
	//, m_bSameSuit(true)
{
	///. In this document we will use a two-character notation 
	///. for cards that will show the card rank and the card suit.
	//
	//	HandA:Ac-Kd-Jd-3d
	//  HandB:5c-5d-6c-7d
	//  Board:Ah-Kh-5s-2s-Qd
	std::size_t r = strInput.find(L"-"), l=0;
	while (r != std::string::npos)
	{
		m_cards.push_back(strInput.substr(l, r-l));
		l = r+1;
		///.
		r = strInput.find(L"-", l);
	}
	std::size_t nLen = strInput.length();
	if (l < nLen)
	{
		m_cards.push_back(strInput.substr(l, nLen-l));
	}
}


COmahaCards::~COmahaCards(void)
{
}

int COmahaCards::combine(int l, int r, int nNum, std::vector<std::wstring>& cards)
{
	int nError = -1;
	if (nNum == 0)
	{
		//base case
		m_vCombs.push_back(cards);
	}
	else if (l > r)
	{
		//bad case
	}
	else
	{
		cards.push_back(m_cards[l]);
		combine(l+1, r, nNum-1, cards);

		cards.pop_back();
		combine(l+1, r, nNum, cards);
	}
	return nError;
}

/////////////////////////////////////////////

COmahaHand::COmahaHand(
	const std::wstring& strId, const std::wstring& strInput)
	: COmahaCards(strId, strInput)
{
	///. In this document we will use a two-character notation 
	///. for cards that will show the card rank and the card suit.
	//
	//	HandA:Ac-Kd-Jd-3d
	//  HandB:5c-5d-6c-7d
	//  Board:Ah-Kh-5s-2s-Qd
	int nSize = m_cards.size(), nNum = 2;
	std::vector<std::wstring> vCards;
	COmahaCards::combine(0, nSize-1, nNum, vCards);
}

COmahaHand::~COmahaHand(void)
{
}
