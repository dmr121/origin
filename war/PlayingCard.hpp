#ifndef PLAYINGCARD_H
#define PLAYINGCARD_H

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
    Joker,
};

enum Color {
    Red,
    Black,
};

class Card {
private:
	uint8_t SuitRank;

public:
	Card(Suit suit, Rank rank);
    Card(Color color, Rank rank);
	uint8_t getRank() const;
	uint8_t getSuit() const;
    uint8_t getColor() const;
};

struct Deck : std::deque<Card> {
  using std::deque<Card>::deque;
};

#endif