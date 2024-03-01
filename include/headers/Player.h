#pragma once

#include "Entity.h"
#include "../SDL.h"
#include "../SDL_image.h"
#include <iostream>
#include "Math.h"
#include "Ball.h"

class Player : public Entity
{
public:
    Player(Vector2f p_pos, float scale, SDL_Texture *p_texture);
    void setSpeed(float speedX, float speedY);
    void addSpeed(float speedX, float speedY);
    Vector2f &getSpeed();
    void setAcceleration(float accelerationX, float accelerationY);
    Vector2f &getAcceleration();
    void update(Ball &ball);
    void reset();
    float distanceToBall(Ball &ball);
    void AI_play(Ball &ball);
    void setAI(bool isAI);

private:
    Vector2f speed, acceleration;
    float friction;
    bool collide;
    int old_posX, old_posY;
    bool isAI;
    int AI_canMove;
};