# War
## David Rozmajzl

### Data Structures
There are **2 enums** in war: Suit for the 4 suits and Rank for the 14 ranks
The **struct** called "Card" has 2 members: a Suit called "suit" and a Rank called "rank"
There is **another struct** called "Player" that contains 1 queue of Cards called "deck." I chose a queue because it works
exactly like a deck of cards works in the game of war. The card in the front of the line is the only one to be used. And
new cards get loaded into the deck from the botton, or the back of the queue.

### Main
52 Card objects with all possible unique suit/rank combos are loaded into an array. Then a for loop that runs 100 times makes
a swap of two random cards in the array with every pass of the loop. This thoroughly sorts the cards. Then, as per the rules
of war, the cards are dealt to each of two players in an alternating order. In a do/while loop, the game plays. The ranks of
each card at the top of each deck are compared. There is a function called "winBattle" which deals the cards to the winner
of a round. It also deals them any extra cards won when there have been draws. There is a function called "draw" that places
the players cards on a common queue called "warLoot". Once a battle is won, the winner gets whichever cards were dealt plus
whatever was on the warLook queue. Once a player has no cards in their deck, the game ends. The winner is printed out at the
end.
