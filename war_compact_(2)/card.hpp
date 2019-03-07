#ifndef CARD_H
#define CARD_H

#include <deque>

enum Suit {
    Heart,
    Diamond,
    Club,
    Spade
};

enum Rank {
    Two,
    Three,
    Four,
    Five,
    Six,
    Seven,
    Eight,
    Nine,
    Ten,
    Jack,
    Queen,
    King,
    Ace,
};

class Card {
private:
	uint8_t SuitRank;

public:
	Card(Suit suit, Rank rank);
	uint8_t getRank() const;
	uint8_t getSuit() const;
};

struct Deck : std::deque<Card> {
  using std::deque<Card>::deque;
};

#endif