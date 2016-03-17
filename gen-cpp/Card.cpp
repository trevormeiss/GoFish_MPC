#include "Card.hpp"

using namespace std;

Card::Card(int num, int i) {
	rank = (num-1) % 13;
	suit = ((num-1) / 13) % 4;
	index = i;
}

int Card::getRank() const {
	return rank;
}

int Card::getSuit() const {
	return suit;
}

int Card::getIndex() const {
	return index;
}

string Card::cardString() const {
	return RANKS[rank] + " of " + SUITS[suit];
}

string Card::rankString() const {
	return RANKS[rank];
}