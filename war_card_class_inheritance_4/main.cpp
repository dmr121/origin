// David Rozmajzl dmr121@zips.uakron.edu
#include <iostream>
#include <vector>
#include <cstdlib>
#include "Card.hpp"

int main() {
	StandardCard standard(Diamond, Ace);
	JokerCard joker(Black);

	standard.print();
	std::cout << '\n';

	joker.print();
	std::cout << '\n';

	return 0;
}