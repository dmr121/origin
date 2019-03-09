#ifndef CARD_H
#define CARD_H

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

// This is the enum for card type in the Card class
enum CardType {
    Standard,
    Joker,
};

class Card {
private:
    CardType type;

public:
    Card(CardType type_)
     : type(type_)
     { }
    virtual void print() const = 0;
    virtual Color getColor() const = 0;
    CardType getType();
};

// The class for a standard card
class StandardCard : Card {
private:
	Suit suit;
    Rank rank;

public:
	// For initialization of a standard card
    StandardCard(Suit suit_, Rank rank_)
     : Card(Standard), suit(suit_), rank(rank_)
     { }
	Rank getRank() const;
	Suit getSuit() const;
    void print() const;
    Color getColor() const;
};

// The class for a nonstandard joker card
class JokerCard : Card {
private:
    Color color;

public:
    JokerCard(Color color_)
     : Card(Joker), color(color_)
     { }
    Color getColor() const;
    void print() const;
};

#endif