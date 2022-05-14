#include "add.hpp"

int add(int a, int b)
{
    SDL_Window *window;

    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow("test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 500, 500, SDL_WINDOW_OPENGL);

    SDL_Delay(3000);

    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}