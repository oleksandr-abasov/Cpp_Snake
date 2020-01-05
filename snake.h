#ifndef CPP_SNAKE_SNAKE_H
#define CPP_SNAKE_SNAKE_H

#include <vector>

using namespace std;

class Cell {
public:
    int x;
    int y;

    Cell(int newX, int newY) {
        x = newX;
        y = newY;
    }
};

class Snake {
public:
    Cell head = Cell(0, 0);
    vector<Cell> tail;

    Snake(vector<Cell> body) {
        head = body.front();
        tail = vector<Cell>(body.begin() + 1, body.end());
    }
};

#endif //CPP_SNAKE_SNAKE_H
