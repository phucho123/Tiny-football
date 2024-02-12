#pragma once
#include "../SDL.h"
#include "../SDL_image.h"
#include "Math.h"

class Entity
{
public:
    Entity(Vector2f p_pos, float p_scale, SDL_Texture *p_texture);
    void update();
    Vector2f &getPos();
    float getScale();
    SDL_Texture *getTexture();
    SDL_Rect getRect();
    void setRect(float x, float y, float w, float h);
    void setPos(float x, float y);

protected:
    Vector2f pos;
    float scale;
    SDL_Texture *p_texture;
    SDL_Rect rect;
};
