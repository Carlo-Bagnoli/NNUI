#pragma once

#include <SDL2/SDL.h>

class Mouse {
public:
    Mouse(){}

    SDL_Point pos = {0, 0};

    void updateMousePosition() {
        SDL_GetMouseState(&pos.x, &pos.y);
    }


    // bool inRect(int x, int y, struct SDL_Rect *rect) {
    //     if (x >= rect->x && x < (rect->x + rect->w)) {
    //         if (y >= rect->y && y < (rect->y + rect->h)){
    //             return true;
    //         }
    //     }
    //     return false;
    // }

};
