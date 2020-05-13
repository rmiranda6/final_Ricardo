#include "Hand.h"

#ifdef HAND_ALL_HANDS
/**
 * @return all possible hands per size
 */
std::array<std::vector<Hand>, Hand::NUM_CARDS + 1> allHands() {
	std::array<std::vector<Hand>, Hand::NUM_CARDS + 1> hands;
	for (int size = 1; size <= Hand::NUM_CARDS; size++) {
		int start = BitString::first(size);
		int finish = BitString::last(size, Card::NUM_CARDS);
		for (int bits = start; bits <= finish; bits = BitString::next(bits)) {
			hands[size].push_back(Hand(std::bitset<Card::NUM_CARDS>(bits)));
		}
		hands[size].shrink_to_fit();
	}
	return hands;
}

/**
 * all possible euchre hands
 */
const std::array<std::vector<Hand>, Hand::NUM_CARDS + 1> Hand::ALL_HANDS = allHands();
#endif

/**
 * constructor sets up an empty hand
 */
Hand::Hand() {
	clear();
}


Hand::Hand(std::bitset<Card::NUM_CARDS> bits) {
	clear();
	addSet(bits);
}

/**
 * clears all cards from this hand
 */
void Hand::clear() {
	bits.reset();
	hand.clear();
}



void Hand::addCard(const Card& card) {
	addCard(card.hashCode());
}



void Hand::addCard(int hash) {
	hand.push_back(hash);
	bits.set(Card::HASH_IDX[hash], true);
}



void Hand::addSet(unsigned int bits) {
	addSet(std::bitset<Card::NUM_CARDS>(bits));
}


void Hand::addSet(std::bitset<Card::NUM_CARDS> bits) {
	for (int i = 0; bits.any(); i++) {
		if (bits[i]) {
			bits.set(i, false);
			addCard(Card::ALL_CARDS[i]);
		}
	}
}



int Hand::getCard(int idx) const {
	return hand[idx];
}


int Hand::removeCardIDX(int idx) {
	int card = getCard(idx);
	bits.set(Card::HASH_IDX[card], false);
	hand.erase(hand.begin() + idx);
	return card;
}


int Hand::removeCard(int hash) {
	for (int i = 0; i < getNumCards(); i++) {
		if (hash == getCard(i)) {
			return removeCardIDX(i);
		}
	}
	return -1;
}



int Hand::removeCard(const Card& card) {
	return removeCard(card.hashCode());
}


int Hand::removeLastCard() {
	return removeCard(getNumCards() - 1);
}



int Hand::getNumCards() const {
	return hand.size();
}



std::bitset<Card::NUM_CARDS> Hand::getBitset() const {
	return bits;
}


std::bitset<Card::NUM_CARDS> Hand::getSuitBitset(int suit) const {
	std::bitset<Card::NUM_CARDS> cards;
	int hash = Card::hashCode(9, suit);
	for (int card : hand) {
		if (Card::sameSuit(card, hash)) {
			cards.set(Card::HASH_IDX[card], true);
		}
	}
	return cards;
}


std::bitset<Card::NUM_CARDS> Hand::getLegalBitset(const Trick& trick) const {
	std::bitset<Card::NUM_CARDS> legalCards;
	for (int card : hand) {
		if (trick.isLegal(card)) {
			legalCards.set(Card::HASH_IDX[card], true);
		}
	}
	return legalCards;
}


std::bitset<Card::NUM_CARDS> Hand::getPlayableBitset(const Trick& trick) const {
	std::bitset<Card::NUM_CARDS> cards = getLegalBitset(trick);
	if (!cards.any()) {
		return getBitset();
	}
	return cards;
}



std::vector<int> Hand::getCards() const {
	return hand;
}


std::vector<int> Hand::getSuitCards(int suit) const {
	std::vector<int> cards;
	int hash = Card::hashCode(9, suit);
	for (int card : hand) {
		if (Card::sameSuit(card, hash)) {
			cards.push_back(card);
		}
	}
	return cards;
}


std::vector<int> Hand::getLegalCards(const Trick& trick) const {
	std::vector<int> legalCards;
	for (int card : hand) {
		if (trick.isLegal(card)) {
			legalCards.push_back(card);
		}
	}
	return legalCards;
}

std::vector<int> Hand::getPlayableCards(const Trick& trick) const {
	std::vector<int> cards = getLegalCards(trick);
	if (cards.empty()) {
		return getCards();
	}
	return cards;
}



int Hand::hashCode() const {
	return bits.to_ulong();
}



std::string Hand::toString() const {
	std::string str = "";
	for (int card : hand) {
		str += Card(card).toString() + " ";
	}
	return str;
}


bool Hand::intersects(const Hand& hand) const {
	return intersects(hand.getBitset());
}


bool Hand::intersects(unsigned int bits) const {
	return (getBitset().to_ulong() & bits) != 0;
}


bool Hand::intersects(const std::bitset<Card::NUM_CARDS>& bits) const {
	return (getBitset() & bits).any();
}


bool Hand::subsetOf(const std::bitset<Card::NUM_CARDS>& bits) const {
	return (getBitset() & bits) == getBitset();
}