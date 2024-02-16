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
    goal = 0;
}

void Ball::update()
{
    if (pos.x < 64 || pos.x + 32 > 877)
    {
        if (pos.x < 36)
            goal = 2;
        else if (pos.x + 32 > 902)
            goal = 1;
        if ((pos.x < 36 || pos.x + 32 > 902) || (pos.y < 260 || pos.y + 32 > 350))
            speed.x = -speed.x;
    }
    if (pos.y < 27 || pos.y + 32 > 577)
    {
        speed.y = -speed.y;
    }
    if ((pos.x < 36 || pos.x + 32 > 902) && (pos.y < 260 || pos.y + 32 > 350))
        speed.y = -speed.y;

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

int Ball::getGoal()
{
    return goal;
}

void Ball::setGoal(int goal)
{
    this->goal = goal;
}

void Ball::reset()
{
    pos.x = 470 - 16;
    pos.y = 300 - 16;

    speed.x = 0;
    speed.y = 0;

    goal = 0;
}