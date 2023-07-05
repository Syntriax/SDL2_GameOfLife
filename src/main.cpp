#include "headers.h"
#include "ConfigurationParser/ConfigurationParser.h"

#define CONFIG_PATH "config.cfg"

#define WIDTH_CONF_KEY "WIDTH"
#define HEIGHT_CONF_KEY "HEIGHT"
#define FPS_CONF_KEY "FPS"
#define SEED_CONF_KEY "SEED"

void ReadConfig(Syn::ConfigurationParser &parser)
{
    if (parser.ParseFile(CONFIG_PATH))
        return;

    parser[WIDTH_CONF_KEY] = "400";
    parser[HEIGHT_CONF_KEY] = "400";
    parser[FPS_CONF_KEY] = "60";
    parser[SEED_CONF_KEY] = "0";

    parser.WriteFile(CONFIG_PATH);
}

void Update(SDL_Surface *surface, GameOfLife *life)
{
    SDL_LockSurface(surface);
    life->Iterate();
    SDL_UnlockSurface(surface);
}

int main(int argc, char *argv[])
{
    SDL_Event event;
    SDL_Renderer *renderer;
    SDL_Window *window;
    SDL_Surface *surface;

    GameOfLife life;
    Syn::ConfigurationParser config;
    ReadConfig(config);

    int width = std::stoi(config[WIDTH_CONF_KEY]);
    int height = std::stoi(config[HEIGHT_CONF_KEY]);
    int fps = std::stoi(config[FPS_CONF_KEY]);
    int seed = std::stoi(config[SEED_CONF_KEY]);

    bool isRunning = true;
    int tickForNext = 1000 / fps;
    int nextTick = 0;

    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow(
        "Game of Life",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        width, height,
        SDL_WindowFlags::SDL_WINDOW_OPENGL);
    renderer = SDL_CreateRenderer(window, -1, SDL_RendererFlags::SDL_RENDERER_ACCELERATED);
    surface = SDL_GetWindowSurface(window);

    life.SetDimensions(width, height);
    life.SetDisplay((int *)surface->pixels, surface->format);
    life.Randomize(seed);

    while (isRunning)
    {
        while (SDL_PollEvent(&event) != 0)
        {
            switch (event.type)
            {
            case SDL_QUIT:
                isRunning = false;
                break;
            }
        }
        if (SDL_GetTicks() >= nextTick)
        {
            Update(surface, &life);
            SDL_UpdateWindowSurface(window);
            nextTick += tickForNext;
        }
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;
}
