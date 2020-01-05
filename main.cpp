#include <ncurses.h>

using namespace std;

// forward declaration - предварительное объявление
void draw();

int main() {
    // Переход в curses-режим
    initscr();

    // Отрисовать содержимое
    draw();

    // Ожидание нажатия какой-либо клавиши пользователем
    getch();

    // Выход из curses-режима. Обязательная команда.
    endwin();

    return 0;
}

void draw() {
    // Очистить экран
    clear();

    // Запись текста в буфер
    mvprintw(5, 5, "Hello World");

    // Вывод данных из буфера на экран
    refresh();
}






















