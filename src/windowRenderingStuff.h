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

// TESTING AREA v ////////////////////////////////////////////////////////////////////////

// void titleBar(SDL_Renderer *render, int window_w, int window_h, SDL_Surface *sprite_sheet)
// {
//     SDL_Rect maximize_area = {0,0,20,20};
//     Button maximize_window_button = Button(maximize_area);
//     maximize_window_button.sprite(render, sprite_sheet, 20, 0, 20, 20);

//     SDL_Rect minimize_area = {0,0,20,20};
//     Button minimize_window_button = Button(minimize_area);
//     minimize_window_button.sprite(render, sprite_sheet,  0, 0, 20, 20);

//     SDL_Rect close_area = {0,0,20,20};
//     Button close_window_button = Button(close_area);
//     close_window_button.sprite(render, sprite_sheet, 40, 0, 20, 20);
// }
// TESTING AREA ^ ///////////////////////////////////////////////////////////////////////

static SDL_HitTestResult SDLCALL hitTest( SDL_Window *vent, const SDL_Point *punto, void *data ) {

    int w, h;
    SDL_GetWindowSize(vent, &w, &h);

    

    if (punto -> y < DRAGGABLE_AREA && punto -> y > TAMANO_BORDE && punto -> x < w - 60) {
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
