#ifndef HEPTAGON_SNAKE_H
#define HEPTAGON_SNAKE_H
#include <string>
#include <vector>

class BlockType {
    private:
        int fg, bg;
        std::string content;
    public:
        BlockType(int fg, int bg, std::string content);
        void Show() const;
};

enum Direction {
    Up,
    Down,
    Left,
    Right
};

class SnakeBody {
    public:
        int x, y, prv, nxt;
        SnakeBody(int x, int y, int prv, int nxt);
        SnakeBody(std::pair<int, int> p, int prv, int nxt);
};

class SnakeMap {
    //private:
    public:
        int head, tail;
        std::pair<int, int> food;
        int W, H;
        BlockType* Map[100][100];
        std::vector<SnakeBody> Body;
        bool dead;

        void MoveHeadTo(int x, int y);
        void AddToHead(int x, int y);
        void NewFood();
        std::pair<int, int> GetRandomPos();
    public:
        void InitMap(int W, int H);
        void LoadMap(std::string filename);
        void SaveMap(std::string filename);
        void EditMap(std::string filename);

        void InitSnake();
        void MoveSnake(Direction d);

        bool isDead();
};

#endif
