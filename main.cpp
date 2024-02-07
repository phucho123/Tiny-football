#include <iostream>
#include "include/SDL.h"
#include "include/SDL_image.h"

#include "include/headers/RenderWindow.h"
#include "include/headers/Entity.h"
#include "include/headers/Ball.h"
#include "include/headers/Player.h"
#include "include/headers/Utils.h"
#include "include/headers/Math.h"

int main(int argc, char *argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO) > 0)
    {
        std::cout << "SDL init failed. Error: " << SDL_GetError() << std::endl;
    }

    if (!(IMG_Init(IMG_INIT_PNG)))
    {
        std::cout << "IMG init failed. Error: " << IMG_GetError() << std::endl;
    }

    RenderWindow window("Tiny football", 930, 600);
    SDL_Texture *field_texture = window.loadTexture("assets/images/field.png");
    SDL_Texture *ball_texture = window.loadTexture("assets/images/ball.png");
    SDL_Texture *player1_texture = window.loadTexture("assets/images/mu.png");
    SDL_Texture *player2_texture = window.loadTexture("assets/images/mc.png");
    Entity field(Vector2f(0, 0), 1.5, field_texture);
    Ball ball(Vector2f(100, 100), 0.5, ball_texture);
    Player player1(Vector2f(0, 0), 1, player1_texture);
    Player player2(Vector2f(200, 200), 1, player2_texture);
    bool quit = false;
    SDL_Event e;

    // SDL_Texture *ball = window.loadTexture("assets/images/ball.png");
    // std::cout << window.getRefreshRate() << std::endl;
    const float timeStep = 0.01f;
    float accumulator = 0.01f;
    float currentTime = utils::hireTimeInSeconds();

    while (!quit)
    {
        int startTicks = SDL_GetTicks();
        float newTime = utils::hireTimeInSeconds();
        float frameTime = newTime - currentTime;
        currentTime = newTime;

        accumulator += frameTime;

        while (accumulator >= timeStep)
        {
            while (SDL_PollEvent(&e))
            {
                if (e.type == SDL_QUIT)
                {
                    quit = true;
                    break;
                }
                else if (e.type == SDL_KEYDOWN)
                {
                    switch (e.key.keysym.sym)
                    {
                    case SDLK_a:
                        player1.addSpeed(-1.5, 0);
                        break;
                    case SDLK_d:
                        player1.addSpeed(1.5, 0);
                        break;
                    case SDLK_w:
                        player1.addSpeed(0, -1.5);
                        break;
                    case SDLK_s:
                        player1.addSpeed(0, 1.5);
                        break;
                    case SDLK_LEFT:
                        player2.addSpeed(-1.5, 0);
                        break;
                    case SDLK_RIGHT:
                        player2.addSpeed(1.5, 0);
                        break;
                    case SDLK_UP:
                        player2.addSpeed(0, -1.5);
                        break;
                    case SDLK_DOWN:
                        player2.addSpeed(0, 1.5);
                        break;
                    default:
                        break;
                    }
                }

                else if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_ESCAPE)
                    break;
            }
            accumulator -= timeStep;
        }
        const float alpha = accumulator / timeStep;

        ball.update();
        player1.update(ball);
        player2.update(ball);

        window.clear();
        window.render(field);
        window.render(ball);
        window.render(player1);
        window.render(player2);
        window.display();
        // SDL_Delay(10);

        int frameTicks = SDL_GetTicks() - startTicks;

        if (frameTicks < 1000 / window.getRefreshRate())
        {
            SDL_Delay(1000 / window.getRefreshRate() - frameTicks);
        }
    }

    window.cleanUp();
    SDL_Quit();
    return 0;
}