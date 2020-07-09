#include "Step.h"
#include "Game.h"

void Step::apply(Game * game) {
    switch (this->type) {
        case (STEP_TYPE::USUAL):
            Figure * fig1 = game->field[attacker.y][attacker.x];
            Figure * fig2 = game->field[attacked.y][attacked.x];
            // cout << "fig1 " << fig1 << " " << attacker.x << " " << attacker.y << endl;
            if (fig2) {
                delete fig2;
            }
            game->field[p1.y][p1.x] = fig1;
            game->field[attacker.y][attacker.x] = 0;
            fig1->incrementSteps();
        break;
    }
}
