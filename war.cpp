#include <iostream>
#include <queue>

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

void compare (std::queue<Card> & winner, std::queue<Card> & loser) {
    winner.push(winner.front());
    winner.pop();
    winner.push(loser.front());
    loser.pop();
}

int main() {
    Card deck[52];
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 13; ++j) {
            deck[j + (13*i)].suit = Suit(i);
            deck[j + (13*i)].rank = Rank(j);
        }
    }

    std::queue<Card> player1Deck;
    std::queue<Card> player2Deck;
    std::queue<Card> warLoot;

    do {
        Card& player1Card = player1Deck.front();
        Card& player2Card = player2Deck.front();

        if (player1Card.suit < player2Card.suit) {
            compare(player2Deck, player1Deck);
        }
        if (player1Card.suit > player2Card.suit) {
            compare(player1Deck, player2Deck);
        }

        // War takes place here
        if (player1Card.suit == player2Card.suit) {
            
        }
    } while (player1Deck.size() != 52 && player1Deck.size() != 0);


}