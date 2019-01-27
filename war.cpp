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

void winBattle (std::queue<Card> & winner, std::queue<Card> & loser, std::queue<Card> & warLoot) {
    winner.push(winner.front());
    winner.pop();
    winner.push(loser.front());
    loser.pop();

    while (warLoot.size() > 0) {
        winner.push(warLoot.front());
        warLoot.pop();
    }
}

void draw (std::queue<Card> & player1Deck, std::queue<Card> & player2Deck, std::queue<Card> & warLoot) {
    for (int i = 0; i < 2; ++i) {
        warLoot.push(player1Deck.front());
        player1Deck.pop();
        warLoot.push(player2Deck.front());
        player2Deck.pop();
    }
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
            winBattle(player2Deck, player1Deck, warLoot);
        }
        if (player1Card.suit > player2Card.suit) {
            winBattle(player2Deck, player1Deck, warLoot);
        }

        // War takes place here
        if (player1Card.suit == player2Card.suit) {
            draw(player2Deck, player1Deck, warLoot);
        }
    } while (player1Deck.size() != 52 && player1Deck.size() != 0);
}