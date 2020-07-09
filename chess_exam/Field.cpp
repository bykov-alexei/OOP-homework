//
// Created by alexei on 07.07.2020.
//

#include "Field.h"
#include "Figure.h"

pair<Figure *, step_t> adopt_step(pair<Figure *, step_t> step, Field * field) {
    if (step.second.second) {
        return pair<Figure *, step_t>(field->field[step.first->y][step.first->x], step_t(point(step.second.first.first, step.second.first.second), field->field[step.second.second->y][step.second.second->x]));
    } else {
        return pair<Figure *, step_t>(field->field[step.first->y][step.first->x], step_t(point(step.second.first.first, step.second.first.second), 0));
    }
};

Field::Field() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            this->field[i][j] = nullptr;
        }
    }
}

Field::Field(vector<Figure *> figs) : Field() {
    for (auto fig: figs) {
        this->field[fig->y][fig->x] = fig;
    }
}

Field::~Field() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            delete this->field[i][j];
        }
    }
}

vector<pair<Figure *, step_t>> Field::steps() {
    vector<pair<int, int>> rook_positions = {{0, 7}, {7, 7}, {7,0}, {0,0}};
    vector<pair<int, int>> king_positions = {{3, 7}, {4, 0}};

    auto steps = *(new vector<pair<Figure *, step_t>>);
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            auto fig = field[i][j];
            if (fig && fig->color == this->turn) {
                auto fig_steps = fig->step(*this);
                for (auto step : fig_steps) {
                    steps.push_back(pair<Figure *, step_t>(fig, step));
                }
            }
        }
    }
    rook_positions = {rook_positions[turn / 2], rook_positions[turn / 2 + 1]};
    auto king_position = king_positions[turn];
    auto king = this->field[king_position.second][king_position.first];
    auto rook1 = this->field[rook_positions[0].second][rook_positions[0].first];
    auto rook2 = this->field[rook_positions[1].second][rook_positions[1].first];
    if (king && king->steps == 0 && king->color==turn && rook1 && rook1->steps == 0 && rook1->color==turn) {
        bool possible = true;
        int delta = king->x > rook1->x * 2 - 1;
        for (int i = king->x + delta; i != rook1->x; i = i + delta) {
            if (field[king->y][i]) {
                possible = false;
            }
        }
        if (possible) {
            int px = king->x + delta * 2;
            int py = king->y;
            steps.push_back(pair<Figure *, step_t>(king, step_t(point(px, py), rook1)));
        }
    }
    if (king && king->steps == 0 && king->color==turn && rook2 && rook2->steps == 0 && rook2->color==turn) {
        bool possible = true;
        int delta = king->x > rook2->x * 2 - 1;
        for (int i = king->x + delta; i != rook2->x; i = i + delta) {
            if (field[king->y][i]) {
                possible = false;
            }
        }
        if (possible) {
            int px = king->x + delta * 2;
            int py = king->y;
            steps.push_back(pair<Figure *, step_t>(king, step_t(point(px, py), rook2)));
        }
    }
    vector<pair<Figure *, step_t>> v;
    // this->stepless_print();
    for (auto step : steps) {
        Field * tmp = this->apply_step(step);
        // tmp->stepless_print();
        // cout << *step.first << " " << step.second.first.first << " " << step.second.first.second << endl;
        // step = adopt_step(step, tmp);
        // tmp->step(tmp->field[step.first->y][step.first->x], step.second);
        if (step.second.second) {
            // cout << *step.second.second << endl;
        }
        tmp->print();
        cout << tmp->check(this->turn) << endl;
       if (!tmp->check(this->turn)) {
           v.push_back(step);
       }
    }
    return v;
}

