#pragma once
#include "../SDL.h"
#include "../SDL_image.h"
#include "Math.h"

class Entity
{
public:
    Entity(Vector2f pos, float scale, SDL_Texture *p_texture);
    void update();
    Vector2f &getPos();
    float getScale();
    SDL_Texture *getTexture();
    SDL_Rect getRect();

protected:
    Vector2f pos;
    float scale;
    SDL_Texture *p_texture;
    SDL_Rect rect;
};
