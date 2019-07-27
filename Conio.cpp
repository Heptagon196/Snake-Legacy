#include "Conio.h"
#include <iostream>

#if defined(linux) || defined(__APPLE__)

bool kbhit() {
    struct termios oldt, newt;
    int ch;
    int oldf;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);
    if(ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }
    return 0;
}

int getch() {
     struct termios tm, tm_old;
     int fd = 0, ch;
     if (tcgetattr(fd, &tm) < 0) {//保存现在的终端设置
          return -1;
     }
     tm_old = tm;
     cfmakeraw(&tm);//更改终端设置为原始模式，该模式下所有的输入数据以字节为单位被处理
     if (tcsetattr(fd, TCSANOW, &tm) < 0) {//设置上更改之后的设置
          return -1;
     }
     ch = getchar();
     if (tcsetattr(fd, TCSANOW, &tm_old) < 0) {//更改设置为最初的样子
          return -1;
     }
     return ch;
}

void gotoxy(int x, int y) {
    printf("\033[%d;%dH", y, x * 2 - 1);
}

void hidecursor() {
    printf("\033[?25l");
}

void unhidecursor() {
    printf("\033[?25h");
}

void color(int a, int b) {
    printf("\033[%dm\033[%dm", b + 40, a + 30);
}

void foreground(int a) {
    printf("\033[%dm", a + 30);
}

void background(int a) {
    printf("\033[%dm", a + 40);
}

void clearcolor() {
    printf("\033[0m");
}

void clear() {
    system("clear");
}

#else

#define color_calc(fg, bg) ((fg) + 16 * (bg))

void gotoxy(int x, int y) {
    COORD c;
    c.X = x * 2 - 2;
    c.Y = y - 1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void hidecursor() {
    CONSOLE_CURSOR_INFO cursor_info = {1, 0};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

void unhidecursor() {
    CONSOLE_CURSOR_INFO cursor_info = {1, 25};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

void color(int a, int b) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color_calc(a,b));
}

void foreground(int a) {
    color(a, BLACK);
}

void background(int a) {
    color(WHITE, a);
}

void clearcolor() {
    color(WHITE, BLACK);
}

void clear() {
    system("cls");
}

#endif

double pro_time() {
    return (double) clock() / CLOCKS_PER_SEC;
}

int readkey(double _time__) {
    double time_last = pro_time();
    while (!kbhit() && (pro_time() - time_last < _time__))  ;
    if (!kbhit())
        return 0;
    while (pro_time() - time_last < _time__) ;
    return getch();
}

// random integer from 1 to m
int randint(int m) {
    return ((int)((double) rand() / RAND_MAX * (m - 1) + 0.5) + 1);
}

