#pragma once

#include "Entity.h"
#include "../SDL.h"
#include "../SDL_image.h"
#include <iostream>
#include "Math.h"

class Ball : public Entity
{
public:
    Ball(Vector2f p_pos, float scale, SDL_Texture *p_texture);
    void setSpeed(float speedX, float speedY);
    Vector2f &getSpeed();
    void setAcceleration(float accelerationX, float accelerationY);
    Vector2f &getAcceleration();
    void move();

private:
    Vector2f speed, acceleration;
    float friction;
};