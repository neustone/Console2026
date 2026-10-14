#pragma once
#include <vector>

class COmahaCards
{
public:

	COmahaCards(
		const std::wstring& strId, const std::wstring& strInput);
	virtual ~COmahaCards(void);

protected:
	///. Hand Name
	std::wstring m_strId;
	///. hand cards
	std::vector<std::wstring> m_cards;
	///. combination of cards
	std::vector<std::vector<std::wstring>> m_vCombs;
//	bool m_bSameSuit;

	////////////////////////////////////

	///. generate all posiblilties recursively
	int combine(int l, int r, int nNum, std::vector<std::wstring>& cards);

};

/*
In OMAHA Hi/Lo each player receives 4 cards and
5 cards are placed on the board seen by all players
*/
class COmahaBoard;
class COmahaHand : public COmahaCards
{
	friend class COmahaBoard;
public:
	COmahaHand(
		const std::wstring& strId, const std::wstring& strInput);
	virtual ~COmahaHand(void);
};

/*
In OMAHA Hi/Lo each player receives 4 cards and
5 cards are placed on the board seen by all players
*/
class COmahaBoard : public COmahaCards
{
public:
	COmahaBoard(
		const std::wstring& strId, const std::wstring& strInput);
	virtual ~COmahaBoard(void);

	/*
	A player must combine any two of his cards with any three cards from the board
	to obtain 5 cards with the highest possible ranking for high hand, 
	
	and combine any other (or same) two of his cards with any other (or same) three cards
	from the board to obtain 5 cards with lowest possible low hand.

	It is important to realize that in all cases best 5-card combination of one player
	will be compared to best 5-card combination of another player to determine the winner.
	*/
	int omahaHiLo(
		COmahaHand& handA, COmahaHand& handB, std::wstring& strOutput);
};

