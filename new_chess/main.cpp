#include <iostream>
#include <fstream>

#include "Game.h"
#include "colors.h"
using namespace std;

class History {
public: 
    COLOR color;
    Point from;
    Point to;
    FIGURE code;

    History() : color(COLOR::WHITE), from(Point()), to(Point()), code(FIGURE::NONE) {};
    History(Step s, Game * g) : from(s.attacker), to(s.p1), code(g->field[s.attacker.y][s.attacker.x]->code), color(g->turn) {};

    string print(ostream & out) {out << (char) code << (char) (from.x + 'A') << from.y + 1 << " -> " << (char) code << (char) (to.x + 'A') << to.y + 1;};
};
vector<vector<History>> solutions(Game * game, int n_steps);


int main() {
    cout << "Enter filename: " << endl;
    string file;
    cin >> file;
    ifstream in(file);  
    Game * game = new Game(in);
    cout << "Who goes here first? Type W or B..." << endl;
    char c;
    cin >> c;
    game->turn = (c == 'W') ? COLOR::WHITE : COLOR::BLACK;
    game->print();
    
    vector<vector<History>> ways = solutions(game, 3);
    cout << "Solutions: " << ways.size() << endl;
    for (vector<History> way : ways) {
        for (History step : way) {
            if (step.color == COLOR::WHITE) {
                cout << BLUE;
                step.print(cout);
                cout << RESET;
                cout << ";";
            } else {
                cout << RED;
                step.print(cout);
                cout << RESET;
                cout << ";";
            }
        }
        cout << endl;
    }
}

// vector<vector<History>> solutions(Game * game, int n_steps) {
//     vector<vector<History>> result;
//     if (n_steps >= 0) {
//         vector<Step> steps = game->possible_steps();
        
//         for (Step step : steps) {
//             Game * next = game->make_step(step);
//             if (next->mate(next->turn)) {
//                 result.push_back({History(step, game)});
//             } else {
//                 vector<vector<History>> _result = solutions(next, n_steps - 1);
//                 if (n_steps == 1) {
//                     if (next->mate(next->turn)) {
//                         result.push_back({History(step, game)});
//                     }
//                 }  
//                 for (vector<History> _tmp : _result) {
//                     vector<History> way = _tmp;
//                     way.insert(way.begin(), History(step, game));
//                     result.push_back(way);
//                 }
//             }
//         }
//         return result;
//     } else {
//         return {};
//     }
// }

vector<vector<History>> solutions(Game * game, int n_steps) {
    vector<vector<History>> result;
    if (n_steps >= 0) {
        vector<Step> steps = game->possible_steps();
        
        for (Step step : steps) {
            Game * next = game->make_step(step);
            vector<vector<History>> _result = solutions(next, n_steps - 1);
            if (n_steps == 1) {
                if (next->mate(next->turn)) {
                    result.push_back({History(step, game)});
                }
            }  
            for (vector<History> _tmp : _result) {
                vector<History> way = _tmp;
                way.insert(way.begin(), History(step, game));
                result.push_back(way);
            }
        }
        return result;
    } else {
        return {};
    }
}