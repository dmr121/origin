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
	Card deck[52];
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 13; ++j) {
			deck[j + (13*i)].suit = Suit(i);
			deck[j + (13*i)].rank = Rank(j);
		}
	}
}