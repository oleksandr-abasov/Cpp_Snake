#include <ncurses.h>

using namespace std;

const int MAX_COLUMNS = 20;
const int MAX_ROWS = 10;

// forward declaration - предварительное объявление
void drawGame();
void drawBox();

int main() {
    // Переход в curses-режим
    initscr();

    // Отрисовать содержимое
    drawGame();

    // Ожидание нажатия какой-либо клавиши пользователем
    getch();

    // Выход из curses-режима. Обязательная команда.
    endwin();

    return 0;
}

void drawGame() {
    // Очистить экран
    clear();

    // Draw game borders
    drawBox();

    // Запись текста в буфер (y, x)
    mvprintw(5, 5, "Hello World");

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






















