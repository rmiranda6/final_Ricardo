#pragma once
#include "PartnerHLPlayer.h"
#include <array>


class CardCountingPlayer : public PartnerHLPlayer
{
public:
	CardCountingPlayer();
	CardCountingPlayer(std::string name);

	virtual void startNewHand() override;

	virtual void publicKnowledge(const Card& card, int playerIDX) override;
	virtual void publicKnowledge(const Card& card, int playerIDX, const Trick& trick) override;
	virtual std::bitset<Card::NUM_CARDS> getKnownCards() const;

	virtual bool playerHasSuit(int playerIDX, int suit, int trump) const;
	virtual int playerCountSuit(int playerIDX, int suit, int trump) const;
	virtual int playerStrengthSuit(int playerIDX, int suit, int trump) const;
	virtual int playerStrengthCard(int playerIDX, const Card& card, int trump) const;


	virtual Card playCard(const Trick& trick) override;
	virtual Card playFirst(const Trick& trick);
	virtual Card playSecond(const Trick& trick);
	virtual Card playThird(const Trick& trick);
	virtual Card playFourth(const Trick& trick);

protected:
	std::array<std::bitset<Card::NUM_CARDS>, Trick::NUM_CARDS> table;
	std::bitset<Card::NUM_CARDS> knownCards;
};