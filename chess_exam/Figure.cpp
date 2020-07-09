//
// Created by alexei on 07.07.2020.
//

#include <string>
#include <algorithm>
#include "Figure.h"
#include "Field.h"

static inline std::string &ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(),
                                    std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
static inline std::string &rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(),
                         std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    return s;
}

// trim from both ends
static inline std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}

Figure * Figure::from_stream(std::istream &in) {
    std::string line;
    in >> line;
    line = trim(line);
    Figure *fig = nullptr;

    char code = line[0];
    int x = line[1] - 'A';
    int y = line[2] - '0' - 1;
    if (code == 'K') {
        fig = new King(x, y);
    } else if (code == QUEEN) {
        fig = new Queen(x, y);
    } else if (code == ROOK) {
        fig = new Rook(x, y);
    } else if (code == KNIGHT) {
        fig = new Knight(x, y);
    } else if (code == BISHOP) {
        fig = new Bishop(x, y);
    } else if (code == PAWN) {
        fig = new Pawn(x, y);
    }
    return fig;
}

std::ostream &operator<<(std::ostream &out, const Figure &fig) {
    out << fig.code << (char)('A' + (fig.x)) << fig.y + 1;
    return out;
}

Figure::Figure(const Figure &fig) : code(fig.code) {
    this->x = fig.x;
    this->y = fig.y;
    this->color = fig.color;
    this->steps = fig.steps;
}

void Figure::change_color(bool color) {
    this->color = color;
}

vector<step_t> King::step(const Field &field) {
    auto steps = *(new vector<step_t>(0));
    for (int i = -1; i < 2; i++) {
        int px = x + i;
        if (px >= 0 && px < 8) {
            for (int j = -1; j < 2; j++) {
                if (i == j && i == 0)
                    continue;
                int py = y + j;
                if (py >= 0 && py < 8 && (!field.field[py][px] || field.field[py][px]->color != this->color)) {
                    steps.push_back(step_t(point(px, py), field.field[py][px]));
                }
            }
        }
    }
    return steps;
}

void King::change_color(bool color) {
    Figure::change_color(color);
    this->render = (this->color) ? WKING : BKING;
}

void Queen::change_color(bool color) {
    Figure::change_color(color);
    this->render = (this->color) ? WQUEEN : BQUEEN;
}

void Rook::change_color(bool color) {
    Figure::change_color(color);
    this->render = (this->color) ? WROOK : BROOK;
}

void Bishop::change_color(bool color) {
    Figure::change_color(color);
    this->render = (this->color) ? WBISHOP : BBISHOP;
}

void Knight::change_color(bool color) {
    Figure::change_color(color);
    this->render = (this->color) ? WKNIGHT : BKNIGHT;
}

void Pawn::change_color(bool color) {
    Figure::change_color(color);
    this->render = (this->color) ? WPAWN : BPAWN;
}


vector<step_t> Queen::step(const Field &field) {
    auto steps = *(new vector<step_t>(0));
    vector<pair<int, int>> deltas = {{0, 1}, {0, -1}, {1, 0}, {-1, 0},
                                    {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
    bool blocked[8] = {};
    for (int factor = 1; factor <= 8; factor++) {
        for (int i = 0; i < 8; i++) {
            if (!blocked[i]) {
                int px = this->x + deltas[i].first * factor;
                int py = this->y + deltas[i].second * factor;
                if (px >= 0 && px < 8 && py >= 0 && py < 8) {
                    if (field.field[py][px] && field.field[py][px]->color == this->color) {
                        blocked[i] = true;
                    } else {
                        steps.push_back(step_t(point(px, py), field.field[py][px]));
                        if (field.field[py][px]) {
                            blocked[i] = true;
                        }
                    }
                }
            }
        }
    }

    return steps;
}

vector<step_t> Rook::step(const Field &field)  {
    auto steps = *(new vector<step_t>(0));

    vector<pair<int, int>> deltas = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}};
    bool blocked[4] = {};
    for (int factor = 1; factor <= 8; factor++) {
        for (int i = 0; i < 4; i++) {
            if (!blocked[i]) {
                int px = this->x + deltas[i].first * factor;
                int py = this->y + deltas[i].second * factor;
                if (px >= 0 && px < 8 && py >= 0 && py < 8) {
                    if (field.field[py][px] && field.field[py][px]->color == this->color) {
                        blocked[i] = true;
                    } else {
                        steps.push_back(step_t(point(px, py), field.field[py][px]));
                        if (field.field[py][px]) {
                            blocked[i] = true;
                        }
                    }
                }
            }
        }
    }

    return steps;
}


