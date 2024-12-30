#include "game.h"
#include <random>

Game::Game()
{
    grid = Grid();
    blocks = getAllBlocks();
    currentBlock = getRandomBlock();
    nextBlock = getRandomBlock();
    gameOver = false;
    Score = 0;
    InitAudioDevice();
    music = LoadMusicStream("Sounds/ES_Tiger Tracks - Lexica.mp3");
    PlayMusicStream(music);
    rotateSound = LoadSound("Sounds/rotate.mp3");
    clearSound = LoadSound("Sounds/clear.mp3");
}
Game::~Game()
{
    UnloadSound(rotateSound);
    UnloadSound(clearSound);
    UnloadMusicStream(music);
    CloseAudioDevice();
}

Block Game::getRandomBlock()
{
    if(blocks.empty())
    {
        blocks = getAllBlocks();
    }
    int randomIndex = rand() % blocks.size();
    Block block = blocks[randomIndex];
    blocks.erase(blocks.begin() + randomIndex);
    return block;
}

std::vector<Block> Game::getAllBlocks()
{
    return {IBlock(), JBlock(), LBlock(), OBlock(), SBlock(), TBlock(), ZBlock()};
}

void Game::Draw()
{
    grid.Draw();
    currentBlock.Draw(11, 11);
    switch(nextBlock.id)
    {
    case 3:
        nextBlock.Draw(255, 290);
        break;
    case 4:
        nextBlock.Draw(255, 280);
        break;
    default:
        nextBlock.Draw(270, 270);
        break;    
    }
}

void Game::HandleInput()
{
    int keyPressed = GetKeyPressed();
    if(gameOver && keyPressed != 0)
    {
        gameOver = false;
        Reset();
    }
    switch(keyPressed)
    {
    case KEY_LEFT:
        moveBlockLeft();
        break;

    case KEY_RIGHT:
        moveBlockRight();
        break;

    case KEY_DOWN:
        moveBlockDown();
        updateScore(0, 1);
        break;

    case KEY_UP:
        rotateBlock();
        break;
    }
}
void Game::moveBlockLeft()
{
    if(!gameOver)
    {
        currentBlock.Move(0, -1);
        if(isBlockOutside() || blockFits() == false)
        {
            currentBlock.Move(0, 1);
        }
    }
}

void Game::moveBlockRight()
{
    if(!gameOver)
    {
        currentBlock.Move(0, 1);
        if(isBlockOutside() || blockFits() == false)
        {
            currentBlock.Move(0, -1);
        }
    }
}

void Game::moveBlockDown()
{
    if(!gameOver)
    {
        currentBlock.Move(1, 0);
        if(isBlockOutside() || blockFits() == false)
        {
            currentBlock.Move(-1, 0);
            LockBlock();
        }
    }
}

bool Game::isBlockOutside()
{
    std::vector<Position> tiles = currentBlock.getCellPositions();
    for(Position item: tiles)
    {
        if(grid.isCellOutside(item.row, item.column))
        {
            return true;
        }
    }
    return false;
}

void Game::rotateBlock()
{
    if(!gameOver)
    {
        currentBlock.Rotate();
        if(isBlockOutside() || blockFits() == false)
        {
            currentBlock.UndoRotation();
        }
        else 
        {
            PlaySound(rotateSound);
        }
    }
}

void Game::LockBlock()
{
    std::vector<Position> tiles = currentBlock.getCellPositions();
    for(Position item: tiles)
    {
        grid.grid[item.row][item.column] = currentBlock.id;
    }

    currentBlock = nextBlock;
    if(blockFits() == false)
    {
        gameOver = true;
    }
    nextBlock = getRandomBlock();
    int rowsCleared = grid.clearFullRows();
    if(rowsCleared > 0)
    {
        PlaySound(clearSound);
        updateScore(rowsCleared, 0);
    }
    
}

bool Game::blockFits()
{
    std::vector<Position> tiles = currentBlock.getCellPositions();
    for(Position item: tiles)
    {
        if(grid.isCellEmpty(item.row, item.column) == false)
        {
            return false;
        }
    }
    return true;
}

void Game::Reset()
{
    grid.Initialize();
    blocks = getAllBlocks();
    currentBlock = getRandomBlock();
    nextBlock = getRandomBlock();
    Score = 0;
}

void Game::updateScore(int linesCleared, int moveDownPoints)
{
    switch(linesCleared)
    {
    case 1:
        Score += 100;
        break;
        
    case 2:
        Score += 300;
        break;

    case 3:
        Score += 500;
        break;

    default:
        break;
    }
    Score += moveDownPoints;

}
