#include "Figure.h"
#include "Step.h"
#include "Game.h"

vector<Step> King::possible_steps(const Game & game, const Point & position) {
    int x = position.x;
    int y = position.y;

    vector<Step> steps = *(new vector<Step>());

    for (int i = ((x == 0) ? 0 : -1); i <= ((x == 7) ? 0 : 1); i++) {
        int px = x + i;
        for (int j = ((y == 0) ? 0 : -1); j <= ((y == 7) ? 0 : 1); j++) {
            if (i == j && i == 0)
                continue;
            int py = y + j;
            if (!game.field[py][px] || game.field[py][px]->color != this->color) {
                steps.push_back(Step(Point(x, y), Point(px, py), Point(px, py)));
            }
        }
    }
    return steps;
}

vector<Step> Queen::possible_steps(const Game & game, const Point & position) {
    int x = position.x;
    int y = position.y;

    vector<Step> steps = *(new vector<Step>());
    vector<pair<int, int>> deltas = {{0, 1}, {0, -1}, {1, 0}, {-1, 0},
                                    {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
    bool blocked[8] = {};
    for (int factor = 1; factor <= 8; factor++) {
        for (int i = 0; i < 8; i++) {
            if (!blocked[i]) {
                int px = x + deltas[i].first * factor;
                int py = y + deltas[i].second * factor;
                if (px >= 0 && px < 8 && py >= 0 && py < 8) {
                    if (game.field[py][px] && game.field[py][px]->color == this->color) {
                        blocked[i] = true;
                    } else {
                        steps.push_back(Step(Point(x, y), Point(px, py), Point(px, py)));
                        if (game.field[py][px]) {
                            blocked[i] = true;
                        }
                    }
                }
            }
        }
    }
    return steps;
}

vector<Step> Rook::possible_steps(const Game & game, const Point & position) {
    int x = position.x;
    int y = position.y;

    vector<Step> steps = *(new vector<Step>());
    vector<Point> deltas = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    bool blocked[4] = {};
    for (int factor = 1; factor <= 8; factor++) {
        for (int i = 0; i < 4; i++) {
            if (!blocked[i]) {
                int px = x + deltas[i].x * factor;
                int py = y + deltas[i].y * factor;
                if (px >= 0 && px < 8 && py >= 0 && py < 8) {
                    if (game.field[py][px] && game.field[py][px]->color == this->color) {
                        blocked[i] = true;
                    } else {
                        steps.push_back(Step(Point(x, y), Point(px, py), Point(px, py)));
                        if (game.field[py][px]) {
                            blocked[i] = true;
                        }
                    }
                }
            }
        }
    }
    return steps;
}

vector<Step> Knight::possible_steps(const Game & game, const Point & position) {
    int x = position.x;
    int y = position.y;

    vector<Step> steps = *(new vector<Step>());

    vector<Point> deltas = {{-1, 2},
                            {1,  2},
                            {2,  1},
                            {2,  -1},
                            {1,  -2},
                            {-1, -2},
                            {-2, -1},
                            {-2, 1}};
    for (auto delta : deltas) {
        int px = x + delta.x;
        int py = y + delta.y;
        if (px >= 0 && px < 8 && py >= 0 && py < 8) {
            if (!game.field[py][px] || game.field[py][px]->color != this->color) {
                steps.push_back(Step(Point(x, y), Point(px, py), Point(px, py)));
            }
        }
    }
    return steps;
}

vector<Step> Bishop::possible_steps(const Game & game, const Point & position) {
    int x = position.x;
    int y = position.y;

    vector<Step> steps = *(new vector<Step>());
    vector<Point> deltas = {{1, 1}, {1, -1}, {1, -1}, {-1, -1}};
    bool blocked[4] = {};
    for (int factor = 1; factor <= 8; factor++) {
        for (int i = 0; i < 4; i++) {
            if (!blocked[i]) {
                int px = x + deltas[i].x * factor;
                int py = y + deltas[i].y * factor;
                if (px >= 0 && px < 8 && py >= 0 && py < 8) {
                    if (game.field[py][px] && game.field[py][px]->color == this->color) {
                        blocked[i] = true;
                    } else {
                        steps.push_back(Step(Point(x, y), Point(px, py), Point(px, py)));
                        if (game.field[py][px]) {
                            blocked[i] = true;
                        }
                    }
                }
            }
        }
    }
    return steps;
}

vector<Step> Pawn::possible_steps(const Game & game, const Point & position) {
    int x = position.x;
    int y = position.y;

    vector<Step> steps = *(new vector<Step>());
    vector<vector<int>> params = {{6, -1, 3}, {1, 1, 4}};

    auto param = params[(int) this->color];
    // First Pawn step
    if (y == param[0]) {
        int px = x;
        int py = y + param[1] * 2;
        steps.push_back(Step(Point(x, y), Point(px, py), Point(px, py)));
    }
    int px = x;
    int py = y + param[1];
    // Usual Pawn step
    if (px >= 0 && px < 8 && py >= 0 && py < 8) {
        if (!game.field[py][px]) {
            steps.push_back(Step(Point(x, y), Point(px, py), Point(px, py)));
        }
    }
    px = x - 1;
    py = y + param[1];
    if (px >= 0 && px < 8 && py >= 0 && py < 8) {
        if (game.field[py][px] && game.field[py][px]->color != this->color) {
            steps.push_back(Step(Point(x, y), Point(px, py), Point(px, py)));
        }
        if (game.field[px][y] && game.field[px][y]->color != this->color &&
            game.field[px][y]->steps == 0 && y == param[2]) {
            steps.push_back(Step(Point(x, y), Point(px, py), Point(px, py)));
        }
    }
    px = x + 1;
    py = y + param[1];
    if (px >= 0 && px < 8 && py >= 0 && py < 8) {
        if (game.field[py][px] && game.field[py][px]->color != this->color) {
            steps.push_back(Step(Point(x, y), Point(px, py), Point(px, py)));
        }
        if (game.field[px][y] && game.field[px][y]->color != this->color &&
            game.field[px][y]->steps == 0 && y == param[2]) {
            steps.push_back(Step(Point(x, y), Point(px, py), Point(py, px)));
        }
    }
    return steps;
}