vector<step_t> Bishop::step(const Field &field)  {
    auto steps = *(new vector<step_t>(0));

    vector<pair<int, int>> deltas = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
    bool blocked[4] = {};
    for (int factor = 1; factor <= 8; factor++) {
        for (int i = 0; i < 4; i++) {
            if (!blocked[i]) {
                int px = this->x + deltas[i].first * factor;
                int py = this->y + deltas[i].second * factor;
                if (px >= 0 && px < 8 && py >= 0 && py < 8) {
                    if (field.field[py][px] && field.field[py][px]->color == this->color) {
                        blocked[i] = true;
                    } else {
                        steps.push_back(step_t(point(px, py), field.field[py][px]));
                        if (field.field[py][px]) {
                            blocked[i] = true;
                        }
                    }
                }
            }
        }
    }

    return steps;
}
vector<step_t> Knight::step(const Field &field) {
    auto steps = *(new vector<step_t>(0));
    vector<pair<int, int>> deltas = {{-1, 2},
                                     {1,  2},
                                     {2,  1},
                                     {2,  -1},
                                     {1,  -2},
                                     {-1, -2},
                                     {-2, -1},
                                     {-2, 1}};
    for (auto delta : deltas) {
        int px = this->x + delta.first;
        int py = this->y + delta.second;
        if (px >= 0 && px < 8 && py >= 0 && py < 8) {
            if (!field.field[py][px] || field.field[py][px]->color != this->color) {
                steps.push_back(step_t(point(px, py), field.field[py][px]));
            }
        }
    }
    return steps;
}

vector<step_t> Pawn::step(const Field &field)  {
    vector<vector<int>> params = {{6, -1, 3}, {1, 1, 4}};
    auto steps = *(new vector<step_t>(0));

    auto param = params[this->color];
    if (this->y == param[0]) {
        int px = this->x;
        int py = this->y + param[1] * 2;
        steps.push_back(step_t(point(px, py), field.field[py][px]));
    }
    int px = this->x;
    int py = this->y + param[1];
    if (px >= 0 && px < 8 && py >= 0 && py < 8) {
        if (!field.field[py][px]) {
            steps.push_back(step_t(point(px, py), field.field[py][px]));
        }
    }
    px = this->x - 1;
    py = this->y + param[1];
    if (px >= 0 && px < 8 && py >= 0 && py < 8) {
        if (field.field[py][px] && field.field[py][px]->color != this->color) {
            steps.push_back(step_t(point(py, px), field.field[py][px]));
        }
        if (field.field[px][this->y] && field.field[px][this->y]->color != this->color &&
            field.field[px][this->y]->steps == 0 && this->y == param[2]) {
            steps.push_back(step_t(point(py, px), field.field[py][px]));
        }
    }
    px = this->x + 1;
    py = this->y + param[1];
    if (px >= 0 && px < 8 && py >= 0 && py < 8) {
        if (field.field[py][px] && field.field[py][px]->color != this->color) {
            steps.push_back(step_t(point(py, px), field.field[py][px]));
        }
        if (field.field[px][this->y] && field.field[px][this->y]->color != this->color &&
            field.field[px][this->y]->steps == 0 && this->y == param[2]) {
            steps.push_back(step_t(point(py, px), field.field[py][px]));
        }
    }
    return steps;
}
