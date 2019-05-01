#include <SFML/Graphics.hpp>
#include <time.h>
#include "game.hpp"
#include <iostream>
using namespace sf;

int
main()
{
  srand(time(0));

  Game game;

  // Construct the event loop and listeners.  
  event_source events(game.window);
  events.listen(game);

  while (game.is_open()) {
    while (game.isInProgress()) {
      float time = game.getClock().getElapsedTime().asSeconds();
      game.restartClock();
      game.addTime(time);

      // Polling only events that I have defined
      events.poll();

      // A tick means that 0.3 seconds have passed and the figure moves down
      game.tick();
      // Check if there is a solid line of 10 blocks
      game.checkLines();
      game.draw();
    }

    // Reset the status of the game to start over
    game.reset();
  }

  return 0;
}