#include <SFML/Graphics.hpp>

#include <iostream>
#include <random>

using namespace sf;


/// An event listener is an interface between an
/// event source (device? set of devices?) -- something
/// that can be polled for events or input, and
/// an application (component) that needs to respond
/// to those events.
///
/// An (abstract) event listener provides a set of
/// operations to be called (these are called callbacks)
/// when various events occur.
struct event_listener
{
  // Window events
  virtual void on_close() { }
  virtual void on_gain_focus() { }
  virtual void on_lose_focus() { }
  virtual void on_resize(sf::Event::SizeEvent) { }

  // Mouse events
  virtual void on_mouse_button_press(sf::Event::MouseButtonEvent) { }
  virtual void on_mouse_button_release(sf::Event::MouseButtonEvent) { }

  // Keyboard events
  virtual void on_key_press(sf::Event::KeyEvent) { }
  virtual void on_key_release(sf::Event::KeyEvent) { }
};


/// The event source notifies one or more listeners
/// about events.
///
/// FIXME: This is a bad name for a class.
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
    case Event::Closed:
      return notify([e](event_listener* l) { l->on_close(); });

    case Event::Resized:
      return notify([e](event_listener* l) { l->on_resize(e.size); });
    
    case Event::MouseButtonPressed:
      return notify([e](event_listener* l) { l->on_mouse_button_press(e.mouseButton); });
    case Event::MouseButtonReleased:
      return notify([e](event_listener* l) { l->on_mouse_button_release(e.mouseButton); });

    case Event::KeyPressed:
      return notify([e](event_listener* l) { l->on_key_press(e.key); });
    case Event::KeyReleased:
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



// The (square?) size of a tile.
int ts = 54;

// Some offset between the window and the game board.
Vector2i offset(48, 24);

/// A piece (or jewel) on the grid.
struct piece
{
  piece()
    : x(), y(), col(), row(), kind(), match(), alpha(255)
  { }

  friend void
  swap(piece& a, piece& b)
  {
    std::swap(a.col, b.col);
    std::swap(a.row, b.row);
  }

  int x, y; // The graphical position of the tile
  int col, row; // The row and column of the piece
  int kind; // The kind of gem.
  int match; // The number of matches?
  int alpha; // Transparency
};

// Encapsulate the game board. Note that the actual game board is 10x10,
// but only the inner 8 rows and columns are used.
struct bejeweled_board
{
  // Construct a randomly generated board.
  bejeweled_board(std::minstd_rand& prng)
  {
    std::uniform_int_distribution<> dist(0, 2);
    for (int i = 1; i <= 8; i++) {
      for (int j = 1; j <= 8; j++) {
        grid[i][j].kind = dist(prng);
        grid[i][j].col = j;
        grid[i][j].row = i;
        grid[i][j].x = j * ts;
        grid[i][j].y = i * ts;
      }
    }
  }

  // The type of a row.
  using row = piece (&)[10];

  // The type of a (constant) row.
  using const_row = piece const (&)[10];

  // Returns the rth row in the array.
  row operator[](int r) { return grid[r]; }

  // Returns the rth row in the array.
  const_row operator[](int r) const { return grid[r]; }

  friend std::ostream&
  operator<<(std::ostream& os, bejeweled_board const& b)
  {
    for (int i = 1; i <= 8; ++i) {
      for (int j = 1; j <= 8; ++j) {
        os << b[i][j].kind << ' ';
      }
      os << '\n';
    }
    return os;
  }

  piece grid[10][10];
};

// A container for graphical resources.
struct bejeweled_graphics
{
  bejeweled_graphics()
  {
    textures[0].loadFromFile("images/background.png");
    textures[1].loadFromFile("images/gems.png");
    background.setTexture(textures[0]);
    gems.setTexture(textures[1]);
  }

  // Textures loaded from disk.
  sf::Texture textures[2];

  // Drawable sprites.
  sf::Sprite background;
  sf::Sprite gems;
};

// The actual application.
struct bejeweled_app : event_listener
{
  bejeweled_app()
    : prng(std::random_device()()),
      window(VideoMode(740, 480), "Match-3 Game!"),
      grid(prng)
  {
    window.setFramerateLimit(120);
  }

  // Returns true if the app is open.
  bool is_open() const { return window.isOpen(); }

  // Close the application.
  void
  on_close() override
  {
    window.close();
  }

  void 
  on_mouse_button_press(sf::Event::MouseButtonEvent e) override
  {
    if (e.button == Mouse::Left) {
      // Only register clicks if we're not currently animating.
      if (!swapping && !moving) {
        click++;
      }
    }
    
    Vector2i pos = Mouse::getPosition(window) - offset;

    // Process the mouse click.
    if (click == 1) {
      // Select the first gem.
      x0 = pos.x / ts + 1;
      y0 = pos.y / ts + 1;
    }
    if (click == 2) {
      // Select the second gem.
      x1 = pos.x / ts + 1;
      y1 = pos.y / ts + 1;
      if (abs(x1 - x0) + abs(y1 - y0) == 1) {
        // Swap the grid pieces.
        std::swap(grid[y0][x0], grid[y1][x1]);
        swapping = 1;
        click = 0;
      } else {
        // Ignore the second click.
        click = 1;
      }
    }
  }

