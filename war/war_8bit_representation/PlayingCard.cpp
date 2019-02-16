#include "PlayingCard.hpp"

// For initialization of a standard card
Card::Card(Suit suit, Rank rank)
 : SuitRank(SuitRank * 0 + (suit * 16) + rank)
 { }

// For initialization of a joker card
Card::Card(Color color, Rank rank)
 : SuitRank(SuitRank * 0 + (color * 64) + rank)
 { }

uint8_t Card::getSuit() const {
 	return SuitRank >> 4;
}

uint8_t Card::getRank() const {
 	return SuitRank % 16;
}

uint8_t Card::getColor() const {
	return SuitRank >> 6;
}