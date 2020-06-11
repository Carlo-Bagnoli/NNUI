#include <exception>
#include <string>
#include <iostream>
#include <SDL2/SDL.h>
// HEADERS
#include "windowRenderingStuff.h"
#include "mouseStuff.h"
#include "button.h"

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

    Mouse mouse = Mouse();

    SDL_Rect close_area = {0,0,20,20};
    SDL_Color red = {255, 0, 0, 255};
    Button close_window_button = Button(close_area, red);

    SDL_Color grey = {70, 70, 70, 255};
    SDL_Rect draggable_area = {0, 0, 0, 20};
    Button draggable_area_rect = Button(draggable_area, grey);

    while (running) {

        // RENDERER SETUP
        SDL_GetWindowSize(ventana, &ancho_ventana, &alto_ventana);
        if ( ancho_ventana < 100) {
            SDL_SetWindowSize(ventana, 100, alto_ventana);
        }

        if (alto_ventana < 100) {
            SDL_SetWindowSize(ventana, ancho_ventana, 100);
        }

        SDL_SetRenderDrawColor(renderizador, 51, 51, 51, 255);
        SDL_RenderClear(renderizador);
        // RENDERER SETUP

        close_window_button.area.x = ancho_ventana - close_window_button.area.w;
        close_window_button.renderButton(renderizador);

        draggable_area_rect.area.w = ancho_ventana - 20;
        draggable_area_rect.renderButton(renderizador);

        SDL_RenderPresent(renderizador);

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
                        SDL_GetMouseState(&mouse.pos.x, &mouse.pos.y);
                        if (close_window_button.mouseInArea(mouse.pos.x, mouse.pos.y)) {
                            running = false;
                        }
                    }
                    break;
            }
        }

        starting_tick = SDL_GetTicks();
        limitFrameRate(fps);
    }

    procesoDeCierre(ventana);

    return 0;
}