void Field::step(Figure * figure, pair<pair<int, int>, Figure *> step) {
    auto beaten = step.second;
    if (beaten && beaten->color == figure->color) {
        bool delta = (beaten->x > figure->x) * 2 - 1;
        field[beaten->y][figure->x + delta * 2] = figure;
        figure->x = figure->x + delta * 2;
        field[beaten->y][figure->x - delta] = beaten;
        beaten->x = figure->x - delta;
        field[beaten->y][figure->x] = 0;
        field[beaten->y][beaten->x] = 0;
    }
    if (beaten) {
        field[beaten->y][beaten->x] = nullptr;
        delete beaten;
    }
    field[figure->y][figure->x] = nullptr;
    field[step.first.second][step.first.first] = figure;
    figure->y = step.first.second;
    figure->x = step.first.first;
    figure->steps++;
}

Field *Field::apply_step(pair<Figure *, step_t> step) {
    Field * new_field = new Field(*this);
    step = adopt_step(step, new_field);
    new_field->step(step.first, step.second);
    return new_field;
}

Field::Field(const Field &field) : Field() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (field.field[j][i]) {
                Figure * fig = new Figure(*field.field[j][i]);
                this->field[j][i] = fig;
            }
        }
    }
    this->turn = field.turn;
    this->n_step = field.n_step;
}

bool Field::check(bool color) {
    bool turn = this->turn;
    this->turn = !color;
    auto steps = this->steps();
    // cout << steps.size() << endl;
    for (auto step : steps) {
        auto beaten = step.second.second;
        if (beaten) {
            cout << "beaten " << *beaten << endl;
        }
        if (beaten && beaten->code == KING) {
            this->turn = turn;
            return true;
        }
    }
    this->turn = turn;
    return false;
}

Figure *Field::king(bool color) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (this->field[j][i]) {
                if (this->field[j][i]->code == KING && this->field[j][i]->color == color) {
                    return this->field[j][i];
                }
            }
        }
    }
    return 0;
}

bool Field::mate(bool color) {
    bool turn = this->turn;
    this->turn = color;
    auto steps = this->steps();
    this->turn = turn;
    return steps.size() == 0;
}

void Field::print() {
    bool step_positions[8][8] = {};
    auto steps = this->steps();
    for (auto step : steps) {
        auto x = step.second.first.first;
        auto y = step.second.first.second;
        step_positions[y][x] = true;
        if (step.second.second) {
            cout << "step" << x << " " << y << " " << *step.second.second << endl;
        }
    }

    if (this->check(this->turn)) {
        cout << RED << "ШАХ!";
        // if (this->mate()) {
            // cout << "МАТ!";
        // }
        cout << RESET << endl;
    }
    cout << RED << "Ход: " << this->n_step << RESET << endl;
    cout << YELLOW << ((this->turn) ? ("Белые") : ("Черные")) << RESET << endl;
    for (int j = 7; j >= 0; j--) {
        cout << j + 1 << " ";
        for (int i = 0; i < 8; i++) {
            if (this->field[j][i]) {
                if (step_positions[j][i]) {
                    cout << YELLOW << this->field[j][i]->code << RESET;
                } else if (!this->field[j][i]->color) {
                    cout << RED << this->field[j][i]->code << RESET;
                } else {
                    cout << BLUE << this->field[j][i]->code << RESET;
                }
            } else if (step_positions[j][i]) {
                cout << YELLOW << '\176' << RESET;
            } else {
                cout << '\176';
            }
            cout << ' ';
        }
        cout << endl;
    }
    cout << "  ";
    for (char n = 'A'; n < 'H' + 1; n++) {
        cout << n << ' ';
    }
    cout << endl;
}

void Field::stepless_print() {
    cout << RED << "Ход: " << this->n_step << RESET << endl;
    cout << YELLOW << ((this->turn) ? ("Белые") : ("Черные")) << RESET << endl;
    for (int j = 7; j >= 0; j--) {
        cout << j + 1 << " ";
        for (int i = 0; i < 8; i++) {
            if (this->field[j][i]) {
                if (!this->field[j][i]->color) {
                    cout << RED << this->field[j][i]->code << RESET;
                } else {
                    cout << BLUE << this->field[j][i]->code << RESET;
                }
            } else {
                cout << '\176';
            }
            cout << ' ';
        }
        cout << endl;
    }
    cout << "  ";
    for (char n = 'A'; n < 'H' + 1; n++) {
        cout << n << ' ';
    }
    cout << endl;
}