// David Rozmajzl dmr121@zips.uakron.edu
#include <iostream>
#include <vector>
#include <cstdlib>
#include "card.hpp"
#include "game.hpp"
#include <algorithm>    // std::shuffle
#include <random>       // std::default_random_engine
#include <chrono>       // std::chrono::system_clock

int main() {
	// Creating the deck with all possible unique rank/suit
	// combinations
	Deck deck {
		{Heart, Ace},
	    {Heart, Two},
	    {Heart, Three},
	    {Heart, Four},
	    {Heart, Five},
	    {Heart, Six},
	    {Heart, Seven},
	    {Heart, Eight},
	    {Heart, Nine},
	    {Heart, Ten},
	    {Heart, Jack},
	    {Heart, Queen},
	    {Heart, King},

	    {Diamond, Ace},
	    {Diamond, Two},
	    {Diamond, Three},
	    {Diamond, Four},
	    {Diamond, Five},
	    {Diamond, Six},
	    {Diamond, Seven},
	    {Diamond, Eight},
	    {Diamond, Nine},
	    {Diamond, Ten},
	    {Diamond, Jack},
	    {Diamond, Queen},
	    {Diamond, King},

	    {Club, Ace},
	    {Club, Two},
	    {Club, Three},
	    {Club, Four},
	    {Club, Five},
	    {Club, Six},
	    {Club, Seven},
	    {Club, Eight},
	    {Club, Nine},
	    {Club, Ten},
	    {Club, Jack},
	    {Club, Queen},
	    {Club, King},

	    {Spade, Ace},
	    {Spade, Two},
	    {Spade, Three},
	    {Spade, Four},
	    {Spade, Five},
	    {Spade, Six},
	    {Spade, Seven},
	    {Spade, Eight},
	    {Spade, Nine},
	    {Spade, Ten},
	    {Spade, Jack},
	    {Spade, Queen},
	    {Spade, King},
	};	

	// Seeding the time
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	// Shuffling the deck in a random order
	std::shuffle (deck.begin(), deck.end(), std::default_random_engine(seed));

	// Create the game object
	Game game;
	// Splitting the deck from above
	game.splitDeck(deck);
	// Play a game of war
	game.play();
}