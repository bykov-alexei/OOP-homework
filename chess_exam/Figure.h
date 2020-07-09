//
// Created by alexei on 07.07.2020.
//

#ifndef CHESS_FIGURE_H
#define CHESS_FIGURE_H

const char KING = 'K';
const char QUEEN = 'Q';
const char ROOK = 'R';
const char KNIGHT = 'N';
const char BISHOP = 'B';
const char PAWN = 'p';
const char DEFAULT = ' ';

const wchar_t WKING = L'♔';
const wchar_t WQUEEN = L'♕';
const wchar_t WROOK = L'♖';
const wchar_t WBISHOP = L'♗';
const wchar_t WKNIGHT = L'♘';
const wchar_t WPAWN = L'♙';
const wchar_t BKING = L'♚';
const wchar_t BQUEEN = L'♛';
const wchar_t BROOK = L'♜';
const wchar_t BBISHOP = L'♝';
const wchar_t BKNIGHT = L'♞';
const wchar_t BPAWN = L'♟';
const wchar_t VOID = L' ';


#include <iostream>
#include <vector>

using namespace std;

typedef pair<int, int> point;

class Field;

class Figure {

public:
    int x, y;
    bool color = 0;
    const char code;
    wchar_t render;
    int steps = 0;

    Figure() : x(0), y(0), color(false), code(DEFAULT), render(VOID) {};
    Figure(const Figure & fig);

    friend std::ostream & operator<<(ostream & out, const Figure & fig);
    static Figure * from_stream(istream & in);

    virtual vector<pair<point, Figure *>> step(const Field & field) {return vector<pair<point, Figure *>>();};

    virtual void change_color(bool color);
protected:
    Figure(int x, int y, int code) : x(x), y(y), code(code), render(VOID) {};
};

typedef pair<point, Figure *> step_t;

class King : public Figure {
public:
    King(int x, int y) : Figure(x, y, KING) {};
    vector<step_t> step(const Field & field);
    void change_color(bool color);
};

class Queen : public Figure {
public:
    Queen(int x, int y) : Figure(x, y, QUEEN) {};
    vector<step_t> step(const Field & field);
    void change_color(bool color);
};

class Rook : public Figure {
public:
    Rook(int x, int y) : Figure(x, y, ROOK) {};
    vector<step_t> step(const Field & field);
    void change_color(bool color) override;
};

class Knight : public Figure {
public:
    Knight(int x, int y) : Figure(x, y, KNIGHT) {};
    vector<step_t> step(const Field & field);
    void change_color(bool color);
};

class Bishop : public Figure {
public:
    Bishop(int x, int y) : Figure(x, y, BISHOP) {};
    vector<step_t> step(const Field & field);
    void change_color(bool color);
};

class Pawn : public Figure {
public:
    Pawn(int x, int y) : Figure(x, y, PAWN) {};
    vector<step_t> step(const Field & field);
    void change_color(bool color);
};

#endif