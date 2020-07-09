#include <sstream>

#include "Step.h"
#include "Figure.h"
#include "Game.h"
#include "colors.h"

Game::Game() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            field[j][i] = nullptr;
        }
    }
}

Game::Game(ifstream & in) : Game() {
    COLOR color = COLOR::WHITE;
    while (!in.eof()) {
        string line;
        getline(in, line);
        stringstream ssin(line);
        int n;
        ssin >> line >> n;
        for (int i = 0; i < n; i++) {
            getline(in, line);
            stringstream ssin(line);
            ssin >> line;
            FIGURE code = (FIGURE) line[0];
            int x = line[1] - 'A';
            int y = line[2] - '0' - 1;
            switch (code) {
                case FIGURE::KING:
                    this->field[y][x] = new King(color);
                break;
                case FIGURE::QUEEN:
                    this->field[y][x] = new Queen(color);
                break;
                case FIGURE::BISHOP:
                    this->field[y][x] = new Bishop(color);
                break;
                case FIGURE::KNIGHT:
                    this->field[y][x] = new Knight(color);
                break;
                case FIGURE::ROOK:
                    this->field[y][x] = new Rook(color);
                break;
                case FIGURE::PAWN:
                    this->field[y][x] = new Pawn(color);
                break; 
            }
        }
        color = ((color == COLOR::WHITE) ? COLOR::BLACK : COLOR::WHITE);
    }
}

Game::Game(const Game & game) : Game() {
    this->turn = game.turn;
    this->step = game.step;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (game.field[j][i]) {
                switch (game.field[j][i]->code) {
                    case FIGURE::KING:
                        this->field[j][i] = new King(*game.field[j][i]);
                    break;
                    case FIGURE::QUEEN:
                        this->field[j][i] = new Queen(*game.field[j][i]);
                    break;
                    case FIGURE::BISHOP:
                        this->field[j][i] = new Bishop(*game.field[j][i]);
                    break;
                    case FIGURE::KNIGHT:
                        this->field[j][i] = new Knight(*game.field[j][i]);
                    break;
                    case FIGURE::ROOK:
                        this->field[j][i] = new Rook(*game.field[j][i]);
                    break;
                    case FIGURE::PAWN:
                        this->field[j][i] = new Pawn(*game.field[j][i]);
                    break;
                }
            }
        }
    }
}

Game::~Game() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (this->field[j][i]) {
                delete this->field[j][i];
            }
        }
    }
} 

vector<Figure *> Game::find(FIGURE figure, COLOR color) {
    vector<Figure *> res = * new vector<Figure *>(0);
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (this->field[j][i]) {
                Figure * fig = this->field[j][i];
                if (fig->color == color && fig->code==figure) {
                    res.push_back(field[j][i]);
                }
            }
        }
    }
    return res;
}

vector<Step> Game::possible_steps() {
    vector<Step> steps = * new vector<Step>(0);
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (this->field[j][i]) {
                if (this->field[j][i]->color == this->turn) {
                    vector<Step> figure_steps = this->field[j][i]->possible_steps(*this, Point(i, j));
                    for (Step s : figure_steps) {
                        Game * game = this->make_step(s);
                        auto a = game->check(this->turn);
                        if (!(game->check(this->turn))) {
                            steps.push_back(s);
                        }
                    }
                }
            }
        }
    }
    return steps;
}

vector<Step> Game::all_steps() {
    vector<Step> steps = * new vector<Step>(0);
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (this->field[j][i]) {
                if (this->field[j][i]->color == this->turn) {
                    vector<Step> figure_steps = this->field[j][i]->possible_steps(*this, Point(i, j));
                    for (Step s : figure_steps) {
                        steps.push_back(s);
                    }
                }
            }
        }
    }
    return steps;    
}

bool Game::check(COLOR color) {
    Game * game = new Game(*this);
    game->turn = color;
    game->pass_turn();
    Figure * king = game->find(FIGURE::KING, color)[0];
    
    vector<Step> steps = game->all_steps();

    for (Step step : steps) {
        Figure * beaten = game->field[step.attacked.y][step.attacked.x];
        if (beaten) {
            if (beaten->code == FIGURE::KING) {
                return true;
            }
        }
    } 
    return false;
}

bool Game::mate(COLOR color) {
    Game * game = new Game(*this);
    game->turn = color;

    vector<Step> steps = game->possible_steps();
    return steps.size() == 0 && this->check(color);
}

Game * Game::make_step(Step step) {
    Game * new_game = new Game(*this);
    step.apply(new_game);
    new_game->pass_turn();
    return new_game;
}

void Game::print() {
    cout << "Ход: " << ((this->turn == COLOR::WHITE) ? "Белые" : "Черные") << endl;
    for (int j = 7; j >= 0; j--) {
        cout << j + 1 << " ";
        for (int i = 0; i < 8; i++) {
            if (this->field[j][i]) {
                if (this->field[j][i]->color == COLOR::WHITE) {
                    cout << BLUE << (char) this->field[j][i]->code << RESET << ' ';
                } else {
                    cout << RED << (char) this->field[j][i]->code << RESET << ' ';
                }
            } else {
                cout << "~ ";
            }
        }
        cout << endl;
    }
    cout << "  ";
    for (int i = 0; i < 8; i++) {
        cout << (char)('A' + i) << ' ';
    }
    cout << endl;
}