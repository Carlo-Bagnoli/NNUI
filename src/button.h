#pragma once
#include <vector>
#include <SDL2/SDL.h>

enum EstadoDeBoton {NORMAL = 0, HOVER = 1, PRESIONADO = 2};


class Button 
{
public:
    SDL_Rect area;
    SDL_Color color;

    Button (SDL_Rect rect_area, const SDL_Color colorIn = {0,0,0,0}) {
        area = rect_area;
        color = colorIn;
    }

    void renderArea(SDL_Renderer *render) {
        SDL_SetRenderDrawColor(render, color.r, color.g, color.b, color.a);
        SDL_RenderFillRect(render, &area);
    }

    bool mouseInArea(int x, int y) {
        if (x >= area.x && x < (area.x + area.w)) {
            if (y >= area.y && y < (area.y + area.h)){
                return true;
            }
        }
        return false;
    }


    SDL_Rect srcRect;
    SDL_Rect dstRect = {0, 0, 20, 20};
    SDL_Surface *sprite_surface;
    SDL_Texture *sprite_texture;

    void sprite(SDL_Renderer *render, SDL_Surface *sprite_in, int xsrc = 0, int ysrc = 0, int wsrc = 0, int hsrc = 0) {
        sprite_surface = sprite_in;
        sprite_texture = SDL_CreateTextureFromSurface(render, sprite_surface);

        srcRect = {xsrc, ysrc, wsrc, hsrc};
    }
    
    void renderSprite(SDL_Renderer *render) {
        SDL_RenderCopy(render, sprite_texture, &srcRect, &dstRect);
    }

    bool mouseInDstRect(int x, int y) {
        if (x >= dstRect.x && x < (dstRect.x + dstRect.w)) {
            if (y >= dstRect.y && y < (dstRect.y + dstRect.h)){
                return true;
            }
        }
        return false;
    }

};
