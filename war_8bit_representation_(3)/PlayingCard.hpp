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
    Two = 1,
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

class PlayingCard {
private:
	uint8_t SuitRank;

public:
	PlayingCard(Suit suit, Rank rank);
    //For initializing a joker card
    PlayingCard(Color color, Rank rank);
	uint8_t getRank() const;
	uint8_t getSuit() const;
    uint8_t getColor() const;
};

struct Deck : std::deque<PlayingCard> {
  using std::deque<PlayingCard>::deque;
};

#endif