  void
  find_matches()
  {
    for (int i = 1; i <= 8; i++) {
      for (int j = 1; j <= 8; j++) {
        // Count matches to the left and right.
        if (grid[i][j].kind == grid[i + 1][j].kind) {
          if (grid[i][j].kind == grid[i - 1][j].kind) {
            for (int n = -1; n <= 1; n++)
              grid[i + n][j].match++;
          }
        }

        // Count matches to the top and bottom.
        if (grid[i][j].kind == grid[i][j + 1].kind) {
          if (grid[i][j].kind == grid[i][j - 1].kind) {
            for (int n = -1; n <= 1; n++)
              grid[i][j + n].match++;
          }
        }
      }
    }
  }

  void
  animate_moves()
  {
    moving = false;
    for (int i = 1; i <= 8; i++) {
      for (int j = 1; j <= 8; j++) {
        piece& p = grid[i][j];
        int dx, dy;
        for (int n = 0; n < 4; n++) { // 4 - speed
          dx = p.x - p.col * ts;
          dy = p.y - p.row * ts;
          if (dx)
            p.x -= dx / abs(dx);
          if (dy)
            p.y -= dy / abs(dy);
        }
        if (dx || dy)
          moving = true;
      }
    }
  }

  void
  animate_deletions()
  {
    if (!moving) {
      for (int i = 1; i <= 8; i++) {
        for (int j = 1; j <= 8; j++) {
          if (grid[i][j].match) {
            if (grid[i][j].alpha > 10) {
              grid[i][j].alpha -= 10;
              moving = true;
            }
          }
        }
      }
    }
  }

  void
  update_score()
  {
    // Get Compute the scope.
    int score = 0;
    for (int i = 1; i <= 8; i++) {
      for (int j = 1; j <= 8; j++)
        score += grid[i][j].match;
    }

    // Restore selected tiles if the swap didn't register a score.
    // FIXME: This belongs in a separate function.
    if (swapping && !moving) {
      if (!score)
        std::swap(grid[y0][x0], grid[y1][x1]);
      swapping = false;
    }
  }

  void
  update_grid()
  {
    // Update grid
    if (!moving) {
      for (int i = 8; i > 0; i--) {
        for (int j = 1; j <= 8; j++) {
          if (grid[i][j].match) {
            for (int n = i; n > 0; n--) {
              if (!grid[n][j].match) {
                swap(grid[n][j], grid[i][j]);
                break;
              }
            }
          }
        }
      }

      std::uniform_int_distribution<> dist(0, 6);

      // Generate new tiles to replace the old ones.
      for (int j = 1; j <= 8; j++) {
        for (int i = 8, n = 0; i > 0; i--) {
          if (grid[i][j].match) {
            grid[i][j].kind = dist(prng);
            grid[i][j].y = -ts * n++;
            grid[i][j].match = 0;
            grid[i][j].alpha = 255;
          }
        }
      }
    }
  }

  void
  draw()
  {
    // Draw the background.
    window.draw(graph.background);

    // Draw each tile.
    for (int i = 1; i <= 8; i++) {
      for (int j = 1; j <= 8; j++) {
        piece p = grid[i][j];
        graph.gems.setTextureRect(IntRect(p.kind * 49, 0, 49, 49));
        graph.gems.setColor(Color(255, 255, 255, p.alpha));
        graph.gems.setPosition(p.x, p.y);
        graph.gems.move(offset.x - ts, offset.y - ts);
        window.draw(graph.gems);
      }
    }

    // Display the drawn window.
    window.display();
  }

  // The pseudo random number generator.
  std::minstd_rand prng;

  // The game window.
  sf::RenderWindow window;

  // A container for graphical resources
  bejeweled_graphics graph;

  // The game board
  bejeweled_board grid;

  // Game state.
  int x0, y0; // The grid location of the first gem.
  int x1, y1; // The grid location of the second gem.
  int click = 0; // Indicates number of gems selected.

  bool swapping = false; // True if swapping tiles.
  bool moving = false; // True if moving.
};

struct debug_listener : event_listener
{
  debug_listener(bejeweled_app& a)
    : app(&a)
  { }
  
  void on_close() override
  {
    std::cerr << "closing...\n";
  }

  void on_mouse_button_press(sf::Event::MouseButtonEvent e) override
  {
    std::cout << "mouse press: " << e.x << ' ' << e.y << '\n';
    std::cout << "  - click: " << app->click << '\n';
    std::cout << "  - moving: " << app->moving << '\n';
    std::cout << "  - swapping: " << app->swapping << '\n';
  }
  void on_mouse_button_release(sf::Event::MouseButtonEvent e) override
  {
    std::cout << "mouse release: " << e.x << ' ' << e.y << '\n';
    std::cout << "  - click: " << app->click << '\n';
    std::cout << "  - moving: " << app->moving << '\n';
    std::cout << "  - swapping: " << app->swapping << '\n';
  }

  bejeweled_app* app;
};

int
main()
{
  // Create the app data and window.
  bejeweled_app app;

  // Create a debugger
  debug_listener debug(app);

  // Construct the event loop and listeners.  
  event_source events(app.window);
  events.listen(app);
  events.listen(debug);


  while (app.is_open()) {
    // Poll for events.
    events.poll();

    // Update game state.
    app.find_matches();
    app.animate_moves();
    app.animate_deletions();
    app.update_score();
    app.update_grid();

    // Redraw the game.
    app.draw();
  }
  
  return 0;
}
