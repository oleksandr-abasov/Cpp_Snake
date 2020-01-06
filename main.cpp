#include <ncurses.h>
#include "snake.h"

const int MAX_COLUMNS = 20;
const int MAX_ROWS = 10;

// forward declaration - предварительное объявление
void drawGame();
void drawBox();
void print(const char *text, Cell cell);
bool hasCollided(Snake snake);
Direction readDirection(char input);

// Create a snake
const vector<Cell> snakeBody = {
        Cell(6, 5),
        Cell(5, 5),
        Cell(4, 5),
        Cell(4, 4)
};
Snake snake = Snake(snakeBody);

int main() {
    // Open curses-mode
    initscr();

    // Hide cursor
    curs_set(0);

    // How much time need to wait user input. If time passed getch will return ERR
    halfdelay(2);

    char input = 0;
    while (input != 'q') {
        // Draw game state
        drawGame();

        // Wait for user keyboard input
        input = getch();
        Direction newDirection = readDirection(input);

        // Move snake towards
        snake.turn(newDirection);
        snake.move();
        bool collided = hasCollided(snake);
        if (collided) {
            input = 'q';
        }
    }

    // Close curses-mode. Required cmd
    endwin();

    return 0;
}

bool hasCollided(Snake snake) {
    bool collided = false;
    // check if the head crossed tail
    for (Cell tailSegment : snake.tail) {
        if (snake.head == tailSegment) {
            collided = true;
            break;
        }
    }

    // check that head crossed borders
    if ((snake.head.x < 1 || snake.head.x > MAX_COLUMNS - 1)
            || (snake.head.y < 1 || snake.head.y > MAX_ROWS)) {
        collided = true;
    }
    return collided;
}

Direction readDirection(char input) {
    switch (input) {
        case 'i':
            return UP;
        case 'j':
            return LEFT;
        case 'k':
            return DOWN;
        case 'l':
            return RIGHT;
        default:
            return UNKNOWN;
    }
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





















