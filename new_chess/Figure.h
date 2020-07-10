#ifndef FIGURE_FILE_H
#define FIGURE_FILE_H

#include <iostream>
#include <vector>

using namespace std;
class Point;
class Step;
class Game;

enum class COLOR { WHITE = 1, BLACK = 0 };
enum class FIGURE { NONE = ' ', KING = 'K', QUEEN = 'Q', BISHOP = 'B', KNIGHT = 'N', ROOK = 'R', PAWN = 'p' };

class Figure {
public:
    const FIGURE code;
    COLOR color;
    int steps = 0;

    Figure() : color(COLOR::WHITE), code(FIGURE::NONE) {};
    Figure(COLOR color, FIGURE code) : color(color), code(code) {};
    Figure(const Figure& figure) : code(figure.code), color(figure.color) {};

    void incrementSteps() { this->steps += 1; };

    virtual vector<Step> * possible_steps(const Game & game, const Point& position) { return 0; };
};

class King : public Figure {
public:
    King(COLOR color) : Figure(color, FIGURE::KING) {};
    King(const Figure& figure) : Figure(figure.color, figure.code) {};
    
    vector<Step> * possible_steps(const Game & game, const Point& position);
};

class Queen : public Figure {
public:
    Queen(COLOR color) : Figure(color, FIGURE::QUEEN) {};
    Queen(const Figure& figure) : Figure(figure.color, figure.code) {};
    
    vector<Step> * possible_steps(const Game & game, const Point& position);
};

class Rook : public Figure {
public:
    Rook(COLOR color) : Figure(color, FIGURE::ROOK) {};
    Rook(const Figure& figure) : Figure(figure.color, figure.code) {};
    
    vector<Step> * possible_steps(const Game & game, const Point & position);
};

class Knight : public Figure {
public:
    Knight(COLOR color) : Figure(color, FIGURE::KNIGHT) {};
    Knight(const Figure& figure) : Figure(figure.color, figure.code) {};
    
    vector<Step> * possible_steps(const Game & game, const Point & position);
};

class Bishop : public Figure {
public:
    Bishop(COLOR color) : Figure(color, FIGURE::BISHOP) {};
    Bishop(const Figure& figure) : Figure(figure.color, figure.code) {};
    
    vector<Step> * possible_steps(const Game & field, const Point & position);
};

class Pawn : public Figure {
public:
    Pawn(COLOR color) : Figure(color, FIGURE::PAWN) {};
    Pawn(const Figure& figure) : Figure(figure.color, figure.code) {};
    
    vector<Step> * possible_steps(const Game & field, const Point & position);
};

#endif
