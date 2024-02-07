#include <iostream>
#include "include/SDL.h"
#include "include/SDL_image.h"

#include "include/headers/Ball.h"
#include "include/headers/Utils.h"
#include "include/headers/Math.h"
#include "include/headers/Entity.h"

Ball::Ball(Vector2f p_pos, float scale, SDL_Texture *p_texture)
    : Entity(p_pos, scale, p_texture)
{
    acceleration = Vector2f(0, 0);
    speed = Vector2f(0, 0);
    friction = 0.005f;
}

void Ball::update()
{
    if (pos.x < 0 || pos.x + 32 > 935)
    {
        speed.x = -speed.x;
    }
    if (pos.y < 0 || pos.y + 32 > 600)
    {
        speed.y = -speed.y;
    }

    if (speed.x < 0)
        speed.x += friction;
    else if (speed.x > 0)
        speed.x -= friction;
    if (speed.y < 0)
        speed.y += friction;
    else if (speed.y > 0)
        speed.y -= friction;

    if (abs(speed.x) < 0.01f)
        speed.x = 0;
    if (abs(speed.y) < 0.01f)
        speed.y = 0;

    pos.x += speed.x;
    pos.y += speed.y;
}

void Ball::setSpeed(float speedX, float speedY)
{
    speed.x = speedX;
    speed.y = speedY;
}