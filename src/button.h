#pragma once
#include <vector>
#include <SDL2/SDL.h>

enum EstadoDeBoton {NORMAL = 0, HOVER = 1, PRESIONADO = 2};


class Button {
public:
    SDL_Rect area;
    SDL_Color color;

    Button (SDL_Rect rect_area, SDL_Color colorIn) {
        area = rect_area;
        color = colorIn;
    }

    void renderButton(SDL_Renderer *render) {
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
};
