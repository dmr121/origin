# Changes:

The most obvious change I made was the addition of 4 new shapes. All I had to do
was add new arrays in the "figures" array. There is a d block, b block, double sqaure,
and a zig zag shape that I called a "weirdShape."

The next change I made was that the game resets when the player loses. Before, the game
kept producing overlapping blocks that stayed at the top of the screen and broke the game.
Now, I made a member function of Figure that detects if the blocks at the top of the screen
are overlapping, and it resets the field if it detects this.

I tried to add some text in the game that would say "game over" if the player lost the game,
but I kept getting a segmentation fault every time I would do that. The game would compile, but
get a seg fault every time I ran it. 

Also, the close button doesn't work on the window. I'm not sure if this is an issue with my
computer, but whenever I click the red button to close the game it stalls and acts weird. For
now, I am closing the game from the command line.