# Tagged Union

## Files with relevant implementation changes:
1. main.cpp (just an example of the constructor in action)
2. PlayingCard.hpp
3. PlayingCard.cpp

I created a PlayingCard class that is capable of representing both standard cards and nonstandard joker cards. To do this, I
first created 2 separate classes. One called StandardCard for standard cards and another called JokerCard for joker cards. These
2 classes are then joined in a union object. Based on what is passed into the constructor, the union will produce only either
a StandardCard or JokerCard.

Similarly to how this was implemented in the 8 bit representation of a playing card, I had to create another enum called Color.
Its only elements are Red and Black. This is because a joker card doesn't have a suit, only a color. 
