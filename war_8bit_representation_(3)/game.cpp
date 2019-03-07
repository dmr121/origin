#include "game.hpp"
#include <iostream>

// PRECONDITION: A Deck object
//
// POSTCONDITION: Splits the Deck object evenly between
//                the 2 member decks of Game class.
void Game::splitDeck(Deck & deck) {
	while (deck.size() > 0) {
		deck1.push_back(deck.front());
		deck.pop_front();
		deck2.push_back(deck.front());
		deck.pop_front();
	}
}

// PRECONDITION: Winner deck, loser deck, cards at stake when war takes place
//
// POSTCONDITION: Removes cards from player decks to be added to the warLoot pile
void Game::draw () {
    if (deck1.size() > 2) {
        warLoot.push_back(deck1.front());
        warLoot.push_back(deck1.front());
        deck1.pop_front();
        deck1.pop_front();
    }
    else if (deck1.size() == 2) {
        warLoot.push_back(deck1.front());
        deck1.pop_front();
    }

    if (deck2.size() > 2) {
        warLoot.push_back(deck2.front());
        warLoot.push_back(deck2.front());
        deck2.pop_front();
        deck2.pop_front();
    }
    else if (deck2.size() == 2) {
        warLoot.push_back(deck2.front());
        deck2.pop_front();
    }
}

// PRECONDITION: Winner, loser, cards at stake when war takes place
//
// POSTCONDITION: Gives winning player all of the cards won
void Game::winBattle (Deck & winner, Deck & loser) {
	winner.push_back(winner.front());
	winner.pop_front();
	winner.push_back(loser.front());
	loser.pop_front();

	while (warLoot.size() > 0) {
    	winner.push_back(warLoot.front());
    	warLoot.pop_front();
	}
} 

// PRECONDITION: None
//
// POSTCONDITION: The two member decks of the Game class play through
//                a game of war until a winner is declared. The winner
//                is printed out to the screen.
void Game::play() {
    int counter = 0;
	do {
        // If player 2 wins
        if (deck1.front().getRank() < deck2.front().getRank()) {
            this->winBattle(deck2, deck1);
        }
        // If player 1 wins
        else if (deck1.front().getRank() > deck2.front().getRank()) {
            this->winBattle(deck1, deck2);
        }
        else {
            // War takes place here
            this->draw();
        }
    } while (deck1.size() > 0 && deck2.size() > 0);
    if (deck1.size() > deck2.size()) {
        std::cout << "Player 1 Wins\n";
    } else {
        std::cout << "Player 2 Wins\n";
    }
}