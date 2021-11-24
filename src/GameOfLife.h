#pragma once
#include "headers.h"

class GameOfLife
{
private:
    int width;
    int height;
    int livePixelColor;
    int *front;
    std::unique_ptr<int[]> back;

    int *GetCell(int, int, int *);
    int GetNeighborCount(int, int, int *);
    int CalculateState(int, int);

public:
    const int *GetGridPointer();
    void Iterate();
    void SetDisplay(int *, SDL_PixelFormat *);
    bool SetDimensions(int, int);
    bool Randomize(int);
    GameOfLife();
    GameOfLife(int, int);
    ~GameOfLife();
};
