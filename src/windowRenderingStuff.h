#pragma once
#include <SDL2/SDL.h>

Uint32 starting_tick;

void limitFrameRate(int fps) {
    if ((1000 / fps ) > SDL_GetTicks() - starting_tick) {
        int present_fps = (1000 / fps) - (SDL_GetTicks() - starting_tick);
        SDL_Delay(present_fps);
    }
}

void procesoDeCierre(SDL_Window *vent) {
    SDL_DestroyWindow(vent);
    SDL_Quit();
}

// HIT TEST ///////////////////////////////

#define TAMANO_BORDE 5
#define DRAGGABLE_AREA 20


static SDL_HitTestResult SDLCALL hitTest( SDL_Window *vent, const SDL_Point *punto, void *data ) {

    int w, h;
    SDL_GetWindowSize(vent, &w, &h);

    

    if (punto -> y < DRAGGABLE_AREA && punto -> y > TAMANO_BORDE && punto -> x < w - 25) {
        return SDL_HITTEST_DRAGGABLE;
    }



    #define RESIZE(side) { \
        return SDL_HITTEST_RESIZE_##side; \
    }
//--------------------------------------------------------------------------------------------------------------------------------------
    if      (punto -> x <     TAMANO_BORDE && punto -> y <     TAMANO_BORDE)                                   { RESIZE(TOPLEFT);     }
//--------------------------------------------------------------------------------------------------------------------------------------
    else if (punto -> x >     TAMANO_BORDE && punto -> x < w - TAMANO_BORDE && punto -> y <     TAMANO_BORDE ) { RESIZE(TOP);         }
//--------------------------------------------------------------------------------------------------------------------------------------
    else if (punto -> x > w - TAMANO_BORDE && punto -> y <     TAMANO_BORDE)                                   { RESIZE(TOPRIGHT);    }
//--------------------------------------------------------------------------------------------------------------------------------------
    else if (punto -> x > w - TAMANO_BORDE && punto -> y >     TAMANO_BORDE && punto -> y < h - TAMANO_BORDE ) { RESIZE(RIGHT);       }
//--------------------------------------------------------------------------------------------------------------------------------------
    else if (punto -> x > w - TAMANO_BORDE && punto -> y > h - TAMANO_BORDE)                                   { RESIZE(BOTTOMRIGHT); }
//--------------------------------------------------------------------------------------------------------------------------------------
    else if (punto -> x < w - TAMANO_BORDE && punto -> x >     TAMANO_BORDE && punto -> y > h - TAMANO_BORDE) { RESIZE(BOTTOM);      }
//--------------------------------------------------------------------------------------------------------------------------------------
    else if (punto -> x <     TAMANO_BORDE && punto -> y > h - TAMANO_BORDE)                                   { RESIZE(BOTTOMLEFT);  }
//--------------------------------------------------------------------------------------------------------------------------------------
    else if (punto -> x <     TAMANO_BORDE && punto -> y >     TAMANO_BORDE && punto -> y < h - TAMANO_BORDE ) { RESIZE(LEFT);        }
//--------------------------------------------------------------------------------------------------------------------------------------

    return SDL_HITTEST_NORMAL;

}
