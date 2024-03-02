#include <iostream>
#include "include/SDL.h"
#include "include/SDL_image.h"

#include "include/headers/Player.h"
#include "include/headers/Ball.h"
#include "include/headers/Utils.h"
#include "include/headers/Math.h"
#include "include/headers/Entity.h"

Player::Player(Vector2f p_pos, float scale, SDL_Texture *p_texture)
    : Entity(p_pos, scale, p_texture)
{
    acceleration = Vector2f(0, 0);
    speed = Vector2f(0, 0);
    friction = 0.005f;
    collide = false;
    old_posX = p_pos.x;
    old_posY = p_pos.y;
    isAI = false;
    AI_canMove = 10;
}

void Player::update(Ball &ball)
{
    if (pos.x < 0 && speed.x < 0 || pos.x + 64 > 935 && speed.x > 0)
    {
        speed.x = 0;
    }
    if (pos.y < 0 && speed.y < 0 || pos.y + 64 > 600 && speed.y > 0)
    {
        speed.y = 0;
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

    float dist = SDL_sqrt(SDL_pow(ball.getPos().x + 16 - (pos.x + 32), 2) + SDL_pow(ball.getPos().y + 16 - (pos.y + 32), 2));

    if (dist < 45)
    {
        // (abs(ball.getPos().x + 16 - (pos.x + 32)) < 48) && (abs(ball.getPos().y + 16 - (pos.y + 32)) < 48)
        // int a = abs(ball.getPos().x + 16 - (pos.x + 32));
        // int b = abs(ball.getPos().y + 16 - (pos.y + 32));

        // float f = 48 / SDL_sqrt(a * a + b * b);

        // if (speed.x > 0)
        //     pos.x -= a * f;
        // else if (speed.x < 0)
        //     pos.x += a * f;
        // if (speed.y > 0)
        //     pos.y -= b * f;
        // else if (speed.y < 0)
        //     pos.y += b * f;

        if (!collide)
        {
            if (!isAI)
            {
                // ball.setSpeed(1.5 * speed.x, 1.5 * speed.y);
                ball.setSpeed(2 * speed.x, 2 * speed.y);
                speed.x = -speed.x * 1;
                speed.y = -speed.y * 1;
                collide = true;
            }
            else
            {
                float dirX = 40 - (ball.getPos().x + 16);
                float dirY = 300 - (ball.getPos().y + 16);
                float dist = SDL_sqrt(dirX * dirX + dirY * dirY);
                if (dist > 0)
                {
                    ball.setSpeed(1.5 * dirX / dist, 1.5 * dirY / dist);
                    speed.x = -dirX / dist * 1.5;
                    speed.y = -dirY / dist * 1.5;
                }
                collide = true;
            }
        }
    }
    else
        collide = false;
}

void Player::setSpeed(float speedX, float speedY)
{
    speed.x = speedX;
    speed.y = speedY;
}

void Player::addSpeed(float speedX, float speedY)
{
    speed.x += speedX;
    speed.y += speedY;

    if (speed.x > 2)
        speed.x = 2;
    else if (speed.x < -2)
        speed.x = -2;
    if (speed.y > 2)
        speed.y = 2;
    else if (speed.y < -2)
        speed.y = -2;
}

void Player::reset()
{
    pos.x = old_posX;
    pos.y = old_posY;
    speed.x = 0;
    speed.y = 0;
}

float Player::distanceToBall(Ball &ball)
{
    return SDL_sqrt(SDL_pow(ball.getPos().x + 16 - (pos.x + 32), 2) + SDL_pow(ball.getPos().y + 16 - (pos.y + 32), 2));
}

void Player::AI_play(Ball &ball)
{
    if (isAI && (AI_canMove == 0))
    {
        float dirX = ball.getPos().x - pos.x;
        float dirY = ball.getPos().y - pos.y;
        float dist = SDL_sqrt(dirX * dirX + dirY * dirY);
        setSpeed(0, 0);
        if (dist > 0)
            addSpeed(2 * dirX / dist, 2 * dirY / dist);
        AI_canMove = 70;
    }
    else
        AI_canMove--;
}

void Player::setAI(bool isAI)
{
    this->isAI = isAI;
}