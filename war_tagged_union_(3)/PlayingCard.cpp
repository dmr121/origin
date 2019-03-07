#include "PlayingCard.hpp"

// For initialization of a standard card
StandardCard::StandardCard(Suit suit_, Rank rank_)
 : suit(suit_), rank(rank_)
 { }

Suit StandardCard::getSuit() const {
 	return suit;
}

Rank StandardCard::getRank() const {
 	return rank;
}

JokerCard::JokerCard(Color color_)
 : color(color_)
 { }

Color JokerCard::getColor() const {
	return color;
}

PlayingCard::PlayingCard(Suit suit_, Rank rank_)
 : data(suit_, rank_), tag(Standard)
 { }

PlayingCard::PlayingCard(Color color_)
 : data(color_), tag(Joker)
 { }

bool PlayingCard::isStandard() {
	return tag == Standard;
}

bool PlayingCard::isJoker() {
	return tag == Joker;
}

Suit PlayingCard::getSuit() {
	assert(isStandard());
	return data.standard.getSuit();
}

Rank PlayingCard::getRank() {
	assert(isStandard());
	return data.standard.getRank();
}

Color PlayingCard::getColor() {
	assert(isJoker());
	return data.joker.getColor();
}