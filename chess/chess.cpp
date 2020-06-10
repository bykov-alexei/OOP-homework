#include <iostream>
#include "chess.h"

std::ostream& operator<<(std::ostream & out, const Figure& fig) {
  char x = 'A' + (int)(fig.x);
  out << fig.code << x << fig.y + 1;
}

Figure * Figure::figure_from_code(string code, bool color) {
    char c = code.at(0);
    int x = code.at(1) - 'A';
    int y = code.at(2) - '0' - 1;
    if (c == 'K') {
        auto k = new King(x, y, c, color);
        return k;
    } else if (c == 'Q') {
        auto q = new Queen(x, y, c, color);
        return q;
    } else if (c == 'R') {
        auto r = new Rook(x, y, c, color);
        return r;
    } else if (c == 'N') {
        auto k = new Knight(x, y, c, color);
        return k;
    } else if (c == 'B') {
        auto b = new Bishop(x, y, c, color);
        return b;
    } else if (c == 'p') {
        auto p = new Pawn(x, y, c, color);
        return p;
    }
    auto f = new Figure(x, y, c, color);
    return f;
}

vector<pair<int, int>> King::beats() {
    int x = this->x;
    int y = this->y;
    vector<pair<int, int>> points(0);
    for (int i = -1; i < 2; i++) {
        int px = x + i;
        if (px >= 0 && px < 8) {
            for (int j = -1; j < 2; j++) {
                if (i == j && i == 0)
                    continue;
                int py = y + j;
                if (py >= 0 && py < 8) {
                    points.push_back(pair<int, int>(px, py));
                }
            }
        }
    }
    return points;
}

vector<pair<int, int>> Queen::beats() {
    vector<pair<int, int>> res;
    vector<pair<int, int>> deltas = {{0, 1}, {1, 0}, {0, -1}, {-1, 0},
                                     {1, 1}, {-1, 1}, {1, -1}, {-1, -1}};
    for (int i = 1; i < 8; i++) {
        for (auto delta : deltas) {
            int px = delta.first * i + this->x;
            int py = delta.second * i + this->y;
            if (px >= 0 && px < 8 && py >= 0 && py < 8) {
                res.push_back({px, py});
            }
        }
    }
    return res;
}

vector<pair<int, int>> Rook::beats() {
    vector<pair<int, int>> res;
    vector<pair<int, int>> deltas = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    for (int i = 1; i < 8; i++) {
        for (auto delta : deltas) {
            int px = delta.first * i + this->x;
            int py = delta.second * i + this->y;
            if (px >= 0 && px < 8 && py >= 0 && py < 8) {
                res.push_back({px, py});
            }
        }
    }
    return res;
}

vector<pair<int, int>> Bishop::beats() {
    vector<pair<int, int>> res;
    vector<pair<int, int>> deltas = {{-1, -1}, {-1, 1}, {1, -1}, {1, 1}};
    for (int i = 1; i < 8; i++) {
        for (auto delta : deltas) {
            int px = delta.first * i + this->x;
            int py = delta.second * i + this->y;
            if (px >= 0 && px < 8 && py >= 0 && py < 8) {
                res.push_back({px, py});
            }
        }
    }
    return res;
}

vector<pair<int, int>> Pawn::beats() {
    vector<pair<int, int>> res;
    if (color) {
        if (this->x - 1 >= 0 && this->y + 1 < 8)
            res.push_back({this->x - 1, this->y + 1});
        if (this->x + 1 < 8 && this->y + 1 < 8) {
            res.push_back({this->x + 1, this->y + 1});
        }
        return res;
    } else {
        if (this->x - 1 >= 0 && this->y - 1 >= 0)
            res.push_back({this->x - 1, this->y - 1});
        if (this->x + 1 < 8 && this->y - 1 >= 0) {
            res.push_back({this->x + 1, this->y - 1});
        }
        return res;
    }
}

vector<pair<int, int>> Knight::beats() {
    vector<pair<int, int>> res;
    vector<pair<int, int>> deltas = {{-1, 2}, {1, 2}, {2, 1}, {2, -1},
                                     {1, -2}, {-1, -2}, {-2, -1}, {-2, 1}};
    for (auto delta : deltas) {
        int p1x = this->x + delta.first;
        int p1y = this->y + delta.second;
        if (p1x >= 0 && p1x < 8 && p1y >= 0 && p1y < 8) {
            res.push_back({p1x, p1y});
        }
    }
    return res;
}
