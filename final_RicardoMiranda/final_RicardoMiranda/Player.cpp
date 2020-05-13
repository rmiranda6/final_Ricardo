#include "Player.h"


Player::Player() {
	startNewHand();
	setName("default");
}


Player::Player(std::string name) {
	startNewHand();
	setName(name);
}



std::string Player::getName() const {
	return name;
}


void Player::setName(std::string name) {
	this->name = name;
}



const Hand& Player::getHand() const {
	return hand;
}


int Player::getNumCards() const {
	return hand.getNumCards();
}



int Player::getPosition() const {
	return position;
}


void Player::setPosition(int position) {
	this->position = position;
}


int Player::relativeIDX(int offset) const {
	return ((getPosition() + offset) % Trick::NUM_CARDS + Trick::NUM_CARDS) % Trick::NUM_CARDS;
}


int Player::partnerIDX() const {
	return relativeIDX(2);
}


int Player::cyclicIDX(int idx) const {
	return ((idx % Trick::NUM_CARDS) + Trick::NUM_CARDS) % Trick::NUM_CARDS;
}


void Player::startNewHand() {
	hand.clear();
}



void Player::addCard(const Card& card) {
	hand.addCard(card);
	publicKnowledge(card, getPosition());
}



void Player::publicKnowledge(const Card& card, int playerIDX) {
}



void Player::publicKnowledge(const Card& card, int playerIDX, const Trick& trick) {
	publicKnowledge(card, playerIDX);
}



std::string Player::toString() const {
	return typeid(this).name() + name + ": " + hand.toString();
}



std::pair<int, bool> Player::orderUp(const Card& top, bool yourTeam) const {
	return std::make_pair(Pass, false);
}



std::pair<int, bool> Player::pickItUp(const Card& top) const {
	return std::make_pair(Pass, false);
}



void Player::replaceCard(const Card& top) {
}



std::pair<int, bool> Player::callTrump(int badSuit) const {
	return std::make_pair(Pass, false);
}



std::pair<int, bool> Player::stickTrump(int badSuit) const {
	return std::make_pair(Card::Spades, false);
}



Card Player::playCard(const Trick& trick) {
	return hand.removeCardIDX(0);
}
