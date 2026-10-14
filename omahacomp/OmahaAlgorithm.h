#pragma once
#include <vector>

enum COmahaAlgorithm_Type
{
	COmahaAlgorithm_None = 0,
	// Poker High rankings for any hand containing 
	// 5 cards are defined in the following order - from highest to lowest
	//
	// add low value here:
	COmahaAlgorithm_One_Pair,
	COmahaAlgorithm_Two_Pair,
	COmahaAlgorithm_Kind_3,
	COmahaAlgorithm_Straight,
	COmahaAlgorithm_Flush,
	COmahaAlgorithm_Full_House,
	COmahaAlgorithm_Kind_4,
	COmahaAlgorithm_Straight_Flush,
};

class COmahaAlgorithm
{
	COmahaAlgorithm(void);
	~COmahaAlgorithm(void);

public:

	/*
	3. Poker Rankings 
	3.1 Poker rankings for High Hand
	Poker High rankings for any hand containing 5 cards are defined in the following order
	- from highest to lowest
	*/
	static bool isHi(
		std::vector<std::wstring>& vCardsA, 
		std::vector<std::wstring>& vCardsB,
		COmahaAlgorithm_Type& type);

	/* 3.2 Poker rankings for Low 8 Hand.
	There are two required qualifications for a hand with 5 cards to qualify for low-8 hand:
	
	a) All 5 cards should have different rank
	b) None of the cards should be higher than 8. Aces are always considered to 
	have the value of 1 for low hand evaluation.

	Any qualified low hand beats a hand that did not qualify for low.
	If no hand qualifies for low, then all chips are awarded to the winner(s) 
	of the high hand.*/
	static bool isLo(
		std::vector<std::wstring>& vCardsA, 
		std::vector<std::wstring>& vCardsB,
		COmahaAlgorithm_Type& type);

	/* find both Omaha Hi and Lo from the combination of Hand & board*/
	static void getOmahaHiLo(
		std::vector<std::vector<std::wstring>>& vHand, 
		std::vector<std::vector<std::wstring>>& vBoard, 
		std::vector<std::wstring>& vHi,
		std::vector<std::wstring>& vLo);
};

