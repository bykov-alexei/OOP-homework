#include "Step.h"
#include "Game.h"

void Step::apply(Game * game) {
    switch (this->type) {
        case (STEP_TYPE::USUAL):
            Figure * fig1 = game->field[attacker.y][attacker.x];
            Figure * fig2 = game->field[attacked.y][attacked.x];
            if (fig2) {
                delete fig2;
            }
            Figure * nfig1 = new Figure(*fig1);
            delete fig1;
            game->field[p1.y][p1.x] = nfig1; 
            game->field[attacker.y][attacker.x] = 0;
            nfig1->incrementSteps();
        break;
    }
}
