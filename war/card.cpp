#include "card.hpp"

Card::Card(Suit suit, Rank rank)
 : SuitRank(SuitRank * 0 + suit * 16 + rank)
 { }

uint8_t Card::getSuit() const {
	return SuitRank >> 4;
}

uint8_t Card::getRank() const {
	return SuitRank % 16;
}