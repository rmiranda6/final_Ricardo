#include "Deck.h"

/**
 * constructs a new unshuffled deck
 */
Deck::Deck() {
	std::copy(Card::ALL_CARDS.begin(), Card::ALL_CARDS.end(), cards.begin());
	used.reset();
	top = 0;
	updatePositions();
}


/**
 * updates the array that keeps track of where every card is in the deck
 */
void Deck::updatePositions() {
	for (int i = 0; i < SIZE; i++) {
		positions[getCard(i).hashCode()] = i;
	}
}


/**
 * shuffles the deck, sets all cards to not used
 */
void Deck::shuffle() {
	used.reset();
	top = 0;
	std::random_shuffle(cards.begin(), cards.end(), Random());
	updatePositions();
}



const Card& Deck::pop() {
	setUsed(top, true);
	return getCard(top++);
}


int Deck::indexOf(const Card& card) const {
	return indexOf(card.hashCode());
}


int Deck::indexOf(int hash) const {
	return positions[hash];
}



bool Deck::isUsed(const Card& card) const {
	return isUsed(indexOf(card));
}


bool Deck::isUsed(int idx) const {
	return used[Card::HASH_IDX[getCard(idx).hashCode()]];
}


void Deck::setUsed(const Card& card, bool used) {
	setUsed(indexOf(card), used);
}


void Deck::setUsed(int idx, bool used) {
	this->used.set(Card::HASH_IDX[getCard(idx).hashCode()], used);
}



std::bitset<Card::NUM_CARDS> Deck::getBitset() const {
	return used;
}



const Card& Deck::getCard(int idx) {
	return cards[idx];
}


const Card& Deck::getCard(int idx) const {
	return cards[idx];
}



std::string Deck::toString() const {
	std::string str = "";
	for (int i = 0; i < SIZE; i++) {
		str += getCard(i).toString();
	}
	str += "\n";
	for (int i = 0; i < SIZE; i++) {
		if (isUsed(i)) {
			str += "--";
		}
		else {
			str += "  ";
		}
	}
	return str + "\n" + used.to_string();
}