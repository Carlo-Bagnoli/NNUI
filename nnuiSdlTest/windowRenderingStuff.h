#pragma once
#include <SDL.h>

Uint32 starting_tick;

void limitarFrameRate(int fps) {
    if ((1000 / fps ) > SDL_GetTicks() - starting_tick) {
        int present_fps = (1000 / fps) - (SDL_GetTicks() - starting_tick);
        // std::cout << "current fps: " << present_fps << '\n';
        SDL_Delay(present_fps);
    }
}

void procesoDeCierre(SDL_Window *vent) {
    SDL_DestroyWindow(vent);
    SDL_Quit();
}
