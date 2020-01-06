#ifndef CPP_SNAKE_SNAKE_H
#define CPP_SNAKE_SNAKE_H

#include <vector>

using namespace std;

class Direction {
public:
    int dx;
    int dy;

    Direction(int dx, int dy) {
        this->dx = dx;
        this->dy = dy;
    }

    bool operator==(const Direction &rhs) const {
        return dx == rhs.dx &&
               dy == rhs.dy;
    }

    bool operator!=(const Direction &rhs) const {
        return !(rhs == *this);
    }

    bool isOppositeTo(Direction direction) {
        return dx + direction.dx == 0 && dy + direction.dy == 0;
    }
};

static const Direction UP = Direction(0, -1);      // ^
static const Direction DOWN = Direction(0, 1);     // V
static const Direction LEFT = Direction(-1, 0);    // <-
static const Direction RIGHT = Direction(1, 0);    // ->
static const Direction UNKNOWN = Direction(999, 999);  // no user input

class Cell {
public:
    int x;
    int y;

    Cell(int newX, int newY) {
        this->x = newX;
        this->y = newY;
    }

    void moveHead(Direction direction) {
        this->x += direction.dx;
        this->y += direction.dy;
    }

    void moveTailToNextCell(Cell cell) {
        this->x = cell.x;
        this->y = cell.y;
    }
};

class Snake {
public:
    Cell head = Cell(0, 0);
    vector<Cell> tail;
    Direction direction = RIGHT;

    Snake(vector<Cell> body) {
        head = body.front();
        tail = vector<Cell>(body.begin() + 1, body.end());
    }

    void move() {
        for (int i = tail.size() - 1; i >= 1; i--) {
            tail[i].moveTailToNextCell(tail[i - 1]);
        }
        tail[0].moveTailToNextCell(head);
        head.moveHead(direction);
    }

    void turn(Direction newDirection) {
        if (newDirection != UNKNOWN && !direction.isOppositeTo(newDirection)) {
            direction = newDirection;
        }
    }
};

#endif //CPP_SNAKE_SNAKE_H
