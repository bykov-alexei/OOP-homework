#ifndef GAME_FILE_H
#define GAME_FILE_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Step.h"
#include "Figure.h"

using namespace std;


class Game {
private:
    vector<Figure *> find(FIGURE figure, COLOR color);

public:
    Figure * field[8][8];
    COLOR turn = COLOR::WHITE;
    int step = 0;

    Game();
    Game(ifstream & in);
    Game(const Game & game);
    ~Game();

    void print();

    void pass_turn() { turn = ((turn == COLOR::WHITE) ? COLOR::BLACK : COLOR::WHITE); };
    void increase_step() { step++; };

    vector<Step> * possible_steps();
    vector<Step> * all_steps();

    bool check(COLOR color);
    bool mate(COLOR color);
    bool pat();

    Game * make_step(Step step);

};

#endif