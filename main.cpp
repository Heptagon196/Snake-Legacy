#include "Snake.h"
#include "Conio.h"
#include <iostream>
using std::string;

SnakeMap snake;

inline void UpdateDirection(Direction& orig, Direction now) {
    if ((orig == Up && now == Down) || (orig == Down && now == Up) || (orig == Left && now == Right) || (orig == Right && now == Left))
        return ;
    orig = now;
}

int main(int argc, char* argv[]) {
    srand(time(NULL));
    hidecursor();
    snake.InitMap(40, 20);
    snake.LoadMap("snake.map");
    if (argc > 1 && (string) argv[1] == "edit") {
        snake.EditMap("snake.map");
        gotoxy(1, 21);
        unhidecursor();
        return 0;
    }
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
        gotoxy(1, 21);
        if (snake.isDead())
            break;
    }
    unhidecursor();
    return 0;
}
