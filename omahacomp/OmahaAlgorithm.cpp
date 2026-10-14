#include "StdAfx.h"
#include "OmahaAlgorithm.h"


namespace COmahaAlgorithm_Pri
{
	class CMyCards
	{
		///. we have the vector sored for high to low
		void sortString(std::vector<int>& vData)
		{
			int nSize = vData.size();
			int i=0;
			while (i<nSize)
			{
				int j=i+1;
				while (j<nSize)
				{
					if (vData[i] < vData[j])
					{
						int t1 = vData[i];

						vData[i] = vData[j];

						vData[j] = t1;
					}
					++j;
				}
				++i;
			}
		}/// end of void sortString(...)
	public:
		std::vector<int> m_cards;
		bool m_bSameSuit;
		CMyCards(std::vector<std::wstring>& str)
			: m_cards(5)
			, m_bSameSuit(true)
		{
			wchar_t s = str[0][1];
			for (int i=0; i<5; ++i)
			{
				//// In Poker unlike Bridge the suit has no impact on the ranking (e.g. Ks is as strong as Kd)
				////. so we only need the first char.
				wchar_t t = str[i][0];
				switch (t)
				{
				case 'A':
					m_cards[i] = 0;
					break;
				case 'K':
					m_cards[i] = 13;
					break;
				case 'Q':
					m_cards[i] = 12;
					break;
				case 'J':
					m_cards[i] = 11;
					break;
				case 'T':
					m_cards[i] = 10;
					break;
				default:
					m_cards[i] = _wtoi(&t);
					break;
				}
				if (s != str[i][1])
					m_bSameSuit = false;
			}
			sortString(m_cards);
		}
	};///. end of Class CMyCards

	///. any straight with all five cards
	bool isStraight(CMyCards& cards, std::wstring& strCard)
	{
		bool bFlag = true;
		auto it = cards.m_cards.begin();
		if (it!= cards.m_cards.end())
		{
			int n = *it;
			++ it;
			while (it!=cards.m_cards.end())
			{
				if (n == 0 || *it == 0)
					;
				else if (*it != n-1)
				{
					bFlag = false;
					break;
				}
				n = *it;
				++ it;
			}
		}
		return bFlag;
	}
	///.  any N cards of the same rank
	bool isKindOf(CMyCards& cards, int nNum, std::wstring& nCard)
	{
		bool bFlag = false;
		//. 14(A), 13(K), ... 1
		std::vector<int> vCards(14, 0);
		auto it  = cards.m_cards.begin();
		while (it != cards.m_cards.end())
		{
			vCards[*it] += 1;
			++ it;
		}
		int nSize = vCards.size();
		for (int i=0; i<nSize; ++i)
		{
			if (vCards[i] == nNum)
			{
				nCard = i + 1;
				bFlag = true;
				break;
			}
		}
		return bFlag;
	}
	///. get number of Pairs: AAKK5, return 2
	int getPairs(CMyCards& cards, std::wstring& nCard)
	{
		//. 14(A), 13(K), ... 1
		std::vector<int> vCards(14, 0);
		auto it  = cards.m_cards.begin();
		while (it != cards.m_cards.end())
		{
			vCards[*it] += 1;
			++ it;
		}
		int nSize = vCards.size();
		int nCount = 0;
		for (int i=0; i<nSize; ++i)
		{
			if (vCards[i] == 2)
			{
				nCard = i + 1;
				++ nCount;
			}
		}
		return nCount;
	}
	///. any hand not int the above-mentioned hands, compare the number
	bool compareString(CMyCards& cardA, CMyCards& cardB)
	{
		bool bFlag = true;
		auto it1 = cardA.m_cards.begin();
		auto it2 = cardB.m_cards.begin();
		while (it1 != cardA.m_cards.end())
		{
			if (*it1 < *it2)
			{
				bFlag = false;
				break;
			}
			++ it1, ++ it2;
		}
		return bFlag;
	}
	///. is all 5 cards have different rank
	bool isDuplicate(CMyCards& card)
	{
		bool bFlag = false;
		//. 14(A), 13(K), ... 1
		std::vector<int> vCards(14, 0);
		auto it  = card.m_cards.begin();
		while (it != card.m_cards.end())
		{
			vCards[*it] += 1;
			++ it;
		}
		int nSize = vCards.size();
		for (int i=0; i<nSize; ++i)
		{
			if (vCards[i] > 1)
			{
				bFlag = true;
				break;
			}
		}
		return bFlag;
	}
	//. is low-8 hand
	bool isLow8(std::vector<std::wstring>& vCards)
	{
		/*
		There are two required qualifications for a hand with 5 cards to 
		qualify for low-8 hand:
		a) All 5 cards should have different rank
		b) None of the cards should be higher than 8. Aces are always 
		considered to have the value of 1 for low hand evaluation.
		*/
		COmahaAlgorithm_Pri::CMyCards cards(vCards);
		return isDuplicate(cards) && cards.m_cards[0] <= 8;
	}
	/**/
	COmahaAlgorithm_Type getOmahaType(CMyCards& cards, std::wstring& strCard)
	{
		if (true == isStraight(cards, strCard))
		{
			return cards.m_bSameSuit ? COmahaAlgorithm_Straight_Flush : COmahaAlgorithm_Straight;
		}

		if (true == isKindOf(cards, 4, strCard))
			return COmahaAlgorithm_Kind_4;

		if (true == isKindOf(cards, 3, strCard))
		{
			if (true == isKindOf(cards, 2, strCard))
				return COmahaAlgorithm_Full_House;
			else
				return COmahaAlgorithm_Kind_3;
		}

		if (cards.m_bSameSuit)
			return COmahaAlgorithm_Flush;

		int nCount = getPairs(cards, strCard);
		switch (nCount)
		{
		case 2:
			return COmahaAlgorithm_Two_Pair;
		case 1:
			return COmahaAlgorithm_One_Pair;
		default:
			break;
		}
		return COmahaAlgorithm_None;
	}

}///. end of namespace COmahaAlgorithm_Pri

