#pragma once

#include "SDL.h"

class Mouse {
public:
    Mouse(){}

    bool inRect(int x, int y, struct SDL_Rect *rect) {
        if (x >= rect->x && x < (rect->x + rect->w)) {
            if (y >= rect->y && y < (rect->y + rect->h)){
                return true;
            }
        }
        return false;
    }

};
