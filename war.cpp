// David Rozmajzl dmr121@zips.uakron.edu
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

struct Player {
    std::queue <Card> deck;
};

// PRECONDITION: Winner, loser, cards at stake when war takes place
//
// POSTCONDITION: Gives winning player all of the cards won
void winBattle (Player & winner, Player & loser, std::queue<Card> & warLoot) {
    winner.deck.push(winner.deck.front());
    winner.deck.pop();
    winner.deck.push(loser.deck.front());
    loser.deck.pop();

    while (warLoot.size() > 0) {
        winner.deck.push(warLoot.front());
        warLoot.pop();
    }
}

// PRECONDITION: A player deck, cards at stake when war takes place
//
// POSTCONDITION: Pops card from front of player deck and pushes it 
//                to back of warLoot deck
void popDeck (std::queue <Card> & playerDeck, std::queue<Card> & warLoot) {
    warLoot.push(playerDeck.front());
    playerDeck.pop();
}

// PRECONDITION: Winner deck, loser deck, cards at stake when war takes place
//
// POSTCONDITION: Removes cards from player decks to be added to the warLoot pile
void draw (Player & player1, Player & player2, std::queue<Card> & warLoot) {
        if (player1.deck.size() > 2) {
            popDeck(player1.deck, warLoot);
            popDeck(player1.deck, warLoot);
        }
        else if (player1.deck.size() == 2) {
            popDeck(player1.deck, warLoot);
        }

        if (player2.deck.size() > 2) {
            popDeck(player2.deck, warLoot);
            popDeck(player2.deck, warLoot);
        }
        else if (player2.deck.size() == 2) {
            popDeck(player2.deck, warLoot);
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

    // Pushing random cards to player decks
    Player player1;
    Player player2;
    std::queue<Card> warLoot;
    for (int i = 0; i < 26; ++i) {
        player1.deck.push(deck[i]);
        player2.deck.push(deck[(2*i) + 1]);
    }

    do {
        // If player 2 wins
        if (player1.deck.front().rank < player2.deck.front().rank) {
            winBattle(player2, player1, warLoot);
        }
        // If player 1 wins
        else if (player1.deck.front().rank > player2.deck.front().rank) {
            winBattle(player1, player2, warLoot);
        }
        else {
            // War takes place here
            draw(player1, player2, warLoot);
        }
    } while (player1.deck.size() > 0 && player2.deck.size() > 0);

    if (player1.deck.size() == 52) {
        std::cout << "Winner: Player 1" << std::endl;
    } else {
        std::cout << "Winner: Player 2" << std::endl;
    }
    return 0;
}