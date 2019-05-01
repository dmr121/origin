#ifndef FIGURE_HPP
#define FIGURE_HPP

#include <SFML/Graphics.hpp>
#include "game.hpp"
#include <iterator>
#include <iostream>

const int M = 20;
const int N = 10;

int field[M][N] = { 0 };

// Changed figure size from 4 to 8. This allows new
// shapes to be generated.
int numShapes = 11;

int figures[11][8] = {
  1, 5, 3, 7, -1, -1, -1, -1, // I
  2, 5, 4, 7, -1, -1, -1, -1, // Z
  3, 5, 4, 6, -1, -1, -1, -1, // S
  3, 5, 4, 7, -1, -1, -1, -1, // T
  2, 5, 3, 7, -1, -1, -1, -1, // L
  3, 5, 7, 6, -1, -1, -1, -1, // J
  2, 5, 4, 3, -1, -1, -1, -1, // O
  0, 5, 2, 3, 4, 1, 6, 7, // Solid 2x4 block
  1, 5, 2, 6, -1, -1, -1 ,-1, // ??
  0, 5, 2, 4, 6, 7, -1, -1, // b
  1, 5, 3, 4, 6, 7, -1, -1, // d
};

struct Point
{
  int x, y;
};

enum Shape {
  Ishape,
  Zshape,
  Sshape,
  Tshape,
  Lshape,
  Jshape,
  Oshape,
  BigShape,
  WeirdShape,
  bShape,
  dShape,
};

enum Direction {
  Left = -1,
  Right = 1,
};

struct Figure {
  Point coordinates[8];
  Point tempCoords[8];
  int color;
  Shape shape;

  //PRECONDITION: None
  //
  //POSTCONDITION: Returns true if the new block coordinates overlap with 
  //               coordinates in the field
  bool overlaps() {
    for (int i = 0; i < 8; ++i) {
      if (coordinates[i].y != -1 && field[coordinates[i].y][coordinates[i].x] != 0) {
        return true;
      }
    }

    return false;
  }

  //PRECONDITION: None
  //
  //POSTCONDITION: Changes the color of the figure to a random color
  void changeColor() {
    color = 1 + rand() % 7;
  }

  //PRECONDITION: None
  //
  //POSTCONDITION: Changes the shape of the figure to a random shape
  void changeShape() {
    shape = static_cast<Shape>(rand() % numShapes);

    for (int i = 0; i < 8; i++) {
      if (figures[shape][i] == -1) {
        coordinates[i].x = 0;
        coordinates[i].y = -1;
      } else {
        coordinates[i].x = figures[shape][i] % 2;
        coordinates[i].y = figures[shape][i] / 2;
      }
    }
  }

  //PRECONDITION: None
  //
  //POSTCONDITION: Returns true if the figure if the figure is in bounds
  bool isInBound() {
    for (int i = 0; i < 8; i++)
      // Ignore case y coordinate of -1 which indicates a blank block
      if (coordinates[i].x < 0 || coordinates[i].x >= N || coordinates[i].y >= M)
        return 0;
      else if (field[coordinates[i].y][coordinates[i].x] && coordinates[i].y != -1)
        return 0;

    return 1;
  }

  //PRECONDITION: None
  //
  //POSTCONDITION: Rotates the figure 90 degrees
  void rotate() {
    Point p = coordinates[1]; // center of rotation
      for (int i = 0; i < 8; i++) {
        if (coordinates[i].y != -1) {
          int x = coordinates[i].y - p.y;
          int y = coordinates[i].x - p.x;
          coordinates[i].x = p.x - x;
          coordinates[i].y = p.y + y;
        }
      }
      if (!this->isInBound())
        for (int i = 0; i < 8; i++) {
          if (coordinates[i].y != -1) {
            coordinates[i] = tempCoords[i];
          }
        }
  }

  //PRECONDITION: Direction either left or right
  //
  //POSTCONDITION: Moves figure in specified direction
  void move(Direction dir) {
    std::cout << "Pickle\n";
    for (int i = 0; i < 8; i++) {
      if (coordinates[i].y != -1) {
        tempCoords[i] = coordinates[i];
        coordinates[i].x += dir;
      }
    }
    if (!this->isInBound())
      for (int i = 0; i < 8; i++) {
        if (coordinates[i].y != -1) {
          coordinates[i] = tempCoords[i];
        }
      }
  }

  //PRECONDITION: None
  //
  //POSTCONDITION: Shifts figure down on coordinate block
  void shiftDownOne() {
    for (int i = 0; i < 8; i++) {
        if (coordinates[i].y != -1) {
          tempCoords[i] = coordinates[i];
          coordinates[i].y += 1;
        }
      }
  }
};
#endif