# 8 Bit Representation

## Files with relevant implementation changes:
1. main.cpp
2. PlayingCard.hpp
3. PlayingCard.cpp

The game plays almost exactly the same as it did before. I added a joker to the Rank enum. Jokers don't have a suit, but they do have a color. I created a Color enum with the members "red" and "black." I overloaded the PlayingCard class contructor to take a Color as an argument for making Joker cards.

As for the representation of the card, the left 2 bits represent the color. The next 2 represent the suit, and the right 4 represent the rank.
