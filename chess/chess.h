#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Figure {
public:
  int x, y;
  char code;
  bool color;

  Figure(): x(0), y(0), code(0), color(0) {};
  Figure(int x, int y) : x(x), y(y), code(0), color(0) {};
  Figure(int x, int y, char code, bool color) : x(x), y(y), code(code), color(color) {};

  friend std::ostream & operator<<(std::ostream & out, const Figure& fig);
  static Figure * figure_from_code(string code, bool color);

  virtual vector<pair<int, int>> beats() {return vector<pair<int, int>>();};
};

class King : public Figure {
public:
    King(int x, int y, char code, bool color) : Figure(x, y, code, color) {};
    vector<pair<int, int>> beats();
};

class Queen : public Figure {
public:
    Queen(int x, int y, char code, bool color) : Figure(x, y, code, color) {};
    vector<pair<int, int>> beats();
};

class Rook : public Figure {
public:
    Rook(int x, int y, char code, bool color): Figure(x, y, code, color) {};
    vector<pair<int, int>> beats();
};

class Knight : public Figure {
public:
    Knight(int x, int y, char code, bool color): Figure(x, y, code, color) {};
    vector<pair<int, int>> beats();
};

class Bishop : public Figure {
public:
    Bishop(int x, int y, char code, bool color): Figure(x, y, code, color) {};
    vector<pair<int, int>> beats();
};

class Pawn : public Figure {
public:
    Pawn(int x, int y, char code, bool color): Figure(x, y, code, color) {};
    vector<pair<int, int>> beats();
};


