#include <ncurses.h>
#include "snake.h"
#include "apple.h"
#include <string>
#include <clocale>

const int MAX_COLUMNS = 20;
const int MAX_ROWS = 10;
const int APPLES_GROWTH_CHANCE = 15;

// Keys
const char KEY_ESCAPE = 27;
const char KEY_SPACE = ' ';

// --- forward declaration - предварительное объявление ---
void systemProcess(char input);
void gameUpdate(char &input);
void drawGame();
void drawBox();
void print(string text, Cell cell);
bool hasCollided(Snake snake);
Direction readDirection(char input);
// --------------------------------------------------------

// Create a snake
const vector<Cell> snakeBody = {
        Cell(6, 5),
        Cell(5, 5),
        Cell(4, 5),
        Cell(4, 4)
};
Snake snake = Snake(snakeBody);
Apples apples = Apples(APPLES_GROWTH_CHANCE, MAX_COLUMNS, MAX_ROWS, std::mt19937());
GameState gameState = GameState::IN_PROGRESS;
int score = 4;

int main() {
    // Add UTF-8 support
    setlocale(LC_ALL, "");

    // Open curses-mode
    initscr();

    // Hide cursor
    curs_set(0);

    // How much time need to wait user input. If time passed getch will return ERR
    halfdelay(2);

    char input = 0;
    while (input != KEY_ESCAPE && input != 'q') {
        // Wait for user keyboard input
        input = getch();

        systemProcess(input);

        if (gameState == GameState::IN_PROGRESS) {
            gameUpdate(input);
        }
    }

    // Close curses-mode. Required cmd
    endwin();

    return 0;
}

void systemProcess(char input) {
    if (input == KEY_SPACE) {
        switch (gameState) {
            case GameState::IN_PROGRESS: {
                gameState = GameState::PAUSE;
                string pauseMsg = "Press Space to continue";
                print(pauseMsg, Cell(MAX_COLUMNS + 2, MAX_ROWS / 2 + 2));
                break;
            }
            case GameState::PAUSE: {
                gameState = GameState::IN_PROGRESS;
                break;
            }
            default: return;
        }
    }
}

void gameUpdate(char &input) {
    // Draw game state
    drawGame();

    Direction newDirection = readDirection(input);

    // Move snake towards
    snake.turn(newDirection);
    snake.move();

    // Eat apple
    bool hasEaten = snake.eat(apples.cells);
    if (hasEaten) score = snake.tail.size() + 1;

    // Generate apples
    apples.grow();

    // check collisions
    bool collided = hasCollided(snake);
    if (collided) input = KEY_ESCAPE;
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
            || (snake.head.y < 1 || snake.head.y > MAX_ROWS - 1)) {
        collided = true;
    }
    return collided;
}

string headSymbol(Direction direction) {
    if (direction == UP) return "∆";
    else if (direction == DOWN) return "¥";
    else if (direction == LEFT) return "≤";
    else if (direction == RIGHT) return "≥";
    else return "Q";
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
    // Clear screen
    clear();

    // Draw game borders
    drawBox();

    // Draw apples
    for (Cell apple : apples.cells) {
        print("", apple);
    }

    // Draw Snake Tail
    for (Cell tailSegment : snake.tail) {
        print("o", tailSegment);
    }

    // Draw Snake Head
    print(headSymbol(snake.direction), snake.head);

    // Draw Game Score
    string scoreMsg = "Score: " + to_string(score);
    print(scoreMsg, Cell(MAX_COLUMNS + 2, MAX_ROWS / 2));

    // Draw Pause Help
    string pauseMsg = "Press Space to pause";
    print(pauseMsg, Cell(MAX_COLUMNS + 2, MAX_ROWS / 2 + 2));

    // Flush data from buffer to display it on the screen
    refresh();
}

void drawBox() {
    // draw celling and floor
    for (int j = 0; j < MAX_COLUMNS; j++) {
        mvprintw(0, j, "_");
        mvprintw(MAX_ROWS, j, "¯");
    }

    // draw left and right walls
    for (int i = 1; i < MAX_ROWS; i++) {
        mvprintw(i, 0, "|");
        mvprintw(i, MAX_COLUMNS - 1, "|");
    }
}

void print(string text, Cell cell) {
    mvprintw(cell.y, cell.x, text.c_str());
}