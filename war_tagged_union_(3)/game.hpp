#ifndef GAME_H
#define GAME_H

#include "PlayingCard.hpp"

class Game {
private:
	Deck deck1;
	Deck deck2;
	Deck warLoot;
public:
	void splitDeck(Deck & deck);
	void draw();
  	void winBattle(Deck &, Deck &);
  	void play();
};

#endif

