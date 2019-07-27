#include "Snake.h"
#include "Conio.h"
#include "Menu.h"
#include <iostream>
using std::string;

SnakeMap snake;

inline void UpdateDirection(Direction& orig, Direction now) {
    if ((orig == Up && now == Down) || (orig == Down && now == Up) || (orig == Left && now == Right) || (orig == Right && now == Left))
        return ;
    orig = now;
}

void InitGame() {
    srand(time(NULL));
    hidecursor();
    snake.InitMap(40, 20);
    snake.LoadMap("snake.map");
}

void EditMode() {
    snake.EditMap("snake.map");
    gotoxy(1, 21);
}

void NormalMode() {
    snake.InitSnake();
    Direction d = (Direction)(randint(4) - 1);
    while (true) {
        char ch = readkey(0.2);
        if (ch == 'w') {
            UpdateDirection(d, Up);
        } else if (ch == 's') {
            UpdateDirection(d, Down);
        } else if (ch == 'a') {
            UpdateDirection(d, Left);
        } else if (ch == 'd') {
            UpdateDirection(d, Right);
        } else if (ch == 'q') {
            break;
        }
        snake.MoveSnake(d);
        if (snake.isDead()) {
            clearcolor();
            break;
        }
        snake.UpdateChanges();
        gotoxy(1, 21);
    }
}

int main() {
    while (true) {
        int mode = Menu({"Start Game", "Edit Map", "Exit"});
        if (mode == 1) {
            InitGame();
            NormalMode();
        } else if (mode == 2) {
            InitGame();
            EditMode();
        } else if (mode == 3) {
            unhidecursor();
            return 0;
        }
    }
    return 0;
}
