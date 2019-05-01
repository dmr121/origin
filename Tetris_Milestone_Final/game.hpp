#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <time.h>
#include "figure.hpp"


// I took these event classes from your gitlab
struct event_listener
{
  // Window events
  virtual void on_close() { }

  // Keyboard events
  virtual void on_key_press(sf::Event::KeyEvent) { }
};

struct event_source
{
  event_source(sf::Window& w)
    : window(&w)
  { }

  void
  listen(event_listener& l)
  {
    listeners.push_back(&l);
  }

  // Notify listeners of queued events.
  void
  poll()
  {
    sf::Event e;
    while (window->pollEvent(e))
      process(e);
  }

  // Notify listeners of a single event.
  void process(sf::Event const& e)
  {
    switch (e.type) {
    case sf::Event::Closed:
      return notify([e](event_listener* l) { l->on_close(); });
    case sf::Event::KeyPressed:
      return notify([e](event_listener* l) { l->on_key_press(e.key); });
    default:
      break;
    }
  }

  template<typename F>
  void notify(F fn)
  {
    for (event_listener* l : listeners)
      fn(l);    
  }

  // The window that we can poll for events.
  sf::Window* window;

  // A list of listeners to notify about particular
  // events.
  std::vector<event_listener*> listeners;
};

struct Game : event_listener {
  Figure figure;
  sf::Clock clock;
  float timer, delay;
  bool inProgress;
  sf::RenderWindow window;
  sf::Sprite s, background, frame;
  sf::Texture t1, t2, t3;

  // Default constructor
  Game()
   : timer(0), delay(0.3), inProgress(true), window(sf::VideoMode(320, 480), "The Game!")
   {
    t1.loadFromFile("../images/tiles.png");
    t2.loadFromFile("../images/background.png");
    t3.loadFromFile("../images/frame.png");
    s.setTexture(t1);
    background.setTexture(t2);
    frame.setTexture(t3);
    window.setVerticalSyncEnabled(true);
   }

   // Returns true if the app is open.
   bool is_open() const { return window.isOpen(); }

   // Close the application.
   void
   on_close() override
   {
     window.close();
   }

   void on_key_press(sf::Event::KeyEvent e) override {
    if (e.code == sf::Keyboard::Up) {
      figure.rotate();
    }
    else if (e.code == sf::Keyboard::Left) {
      figure.move(Left);
    }
    else if (e.code == sf::Keyboard::Right) {
      figure.move(Right);
    }
    else if (e.code == sf::Keyboard::Down) {
      delay = 0.05;
    }
   }

   void draw() {
    window.clear(sf::Color::White);
    window.draw(background);
    drawBlocks(s);
    window.draw(frame);
    window.display();
   }

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
   void drawBlocks(sf::Sprite & s) {
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