#include <SFML/Graphics.hpp>
#include <time.h>
#include "game.hpp"
using namespace sf;

int
main()
{
  srand(time(0));

  RenderWindow window(VideoMode(320, 480), "The Game!");

  Texture t1, t2, t3;
  t1.loadFromFile("../images/tiles.png");
  t2.loadFromFile("../images/background.png");
  t3.loadFromFile("../images/frame.png");

  Sprite s(t1), background(t2), frame(t3);

  Game game;

  while (window.isOpen()) {
    float time = game.getClock().getElapsedTime().asSeconds();
    game.restartClock();
    game.addTime(time);

    Event e; // This event is used to detect arrow keys
    // Detecting and responding to arrow keys
    game.pollKeyBoard(e, window);
    // A tick means that 0.3 seconds have passed and the figure moves down
    game.tick();
    // Check if there is a solid line of 10 blocks
    game.checkLines();

    window.clear(Color::White);
    window.draw(background);
    // Draw the figure on the board every 0.3 seconds
    game.drawBlocks(window, s);

    window.draw(frame);
    window.display();
  }

  return 0;
}