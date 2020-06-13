#include <exception>
#include <string>
#include <iostream>
#include <SDL2/SDL.h>
// HEADERS
#include "windowRenderingStuff.h"
#include "mouseStuff.h"
#include "button.h"
#include "sprites.h"
#include "testingStuff.h"

#define fps 60

using namespace std;

int main( int argc, char *argv[] ) {

    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    window = SDL_CreateWindow( "NNUI",
                                SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED,
                                400,
                                200,
                                SDL_WINDOW_RESIZABLE | SDL_WINDOW_BORDERLESS );
    if ( window == NULL ) cout << "Hubo un error con la ventana.\n" << SDL_GetError() << '\n';

    

    renderer = SDL_CreateRenderer(window, -1, 0);


    // Nueva pantalla
    SDL_Surface *pantalla = SDL_GetWindowSurface( window );


    // HIT TEST
    if (SDL_SetWindowHitTest(window, hitTest, NULL) == -1) {
        SDL_Log("Hit test failed!!!");
        procesoDeCierre(window);
        return 1;
    }


    SDL_Event event;
    bool running = true;
    int window_width, window_height;

    SDL_Surface *buttons_sprite_sheet = SDL_LoadBMP("buttons-title-bar.bmp");

    Mouse mouse = Mouse();

//TESTING AREA v ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    SDL_Rect maximize_area = {0,0,20,20};
    Button maximize_window_button = Button(maximize_area);
    maximize_window_button.sprite(renderer, buttons_sprite_sheet, 20, 0, 20, 20);

    SDL_Rect minimize_area = {0,0,20,20};
    Button minimize_window_button = Button(minimize_area);
    minimize_window_button.sprite(renderer, buttons_sprite_sheet,  0, 0, 20, 20);

    SDL_Rect close_area = {0,0,20,20};
    Button close_window_button = Button(close_area);
    close_window_button.sprite(renderer, buttons_sprite_sheet, 40, 0, 20, 20);

    // HandleEvents event_handler = HandleEvents(&event);

//TESTING AREA ^ ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    
    SDL_Color grey = {70, 70, 70, 255};
    SDL_Rect draggable_area = {0, 0, 0, 20};
    Button draggable_area_rect = Button(draggable_area, grey);

    int index = 0;  

    while (running) {

        // RENDERER SETUP
        SDL_GetWindowSize(window, &window_width, &window_height);
        if ( window_width < 100) {
            SDL_SetWindowSize(window, 100, window_height);
        }

        if (window_height < 100) {
            SDL_SetWindowSize(window, window_width, 100);
        }

        SDL_SetRenderDrawColor(renderer, 51, 51, 51, 255);
        SDL_RenderClear(renderer);
        // RENDERER SETUP

//TESTING AREA v ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        draggable_area_rect.area.w = window_width;
        draggable_area_rect.renderArea(renderer);
        
        close_window_button.dstRect.x = window_width - close_window_button.dstRect.w;
        close_window_button.renderSprite(renderer);

        maximize_window_button.dstRect.x = window_width - maximize_window_button.dstRect.w - 20;
        maximize_window_button.renderSprite(renderer);

        minimize_window_button.dstRect.x = window_width - minimize_window_button.dstRect.w - 40;
        minimize_window_button.renderSprite(renderer);



//TESTING AREA ^ ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        SDL_RenderPresent(renderer);


        while ( SDL_PollEvent( &event ) ) {

            if (eventHandler(&event)) {
                close_window_button.srcRect.x    = 40;
                maximize_window_button.srcRect.x = 20;
                minimize_window_button.srcRect.x =  0;
            }
            
            switch (event.type) {
                case SDL_QUIT:

                    running = false;

                    break;

                case SDL_KEYDOWN:

                    if (event.key.keysym.sym == SDLK_ESCAPE) running = false;

                    break;

                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT) {
                        mouse.updateMousePosition();
                        // cout << mouse.pos.x << ", " << mouse.pos.y << '\n';

                        if (close_window_button.mouseInDstRect(mouse.pos.x, mouse.pos.y)) running = false;


                    }

                    SDL_Log("click!");
                    break;

                case SDL_MOUSEMOTION:
                    mouse.updateMousePosition();
                    
                    close_window_button.srcRect.x    =    close_window_button.mouseInDstRect(mouse.pos.x, mouse.pos.y) ? 100 : 40;
                    maximize_window_button.srcRect.x = maximize_window_button.mouseInDstRect(mouse.pos.x, mouse.pos.y) ?  80 : 20;
                    minimize_window_button.srcRect.x = minimize_window_button.mouseInDstRect(mouse.pos.x, mouse.pos.y) ?  60 :  0;

                    break;

                case SDL_WINDOWEVENT:
                    break;
                default:
                    index++;
                    break;
            }
        }

        starting_tick = SDL_GetTicks();
        limitFrameRate(fps);
    }

    procesoDeCierre(window);

    return 0;
}
