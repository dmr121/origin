#ifndef PLAYINGCARD_H
#define PLAYINGCARD_H

#include <deque>
#include <cassert>

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

enum Color {
    Red,
    Black,
};

// The class for a standard card
class StandardCard {
private:
	Suit suit;
    Rank rank;

public:
	StandardCard(Suit suit_, Rank rank_);
	Rank getRank() const;
	Suit getSuit() const;
};

// The class for a nonstandard joker card
class JokerCard {
private:
    Color color;
public:
    JokerCard(Color color_);
    Color getColor() const;
};

// This union can hold one of two type of cards,
// It can be either a joker card or a standard card
// but not both.
union Card {
    JokerCard joker;
    StandardCard standard;

    Card(Suit suit_, Rank rank_)
     : standard(suit_, rank_)
     { }

    Card(Color color_)
     : joker(color_)
     { }
};

// This is the enum for the tag in the tagged union below
enum CardType {
    Standard,
    Joker,
};

// This class is all-encompassing. It can hold data
// from either a standard card or nonstandard joker card.
class PlayingCard {
private:
    Card data;
    CardType tag;

public:
    // Constructor for a standard card
    PlayingCard(Suit suit_, Rank rank_);
    // Constructor for a joker card
    PlayingCard(Color color_);
    bool isStandard();
    bool isJoker();
    Suit getSuit();
    Rank getRank();
    Color getColor();
};

struct Deck : std::deque<PlayingCard> {
  using std::deque<PlayingCard>::deque;
};

#endif