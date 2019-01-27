#include <iostream>
#include <queue>
#include <cstdlib>

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

void popDeck (std::queue<Card> & deck, std::queue<Card> & warLoot) {
    warLoot.push(deck.front());
    deck.pop();
}

void draw (std::queue<Card> & player1Deck, std::queue<Card> & player2Deck, std::queue<Card> & warLoot) {
        if (player1Deck.size() > 2) {
            popDeck(player1Deck, warLoot);
            popDeck(player1Deck, warLoot);
        }
        else if (player1Deck.size() == 2) {
            popDeck(player1Deck, warLoot);
        }

        if (player2Deck.size() > 2) {
            popDeck(player2Deck, warLoot);
            popDeck(player2Deck, warLoot);
        }
        else if (player2Deck.size() == 2) {
            popDeck(player2Deck, warLoot);
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
    // Seeding the time
    srand(time(0));
    for (int i = 0; i < 100; ++i) {
        int random1 = rand() % 52;
        int random2 = rand() % 52;
        std::swap(deck[random1], deck[random2]);
    }

    std::queue<Card> player1Deck;
    std::queue<Card> player2Deck;
    std::queue<Card> warLoot;
    for (int i = 0; i < 26; ++i) {
        player1Deck.push(deck[i]);
        player2Deck.push(deck[(2*i) + 1]);
    }

    do {
        Card& player1Card = player1Deck.front();
        Card& player2Card = player2Deck.front();

        if (player1Card.rank < player2Card.rank) {
            std::cout << player1Card.rank << " vs " << player2Card.rank << std::endl;
            winBattle(player2Deck, player1Deck, warLoot);
        }
        else if (player1Card.rank > player2Card.rank) {
            std::cout << player1Card.rank << " vs " << player2Card.rank << std::endl;
            winBattle(player1Deck, player2Deck, warLoot);
        }
        else {
            // War takes place here
            draw(player1Deck, player2Deck, warLoot);
        }
    } while (player1Deck.size() > 0 && player2Deck.size() > 0);

    if (player1Deck.size() == 52) {
        std::cout << "Winner: Player 1" << std::endl;
    } else {
        std::cout << "Winner: Player 2" << std::endl;
    }
    return 0;
}