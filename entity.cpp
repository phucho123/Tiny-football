#include <iostream>
#include "include/SDL.h"
#include "include/SDL_image.h"

#include "include/headers/Entity.h"
#include "include/headers/Math.h"

Entity::Entity(Vector2f p_pos, float p_scale, SDL_Texture *p_texture) : pos(p_pos), p_texture(NULL)
{
    this->p_texture = p_texture;

    int w, h;
    SDL_QueryTexture(p_texture, NULL, NULL, &w, &h);
    rect.x = 0;
    rect.y = 0;
    rect.w = w;
    rect.h = h;

    scale = p_scale;
}

void Entity::update()
{
    // move();
}

Vector2f &Entity::getPos()
{
    return pos;
}

SDL_Texture *Entity::getTexture()
{
    return p_texture;
}

SDL_Rect Entity::getRect()
{
    return rect;
}

void Entity::setRect(float x, float y, float w, float h)
{
    if (x > 0)
        rect.x = x;
    if (y > 0)
        rect.y = y;
    if (w > 0)
        rect.w = w;
    if (h > 0)
        rect.h = h;
}

float Entity::getScale()
{
    return scale;
}

void Entity::setPos(float x, float y)
{
    pos.x = x;
    pos.y = y;
}