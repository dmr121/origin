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
    // Randomly sort the deck
    for (int i = 0; i < 100; ++i) {
        int random1 = rand() % 52 + 1;
        int random2 = rand() % 52 + 1;
        std::swap(deck[random1], deck[random2]);
    }

    std::queue<Card> player1Deck;
    std::queue<Card> player2Deck;
    std::queue<Card> warLoot;
    for (int i = 0; i < 26; ++i) {
        player1Deck.push(deck[i]);
        player2Deck.push(deck[2*i + 1]);
    }

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
            draw(player1Deck, player2Deck, warLoot);
        }
    } while (player1Deck.size() != 52 && player1Deck.size() != 0);
}