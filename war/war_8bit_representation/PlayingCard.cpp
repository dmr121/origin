#include "PlayingCard.hpp"

// For initialization of a standard card
PlayingCard::PlayingCard(Suit suit, Rank rank)
 : SuitRank(0)
 {
 	if (suit == Heart || suit == Diamond) {
 		SuitRank = Red * 64;
 	} else if (suit == Club || suit == Spade) {
 		SuitRank = Black * 64;
 	}
 	SuitRank += (suit * 16) + rank;
 }

// For initialization of a joker card
PlayingCard::PlayingCard(Color color, Rank rank)
 : SuitRank(0)
 {
 	SuitRank = color * 64 + rank;
 }

uint8_t PlayingCard::getSuit() const {
 	return SuitRank >> 4;
}

uint8_t PlayingCard::getRank() const {
 	return SuitRank % 16;
}

uint8_t PlayingCard::getColor() const {
	return SuitRank >> 6;
}