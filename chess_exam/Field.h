//
// Created by alexei on 07.07.2020.
//

#ifndef CHESS_FIELD_H
#define CHESS_FIELD_H

#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"

#include <vector>
#include <iostream>
class Figure;

using namespace std;

class Field {
public:
    Figure * field[8][8];
    bool turn = true;
    int n_step = 0;

    Field();
    Field(vector<Figure *> figs);
    Field(const Field & field);
    ~Field();

    vector<pair<Figure *, pair<pair<int, int>, Figure *>>> steps();
    Field * apply_step(pair<Figure *, pair<pair<int, int>, Figure *>> step);
    void step(Figure * figure, pair<pair<int, int>, Figure *> step);

    bool check(bool color);
    bool mate(bool color);
//    bool pat();

    Figure * king(bool color);

    void print();
    void stepless_print();
};


#endif //CHESS_FIELD_H
