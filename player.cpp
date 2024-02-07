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

    if ((abs(ball.getPos().x + 16 - (pos.x + 32)) <= 48) && (abs(ball.getPos().y + 16 - (pos.y + 32)) <= 48))
    {
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
            ball.setSpeed(speed.x, speed.y);
            speed.x = -speed.x / 2;
            speed.y = -speed.y / 2;
            collide = true;
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
