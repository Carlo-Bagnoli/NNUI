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


void show_flags(int flags) {

    printf("\nFLAGS ENABLED: ( %d )\n", flags);
    printf("=======================\n");
    if(flags & SDL_WINDOW_FULLSCREEN)         printf("SDL_WINDOW_FULLSCREEN\n");
    if(flags & SDL_WINDOW_OPENGL)             printf("SDL_WINDOW_OPENGL\n");
    if(flags & SDL_WINDOW_SHOWN)              printf("SDL_WINDOW_SHOWN\n");
    if(flags & SDL_WINDOW_HIDDEN)             printf("SDL_WINDOW_HIDDEN\n");
    if(flags & SDL_WINDOW_BORDERLESS)         printf("SDL_WINDOW_BORDERLESS\n");
    if(flags & SDL_WINDOW_RESIZABLE)          printf("SDL_WINDOW_RESIZABLE\n");
    if(flags & SDL_WINDOW_MINIMIZED)          printf("SDL_WINDOW_MINIMIZED\n");
    if(flags & SDL_WINDOW_MAXIMIZED)          printf("SDL_WINDOW_MAXIMIZED\n");
    if(flags & SDL_WINDOW_INPUT_GRABBED)      printf("SDL_WINDOW_INPUT_GRABBED\n");
    if(flags & SDL_WINDOW_INPUT_FOCUS)        printf("SDL_WINDOW_INPUT_FOCUS\n");
    if(flags & SDL_WINDOW_MOUSE_FOCUS)        printf("SDL_WINDOW_MOUSE_FOCUS\n");
    if(flags & SDL_WINDOW_FULLSCREEN_DESKTOP) printf("SDL_WINDOW_FULLSCREEN_DESKTOP\n");
    if(flags & SDL_WINDOW_FOREIGN)            printf("SDL_WINDOW_FOREIGN\n");
}



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

    int flags;
    int window_maximized;
    int window_minimized;
    

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

        flags = SDL_GetWindowFlags(window);
        window_maximized = (flags & SDL_WINDOW_MAXIMIZED) ? true : false;
        window_minimized = (flags & SDL_WINDOW_MINIMIZED) ? true : false;

        // if (window_maximized) {
        //     SDL_Log("fucking finally m8!");
        // }

        draggable_area_rect.area.w = window_width;
        draggable_area_rect.renderArea(renderer);
        
        close_window_button.dstRect.x = window_width - close_window_button.dstRect.w;
        close_window_button.renderSprite(renderer);

        maximize_window_button.dstRect.x = window_width - maximize_window_button.dstRect.w - 20;
        maximize_window_button.renderSprite(renderer);

        minimize_window_button.dstRect.x = window_width - minimize_window_button.dstRect.w - 40;
        minimize_window_button.renderSprite(renderer);

        // if (SDL_GetWindowFlags(window) == SDL_WINDOW_MAXIMIZED) {
        //     SDL_Log("Window is borderless!");
        // }


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

                        if (maximize_window_button.mouseInDstRect(mouse.pos.x, mouse.pos.y)) {
                            if (!window_maximized){ 
                                SDL_MaximizeWindow(window);
                            } else {
                                SDL_RestoreWindow(window);
                            }
                        }

                        if (minimize_window_button.mouseInDstRect(mouse.pos.x, mouse.pos.y)) {
                            if (!window_minimized) {
                                SDL_MinimizeWindow(window);
                            } else {
                                SDL_RestoreWindow(window);
                            }
                        }



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
