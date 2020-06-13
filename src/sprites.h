#pragma once
#include <SDL2/SDL.h>


class Sprite 
{
public:
    SDL_Rect srcRect;
    SDL_Rect dstRect;
    SDL_Surface *sprite_surface;
    SDL_Texture *sprite_texture;

    Sprite(SDL_Renderer *render, const char* file, int xsrc = 0, int ysrc = 0, int wsrc = 0, int hsrc = 0 , int xdst = 0, int ydst = 0, int wdst = 0, int hdst = 0) {
        sprite_surface = SDL_LoadBMP(file);
        sprite_texture = SDL_CreateTextureFromSurface(render, sprite_surface);

        srcRect = {xsrc, ysrc, wsrc, hsrc};

        dstRect = {xdst, ydst, wdst, hdst};
    }

    void renderSprite(SDL_Renderer *render) {
        SDL_RenderCopy(render, sprite_texture, &srcRect, &dstRect);
    }

};