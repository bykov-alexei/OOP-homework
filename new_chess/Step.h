#ifndef STEP_FILE_H
#define STEP_FILE_H

class Game;
class Figure;

enum class STEP_TYPE { USUAL, CASTLING, REPLACEMENT };
struct Point {
    int x, y;
    Point(): x(-1), y(-1) {};
    Point(int x, int y): x(x), y(y) {};
};

class Step {
public:
    STEP_TYPE type;
    
    Point attacker;
    Point attacked;
    Point p1;
    Point p2;
    char code;

    Step() {};
    // Usual step
    Step(Point attacker, Point attacked, Point p) : attacker(attacker), attacked(attacked), p1(p), type(STEP_TYPE::USUAL) {};
    // Castling
    Step(Point attacker, Point attacked, Point p1, Point p2) : attacker(attacker), attacked(attacked), p1(p1), p2(p2), type(STEP_TYPE::CASTLING) {};
    // Replacement
    // Step(Point p, Point attacker, Point attacked) : attacker(attacker), attacked(attacked), p1(p), type(STEP_TYPE::REPLACEMENT) {};

    void apply(Game * game);
};

#endif
