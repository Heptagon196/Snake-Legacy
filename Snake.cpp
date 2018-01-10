#include <iostream>
#include <fstream>
#include <map>
#include "Snake.h"
#include "Conio.h"

using std::cout;
using std::map;
using std::ifstream;
using std::ofstream;
using std::endl;
using std::string;
using std::pair;

int lastfg = -1, lastbg = -1;

BlockType::BlockType(int fg, int bg, string content) : fg(fg), bg(bg), content(content) {}

void BlockType::Show() const {
    if (fg != lastfg) {
        foreground(fg);
        lastfg = fg;
    }
    if (bg != lastbg) {
        background(bg);
        lastbg = bg;
    }
    cout << content;
}

BlockType VoidBlock(WHITE, WHITE, "  ");
BlockType HeadBlock(WHITE, BLUE, "  ");
BlockType BodyBlock(WHITE, GREEN, "  ");
BlockType WallBlock(WHITE, YELLOW, "  ");
BlockType FoodBlock(WHITE, RED, "  ");
BlockType Cursor(WHITE, BLACK, "  ");

SnakeBody::SnakeBody(int x, int y, int prv, int nxt) : x(x), y(y), prv(prv), nxt(nxt) {}
SnakeBody::SnakeBody(pair<int, int> p, int prv, int nxt) : x(p.first), y(p.second), prv(prv), nxt(nxt) {}

void SnakeMap::InitMap(int W, int H) {
    clear();
    dead = false;
    this->W = W;
    this->H = H;
    for (int y = 1; y <= H; ++ y) {
        for (int x = 1; x <= W; ++ x) {
            if (x == 1 || x == W || y == 1 || y == H)
                Map[x][y] = &WallBlock;
            else
                Map[x][y] = &VoidBlock;
            Map[x][y]->Show();
        }
#ifdef linux
        cout << endl;
#endif
    }
}

pair<int, int> SnakeMap::GetRandomPos() {
    int x, y;
    do {
        x = randint(W);
        y = randint(H);
    } while (Map[x][y] != &VoidBlock);
    return {x, y};
}

#define SetMap(pos, attr) Map[Body[pos].x][Body[pos].y] = &attr; updates.push_back({Body[pos].x, Body[pos].y});

void SnakeMap::NewFood() {
    food = GetRandomPos();
    Map[food.first][food.second] = &FoodBlock;
    updates.push_back({food.first, food.second});
}

void SnakeMap::InitSnake() {
    Body.push_back({GetRandomPos(), 0, 0});
    head = tail = 0;
    SetMap(head, HeadBlock);
    NewFood();
}

void SnakeMap::MoveHeadTo(int x, int y) {
    if (Body.size() == 1) {
        SetMap(head, VoidBlock);

        Body[head] = {x, y, 0, 0};
        SetMap(head, HeadBlock);
    } else {
        SetMap(tail, VoidBlock);

        int p = tail;
        tail = Body[tail].prv;
        SetMap(head, BodyBlock);

        Body[head].prv = p;
        Body[p].nxt = head;
        head = p;
        Body[head].x = x;
        Body[head].y = y;
        SetMap(head, HeadBlock);
    }
}

void SnakeMap::MoveSnake(Direction d) {
    int x = Body[head].x;
    int y = Body[head].y;
    if (d == Up) {
        y --;
    } else if (d == Down) {
        y ++;
    } else if (d == Left) {
        x --;
    } else {
        x ++;
    }
    if (Map[x][y] == &FoodBlock) {
        AddToHead(x, y);
        NewFood();
    } else if (Map[x][y] == &VoidBlock) {
        MoveHeadTo(x, y);
    } else {
        dead = true;
    }
}

void SnakeMap::AddToHead(int x, int y) {
    Body.push_back({x, y, 0, head});
    SetMap(head, BodyBlock);

    head = (Body[head].prv = Body.size() - 1);
    SetMap(head, HeadBlock);
}

bool SnakeMap::isDead() {
    return dead;
}

void SnakeMap::LoadMap(string filename) {
    ifstream fin(filename);
    string l;
    while (fin >> l) {
        if (l == "wall") {
            int x, y;
            fin >> x >> y;
            Map[x][y] = &WallBlock;
            gotoxy(x, y);
            WallBlock.Show();
        }
    }
    fin.close();
}

void SnakeMap::SaveMap(string filename) {
    ofstream fout(filename);
    for (int x = 1; x <= W; ++ x)
        for (int y = 1; y <= H; ++ y)
            if (x != 1 && x != W && y != 1 && y != H && Map[x][y] == &WallBlock)
                fout << "wall " << x << ' ' << y << endl;
    fout.close();
}

void SnakeMap::UpdateChanges() {
    for (const pair<int, int>& p : updates) {
        gotoxy(p.first, p.second);
        Map[p.first][p.second]->Show();
    }
    updates.clear();
}

#define Check(ch) (isdigit(ch) && ch - '0' < TypeID.size())
void SnakeMap::EditMap(string filename) {
    LoadMap(filename);
    int curx = 1, cury = 1;
    gotoxy(curx, cury);
    Cursor.Show();
    map<char, BlockType*> TypeID= {
        {'0', &VoidBlock},
        {'1', &WallBlock}
    };
    while (true) {
        char ch = getch();
        int bakcurx = curx;
        int bakcury = cury;
        if (ch == 'w') {
            cury --;
        } else if (ch == 's') {
            cury ++;
        } else if (ch == 'a') {
            curx --;
        } else if (ch == 'd') {
            curx ++;
        } else if (ch == 'q') {
            break;
        } else if (Check(ch)) {
            Map[curx][cury] = TypeID[ch];
            gotoxy(curx, cury);
            TypeID[ch]->Show();
        } else if (ch == 'h') {
            while (!Check(ch))
                ch = getch();
            for (int x = 1; x <= curx; x ++) {
                Map[x][cury] = TypeID[ch];
                gotoxy(x, cury);
                TypeID[ch]->Show();
            }
        } else if (ch == 'l') {
            while (!Check(ch))
                ch = getch();
            for (int x = curx; x <= W; x ++) {
                Map[x][cury] = TypeID[ch];
                gotoxy(x, cury);
                TypeID[ch]->Show();
            }
        } else if (ch == 'k') {
            while (!Check(ch))
                ch = getch();
            for (int y = 1; y <= cury; y ++) {
                Map[curx][y] = TypeID[ch];
                gotoxy(curx, y);
                TypeID[ch]->Show();
            }
        } else if (ch == 'j') {
            while (!Check(ch))
                ch = getch();
            for (int y = cury; y <= H; y ++) {
                Map[curx][y] = TypeID[ch];
                gotoxy(curx, y);
                TypeID[ch]->Show();
            }
        }
        if (curx < 1)
            curx = W;
        if (curx > W)
            curx = 1;
        if (cury < 1)
            cury = H;
        if (cury > H)
            cury = 1;
        if (curx == bakcurx && cury == bakcury)
            continue;
        gotoxy(bakcurx, bakcury);
        Map[bakcurx][bakcury]->Show();
        gotoxy(curx, cury);
        Cursor.Show();
    }
    SaveMap(filename);
}
#undef Check
