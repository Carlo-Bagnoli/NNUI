#include <exception>
#include <string>
#include <iostream>
#include <SDL.h>
// HEADERS
#include "windowRenderingStuff.h"
#include "mouseStuff.h"

#define fps 30

using namespace std;



int main( int argc, char *argv[] ) {

    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window *ventana = NULL;
    SDL_Renderer *renderizador = NULL;

    ventana = SDL_CreateWindow( "NNUI",
                                SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED,
                                400,
                                200,
                                SDL_WINDOW_RESIZABLE | SDL_WINDOW_BORDERLESS );
    if ( ventana == NULL ) cout << "Hubo un error con la ventana.\n" << SDL_GetError() << '\n';

    renderizador = SDL_CreateRenderer(ventana, -1, 0);


    // Nueva pantalla
    SDL_Surface *pantalla = SDL_GetWindowSurface( ventana );


    // HIT TEST
    if (SDL_SetWindowHitTest(ventana, hitTest, NULL) == -1) {
        SDL_Log("Hit test failed!!!");
        procesoDeCierre(ventana);
        return 1;
    }


    SDL_Event evento;
    bool running = true;
    int ancho_ventana, alto_ventana;

    SDL_Rect close_area = {0,0,20,20};
    int mouse_x, mouse_y;
    Mouse mouse = Mouse();

    while (running) {

        SDL_GetWindowSize(ventana, &ancho_ventana, &alto_ventana);
        if ( ancho_ventana < 100 && alto_ventana < 100 ) {
            SDL_SetWindowSize(ventana, 100, 100);
        }

        close_area.x = ancho_ventana - close_area.w;

        SDL_SetRenderDrawColor(renderizador, 51, 51, 51, 255);
        SDL_RenderClear(renderizador);

        SDL_SetRenderDrawColor(renderizador, 159, 1, 1, 255);
        SDL_RenderFillRect(renderizador, &close_area);

        SDL_RenderPresent(renderizador);


        starting_tick = SDL_GetTicks();



        while ( SDL_PollEvent( &evento ) ) {
            switch (evento.type) {
                case SDL_QUIT:
                    running = false;
                    break;
                case SDL_KEYDOWN:
                    if (evento.key.keysym.sym == SDLK_ESCAPE) {
                        running = false;
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (evento.button.button == SDL_BUTTON_LEFT) {
                        SDL_GetMouseState(&mouse_x, &mouse_y);
                        cout << mouse_x << ", " << mouse_y << '\n';
                        if (mouse.inRect(mouse_x, mouse_y, &close_area)) {
                            running = false;
                        }
                    }
                    break;
            }
        }

        limitarFrameRate(fps);

    }

    procesoDeCierre(ventana);

    return 0;
}
