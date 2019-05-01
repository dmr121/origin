# Changes:

I added the **event_source** class and the **event_listener** class to game.hpp.
This makes sure that the main game loop in main polls for only events that
I have specified. 

I also made the window, sprites, and textures a part of the Game class so upon
creating the Game object called game, everything is initialized.