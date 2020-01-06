#ifndef CPP_SNAKE_APPLE_H
#define CPP_SNAKE_APPLE_H

#include <random>
#include "snake.h"

class Apples {
private:
    static random_device randomDevice;
    mt19937 randomEngine = mt19937(randomDevice());
    uniform_int_distribution<int> distributionOfApples;
    uniform_int_distribution<int> distributionOfX;
    uniform_int_distribution<int> distributionOfY;

public:
    // list of apples
    vector<Cell> cells;
    // chance to create new apple
    int growthSpeed = 15;

    void grow() {
        int chance = distributionOfApples(randomEngine);
        if (chance <= growthSpeed) {
            Cell newApple = Cell(distributionOfX(randomEngine), distributionOfY(randomEngine));
            cells.push_back(newApple);
        }
    }

    Apples(int growthSpeed, int maxColumns, int maxRows, mt19937 randomEngine) : randomEngine(randomEngine) {
        this->growthSpeed = growthSpeed;
        distributionOfApples = uniform_int_distribution<int>(1, 100); // range of random [1, 100]
        distributionOfX = uniform_int_distribution<int>(1, maxColumns - 2);
        distributionOfY = uniform_int_distribution<int>(1, maxRows - 1);
    }
};

#endif //CPP_SNAKE_APPLE_H
