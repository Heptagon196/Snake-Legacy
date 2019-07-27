#include "Menu.h"
using namespace std;

const int Width = 79;

int getLength(string str) {
    int tmp = 0;
    for (int i = 0; i < str.length(); ++ i) {
        if (str[i] < 0) {
            tmp ++;
        }
    }
    return str.length() - tmp / 3;
}

void MiddlePrint(const string& str) {
    int len = getLength(str);
    int l = (Width - len) / 2, r = Width - l - len;
    for (int i = 0; i < l; ++ i) {
        cout << ' ';
    }
    cout << str;
    for (int i = 0; i < r; ++ i) {
        cout << ' ';
    }
    cout << endl;
}

void Print(const string& str) {
    color(WHITE, BLACK);
    MiddlePrint(str);
}

void PrintSelected(const string& str) {
    color(BLACK, WHITE);
    MiddlePrint(str);
}

int Menu(const vector<string>& List) {
    if (List.size() == 0) {
        return -1;
    }
    int cur = 0;
    hidecursor();
    clearcolor();
    clear();
    gotoxy(1, 1);
    for (const string& s : List) {
        Print(s);
    }
    gotoxy(1, 1);
    PrintSelected(List[cur]);
    while (true) {
        char ch = getch();
        gotoxy(1, cur + 1);
        Print(List[cur]);
        if (ch == 'w') {
            cur --;
        } else if (ch == 's') {
            cur ++;
        } else if (ch == '\n' || ch == '\r') {
            unhidecursor();
            return cur + 1;
        } else if (ch == 'q') {
            return List.size();
        }
        if (cur == -1) {
            cur = List.size() - 1;
        }
        if (cur == List.size()) {
            cur = 0;
        }
        gotoxy(1, cur + 1);
        PrintSelected(List[cur]);
    }
    unhidecursor();
    return cur + 1;
}
