#include <iostream>
#include <fstream>

#include "Game.h"
using namespace std;

int main() {
    ifstream in("fields/test1.txt");
    Game * game = new Game(in);
    game->print();
    cout << "check: " << game->check(COLOR::BLACK) << endl;
    cout << "mate: " << game->mate(COLOR::BLACK) << endl;
    // vector<Step> steps = game->possible_steps();
    // cout << steps.size() << endl;
    // for (auto step : steps) {
    //     cout << step.attacker.x << " " << (char) (step.p1.x + 'A') << " " << step.p1.y + 1 << endl;
    //     Game * new_game = game->make_step(step);
    //     new_game->print();
    //     cout << "check " << new_game->check(COLOR::WHITE) << endl;
    // }
}