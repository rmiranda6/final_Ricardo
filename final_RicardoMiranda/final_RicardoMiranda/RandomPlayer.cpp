#include "RandomPlayer.h"

/**
 * constructor, just call parent
 */
RandomPlayer::RandomPlayer() : Player() {
}


RandomPlayer::RandomPlayer(std::string name) : Player(name) {
}






 
   /*
   void RandomPlayer::replaceCard(const Card& top) {
	   hand.removeCard(Random::nextInt(hand.getNumCards()));
	   hand.addCard(top);
   }
   */

 
Card RandomPlayer::playCard() {
	std::vector<int> cards = getHand().getPlayableCards();
	return hand.removeCard(cards[Random::nextInt(cards.size())]);
	/*
	std::vector<int> legal);
	if (legalCards.empty()) {
		return hand.removeCard(Random::nextInt(hand.getNumCards()));
	}
	return hand.removeCard(Card(legal[Random::nextInt(legalCards.size())]));
	*/
}