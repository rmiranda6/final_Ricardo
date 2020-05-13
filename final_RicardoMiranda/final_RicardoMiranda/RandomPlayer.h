#pragma once
#include "Random.h"
#include "Card.h"
#include "Hand.h"
#include "Player.h"
#include <utility>


class RandomPlayer : public Player
{
public:
	RandomPlayer();
	RandomPlayer(std::string name);

	/*
	virtual std::pair<int,bool> orderUp(const Card& top, bool yourTeam) const override;
	virtual std::pair<int,bool> pickItUp(const Card& top) const override;
	virtual void replaceCard(const Card& top) override;
	virtual std::pair<int,bool> callTrump(int badSuit) const override;
	virtual std::pair<int,bool> stickTrump(int badSuit) const override;
	*/
	virtual Card playCard() override;
};