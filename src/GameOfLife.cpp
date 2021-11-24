#include "GameOfLife.h"

int *GameOfLife::GetCell(int x, int y, int *buffer) { return buffer + y * width + x; }

int GameOfLife::GetNeighborCount(int x, int y, int *buffer)
{
    int i, j;
    int result = 0;

    for (i = -1; i < 2; i++)
        for (j = -1; j < 2; j++)
            result += *GetCell(x + i, y + j, buffer) & 1;

    return result - (*GetCell(x, y, buffer) & 1);
}

int GameOfLife::CalculateState(int state, int neighborCount)
{
    if (state == 0)
        return neighborCount == 3;

    return neighborCount == 2 || neighborCount == 3;
}

void GameOfLife::Iterate()
{
    int x, y;
    int count = 0;
    int *backCell;

    for (y = 1; y < height - 1; y++)
        for (x = 1; x < width - 1; x++)
        {
            count = GetNeighborCount(x, y, front);
            backCell = GetCell(x, y, back.get());
            if (CalculateState(*GetCell(x, y, front), count))
                *backCell = livePixelColor;
            else
                *backCell = 0;
        }

    std::memcpy(front, back.get(), width * height * sizeof(int));
}

void GameOfLife::SetDisplay(int *pixelPointer, SDL_PixelFormat *pixelFormat)
{
    front = pixelPointer;
    livePixelColor = SDL_MapRGBA(pixelFormat, 255, 255, 255, 255);
}

bool GameOfLife::SetDimensions(int width, int height)
{
    this->width = width;
    this->height = height;

    back = std::make_unique<int[]>(width * height);
    return back.get() != nullptr;
}

bool GameOfLife::Randomize(int seed)
{
    if (front == nullptr)
        return false;

    int count = width * height;
    std::srand(seed);

    for (int i = 0; i < count; i++)
        if (rand() % 2 == 0)
            *(front + i) = livePixelColor;
        else
            *(front + i) = 0;

    return true;
}

GameOfLife::GameOfLife() { SetDimensions(100, 100); }
GameOfLife::GameOfLife(int width, int height) { SetDimensions(width, height); }
GameOfLife::~GameOfLife() {}