COmahaAlgorithm::COmahaAlgorithm(void)
{
}


COmahaAlgorithm::~COmahaAlgorithm(void)
{
}

void COmahaAlgorithm::getOmahaHiLo(
	std::vector<std::vector<std::wstring>>& vHand, 
	std::vector<std::vector<std::wstring>>& vBoard, 
	std::vector<std::wstring>& vHi,
	std::vector<std::wstring>& vLo)
{
	int nSizeH = vHand.size();
	std::vector<std::wstring> vCards(5);
	for (int i=0; i<nSizeH; ++i)
	{
		auto itH = vHand[i].begin();
		int nPos = 0;
		while (itH != vHand[i].end())
		{
			vCards[nPos] = *itH;
			++ itH, ++ nPos;
		}
		int nSizeB = vBoard.size();
		for (int j=0; j<nSizeB; ++j)
		{
			auto itB = vBoard[j].begin();
			int nPos2 = nPos;
			while (itB != vBoard[j].end())
			{
				vCards[nPos2] = *itB;
				++ itB, ++ nPos2;
			}
			///. sort the numbers from high to low
			COmahaAlgorithm_Type type = COmahaAlgorithm_None;
			if (vHi.empty() || isHi(vCards, vHi, type))
				vHi = vCards;
			else
				;//nothing
			bool bDupA = COmahaAlgorithm_Pri::isLow8(vCards);
			if (bDupA && (vLo.empty() || isLo(vCards, vLo, type)))
				vLo = vCards;
			else
				;//nothing
		}
	}//. end of for (int i=0; i<vHand.size(); ++i)

}//. end of void getOmahaHiLo(...)

bool COmahaAlgorithm::isLo(
	std::vector<std::wstring>& vCardsA, 
	std::vector<std::wstring>& vCardsB,
	COmahaAlgorithm_Type& type)
{
	bool bFlag = false;
	/*Any qualified low hand beats a hand that did not qualify for low.
	If no hand qualifies for low, then all chips are awarded to the winner(s) of the high hand.*/
	COmahaAlgorithm_Pri::CMyCards cardsA(vCardsA), cardsB(vCardsB);
	if (vCardsB.empty())
	{
		bFlag = true;
	}
	else if (vCardsA.empty())
	{
		bFlag = false;
	}
	else if (cardsA.m_cards[0] < cardsB.m_cards[0])
	{
		 bFlag = true;
	}
	return bFlag;
}

bool COmahaAlgorithm::isHi(
	std::vector<std::wstring>& vCardsA, 
	std::vector<std::wstring>& vCardsB,
	COmahaAlgorithm_Type& type)
{
	/* There are two required qualifications for a hand with 5 cards to qualify for low-8 hand:
	a) All 5 cards should have different rank
	b) None of the cards should be higher than 8. Aces are always considered to have the value of 1 for low hand evaluation.*/
	bool bFlag = false;
	std::wstring nCard1, nCard2;
	COmahaAlgorithm_Pri::CMyCards cardsA(vCardsA), cardsB(vCardsB);

	COmahaAlgorithm_Type type1 = COmahaAlgorithm_Pri::getOmahaType(cardsA, nCard1);
	COmahaAlgorithm_Type type2 = COmahaAlgorithm_Pri::getOmahaType(cardsB, nCard2);
	if (type1 > type2)
	{
		type = type1;
		bFlag = true;
	}
	else if (type1 == type2 && COmahaAlgorithm_Pri::compareString(cardsA, cardsB))
	{
		type1 = type1;
		bFlag = true;
	}
	else
	{
		//nothing
		type = type2;
	}
	return bFlag;
}
