#pragma once
#include "grid.h"
#include "blocks.cpp"
#include "vector"

class Game
{
public:
    Game();
    ~Game();
    void Draw();
    void HandleInput();
    void moveBlockDown();
    bool gameOver;
    int Score;
    Music music;

private:
    void moveBlockLeft();
    void moveBlockRight();
    Block getRandomBlock();
    std::vector<Block> getAllBlocks();
    bool isBlockOutside();
    void rotateBlock();
    void LockBlock();
    bool blockFits();
    void Reset();
    void updateScore(int linesCleared, int moveDownPoints);
    Grid grid;
    std::vector<Block> blocks;
    Block currentBlock;
    Block nextBlock;
    Sound rotateSound;
    Sound clearSound;
};