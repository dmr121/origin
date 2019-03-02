#ifndef FIGURE_HPP
#define FIGURE_HPP

#include <SFML/Graphics.hpp>
#include "game.hpp"

const int M = 20;
const int N = 10;

int field[M][N] = { 0 };

int figures[7][4] = {
  1, 3, 5, 7, // I
  2, 4, 5, 7, // Z
  3, 5, 4, 6, // S
  3, 5, 4, 7, // T
  2, 3, 5, 7, // L
  3, 5, 7, 6, // J
  2, 3, 4, 5, // O
};

struct Point
{
  int x, y;
} a[4], b[4];

enum Shape {
  Ishape,
  Zshape,
  Sshape,
  Tshape,
  Lshape,
  Jshape,
  Oshape,
};

enum Direction {
  Left = -1,
  Right = 1,
};

struct Figure {
  Point coordinates[4];
  Point tempCoords[4];
  int color;
  Shape shape;

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
    shape = static_cast<Shape>(rand() % 7);
    for (int i = 0; i < 4; i++) {
      coordinates[i].x = figures[shape][i] % 2;
      coordinates[i].y = figures[shape][i] / 2;
    }
  }

  //PRECONDITION: None
  //
  //POSTCONDITION: Returns true if the figure if the figure is in bounds
  bool isInBound() {
    for (int i = 0; i < 4; i++)
      if (coordinates[i].x < 0 || coordinates[i].x >= N || coordinates[i].y >= M)
        return 0;
      else if (field[coordinates[i].y][coordinates[i].x])
        return 0;

    return 1;
  }

  //PRECONDITION: None
  //
  //POSTCONDITION: Rotates the figure 90 degrees
  void rotate() {
    Point p = coordinates[1]; // center of rotation
      for (int i = 0; i < 4; i++) {
        int x = coordinates[i].y - p.y;
        int y = coordinates[i].x - p.x;
        coordinates[i].x = p.x - x;
        coordinates[i].y = p.y + y;
      }
      if (!this->isInBound())
        for (int i = 0; i < 4; i++)
          coordinates[i] = tempCoords[i];
  }

  //PRECONDITION: Direction either left or right
  //
  //POSTCONDITION: Moves figure in specified direction
  void move(Direction dir) {
    for (int i = 0; i < 4; i++) {
      tempCoords[i] = coordinates[i];
      coordinates[i].x += dir;
    }
    if (!this->isInBound())
      for (int i = 0; i < 4; i++)
        coordinates[i] = tempCoords[i];
  }

  //PRECONDITION: None
  //
  //POSTCONDITION: Shifts figure down on coordinate block
  void shiftDownOne() {
    for (int i = 0; i < 4; i++) {
        tempCoords[i] = coordinates[i];
        coordinates[i].y += 1;
      }
  }
};
#endif