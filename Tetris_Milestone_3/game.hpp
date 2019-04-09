#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <time.h>
#include "figure.hpp"

class Game {
private:
  Figure figure;
  sf::Clock clock;
  float timer, delay;
  bool inProgress;
public:
  // Default constructor
  Game()
   : timer(0), delay(0.3), inProgress(true)
   { }

   //PRECONDITION: None
   //
   //POSTCONDITION: Resets game
   void reset() {
    inProgress = true;
    // Resets the field once the game is over
    for (int i = 0; i < M; ++i) {
      for (int j = 0; j < N; ++j) {
        field[i][j] = 0;
      }
    }
   }

   //PRECONDITION: None
   //
   //POSTCONDITION: Returns the active status of the game
   bool isInProgress() {
    return inProgress;
   }

   //PRECONDITION: Event and window objects
   //
   //POSTCONDITION: Reads keyboard/event input and reacts accordingly.
   //               Can rotate, move laterally, speed up the fall of the figure.
   //               Also can close the window.
   void pollKeyBoard(sf::Event & e, sf::RenderWindow & window) {
      while (window.pollEvent(e)) {
        if (e.type == sf::Event::Closed)
          window.close();

        if (e.type == sf::Event::KeyPressed) {
          if (e.key.code == sf::Keyboard::Up)
            figure.rotate();
          else if (e.key.code == sf::Keyboard::Left)
            figure.move(Left);
          else if (e.key.code == sf::Keyboard::Right)
            figure.move(Right);
        }
      }

      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
      delay = 0.05;
   }

   //PRECONDITION: None
   //
   //POSTCONDITION: Represents a cycle in the game based on the
   //               length of the delay. Can shift figure down and also
   //               assign new shape and color to a new figure.
   void tick() {
    if (timer > delay) {
      figure.shiftDownOne();

      if (!figure.isInBound()) {
        this->setFieldColor();
        figure.changeShape();
        if (figure.overlaps()) {
          inProgress = false;
        }
        figure.changeColor();
      }
      timer = 0;
    }
   }

   //PRECONDITION: None
   //
   //POSTCONDITION: Changes the color of the field by sticking static blocks in it.
   void setFieldColor() {
    for (int i = 0; i < 8; i++)
      if (figure.coordinates[i].y != -1) {
        field[figure.tempCoords[i].y][figure.tempCoords[i].x] = figure.color;
      }
   }

   //PRECONDITION: None
   //
   //POSTCONDITION: Checks if there are 10 blocks in a row for a win.
   //               Removes the blocks if that is the case.
   void checkLines() {
    int k = M - 1;
    for (int i = M - 1; i > 0; i--) {
      int count = 0;
      for (int j = 0; j < N; j++) {
        if (field[i][j])
          count++;
        field[k][j] = field[i][j];
      }
      if (count < N)
        k--;
    }
    delay = 0.3;
   }

   //PRECONDITION: Window object and Sprite object
   //
   //POSTCONDITION: Draw the current positions of eveything on the screen
   //               based off of figure coordinates and field properties.
   void drawBlocks(sf::RenderWindow & window, sf::Sprite & s) {
    for (int i = 0; i < M; i++)
      for (int j = 0; j < N; j++) {
        if (field[i][j] == 0)
          continue;
        s.setTextureRect(sf::IntRect(field[i][j] * 18, 0, 18, 18));
        s.setPosition(j * 18, i * 18);
        s.move(28, 31); // offset
        window.draw(s);
      }

      for (int i = 0; i < 8; i++) {
        if (figure.coordinates[i].y != -1) {
          s.setTextureRect(sf::IntRect(figure.color * 18, 0, 18, 18));
          s.setPosition(figure.coordinates[i].x * 18, figure.coordinates[i].y * 18);
          s.move(28, 31); // offset
          window.draw(s);
        }
    }
   }

   sf::Clock getClock() {
    return clock;
   }

   void restartClock() {
    clock.restart();
   }

   //PRECONDITION: a float
   //
   //POSTCONDITION: Adds the time elapsed to the total time
   void addTime(float & time) {
    timer += time;
   }
};

#endif