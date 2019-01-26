#include <iostream>

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
	Ace

};

struct Card {
	Suit suit;
	Rank rank;
};

int main() {
	Card test{Heart, Nine};
	std::cout << test.suit;
}