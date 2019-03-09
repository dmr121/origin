// David Rozmajzl dmr121@zips.uakron.edu
#include <iostream>
#include <vector>
#include <cstdlib>
#include <cassert>
#include "Card.hpp"

int main() {
	StandardCard standard(Diamond, Ace);
	JokerCard joker(Black);

	standard.print();
	std::cout << '\n';
	assert(standard.getColor() == Red);
	assert(standard.isStandard() == true);
	assert(standard.isJoker() == false);

	joker.print();
	std::cout << '\n';
	assert(joker.getColor() == Black);
	assert(joker.isJoker() == true);
	assert(joker.isStandard() == false);

	return 0;
}