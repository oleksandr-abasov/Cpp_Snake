#include <ncurses.h>
#include "snake.h"

const int MAX_COLUMNS = 20;
const int MAX_ROWS = 10;

// forward declaration - предварительное объявление
void drawGame();
void drawBox();
void print(const char *text, Cell cell);

// Create a snake
const vector<Cell> snakeBody = {
        Cell(6, 5),
        Cell(5, 5),
        Cell(4, 5),
        Cell(4, 4)
};
Snake snake = Snake(snakeBody);

int main() {
    // Переход в curses-режим
    initscr();

    // How much time need to wait user input. If time passed getch will return ERR
    halfdelay(2);

    char input = 0;
    while (input != 'q') {
        // Отрисовать содержимое
        drawGame();

        // Ожидание нажатия какой-либо клавиши пользователем
        input = getch();

        // Move snake towards
        snake.move();
    }

    // Выход из curses-режима. Обязательная команда.
    endwin();

    return 0;
}

void drawGame() {
    // Очистить экран
    clear();

    // Draw game borders
    drawBox();

    // Draw Snake
    for (Cell tailSegment : snake.tail) {
        print("o", tailSegment);
    }
    print("Q", snake.head);

    // Вывод данных из буфера на экран
    refresh();
}

void drawBox() {
    // draw celling and floor
    for (int j = 0; j < MAX_COLUMNS; j++) {
        mvprintw(0, j, "_");
        mvprintw(MAX_ROWS, j, "-");
    }

    // draw left and right walls
    for (int i = 1; i < MAX_ROWS; i++) {
        mvprintw(i, 0, "|");
        mvprintw(i, MAX_COLUMNS - 1, "|");
    }
}

void print(const char *text, Cell cell) {
    mvprintw(cell.y, cell.x, text);
}





















