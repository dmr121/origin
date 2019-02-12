# War
## David Rozmajzl

### Data Structures
There are **2 enums** in war: Suit for the 4 suits and Rank for the 14 ranks
The **struct** called "Card" has 1 member called "SuitRank". It is an unsigned 8 bit integer. The 4 leftmost bits
represent the suit whereas the rightmost 4 bits represent the rank.
There is another **struct** called "Deck" which behaves exactly like a deque. It holds Card objects.
The **class** "Game" has 2 members called "deck1" and "deck2" to represent the two decks that play against each other
in a game of war.

### Main
52 Card objects with all possible unique suit/rank combos are loaded into a Deck object called "deck." I then
used std::shuffle to shuffle the deck randomly. The deck is then split between deck1 and deck2 in the Game object
called "game." I then invoke game.play() to play a game of war. The winner is then printed out to the console.

Before, my functions for playing the game of war were standalone and existed in main. Because I created a Game object,
I made these functions public members of the game class so only the game has access to them and invokes these
functions on itself.
