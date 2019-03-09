#include "Card.hpp"
#include <iostream>
#include <string>

Suit StandardCard::getSuit() const {
 	return suit;
}

Rank StandardCard::getRank() const {
 	return rank;
}

void StandardCard::print() const {
	std::string value;
	int rank = this->getRank();
	switch (rank) {
		case Two: value = "2"; break;
		case Three: value = "3"; break;
		case Four: value = "4"; break;
		case Five: value = "5"; break;
		case Six: value = "6"; break;
		case Seven: value = "7"; break;
		case Eight: value = "8"; break;
		case Nine: value = "9"; break;
		case Ten: value = "10"; break;
		case Jack: value = "Jack"; break;
		case Queen: value = "Queen"; break;
		case King: value = "King"; break;
		case Ace: value = "Ace"; break;
	}

	value += " of ";

	int suit = this->getSuit();
	switch (suit) {
		case Heart: value += "Hearts"; break;
		case Diamond: value += "Diamonds"; break;
		case Club: value += "Clubs"; break;
		case Spade: value += "Spades"; break;
	}

	std::cout << value;
	return;
}

Color StandardCard::getColor() const {
	int suit = this->getSuit();
	switch (suit) {
		case Heart: return Red;
		case Diamond: return Red;
		case Club: return Black;
		case Spade: return Black;
	}
}

Color JokerCard::getColor() const {
	return color;
}

void JokerCard::print() const {
	int color = this->getColor();
	if (color == Black) {
		std::cout << "Black Joker";
	} else {
		std::cout << "Red Joker";
	}
	return;
}


bool Card::isStandard() const {
	if (type == Standard) {
		return true;
	} else {
		return false;
	}
}

bool Card::isJoker() const {
	if (type == Joker) {
		return true;
	} else {
		return false;
	}
}