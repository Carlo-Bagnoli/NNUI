#include <iostream>
#include "SDL2/SDL.h"

#define fps 60

using namespace std;

void limitarFrameRate( Uint32 starting_tick) {
    if ((1000 / fps ) > SDL_GetTicks() - starting_tick ) {
        SDL_Delay((1000 / fps) - (SDL_GetTicks() - starting_tick));
    }

}

int main( int argc, char *argv[] ) {
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window *ventana = NULL;

    ventana = SDL_CreateWindow( "NNUI",
                                SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED,
                                400,
                                200,
                                SDL_WINDOW_RESIZABLE );

    if ( ventana == NULL ) cout << "Hubo un error\n" << SDL_GetError() << '\n';

    // Nueva pantalla
    SDL_Surface *pantalla = SDL_GetWindowSurface( ventana );
    Uint32 white = SDL_MapRGB( pantalla->format, 255, 255, 255 );
    SDL_FillRect(pantalla, NULL, white);
    SDL_UpdateWindowSurface( ventana );

    // fps limiter
    Uint32 starting_tick;



    SDL_Event evento;
    bool running = true;

    while (running) {

        starting_tick = SDL_GetTicks();

        while ( SDL_PollEvent( &evento ) ) {
            if (evento.type == SDL_QUIT ) {
                running = false;
                break;
            }
        }

        limitarFrameRate(starting_tick);

    }




    SDL_DestroyWindow(ventana);

    SDL_Quit();
    return 0;
}

