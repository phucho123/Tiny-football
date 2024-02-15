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
    SDL_Texture *numbers_texture = window.loadTexture("assets/images/number.png");
    SDL_Texture *pointer_texture = window.loadTexture("assets/images/pointer.png");
    Entity field(Vector2f(0, 0), 1.5, field_texture);
    Entity goal_of_player1(Vector2f(260, 0), 0.5, numbers_texture);
    SDL_Rect tmp1 = goal_of_player1.getRect();
    goal_of_player1.setRect(0, -1, tmp1.w / 10, -1);
    Entity goal_of_player2(Vector2f(600, 0), 0.5, numbers_texture);
    SDL_Rect tmp2 = goal_of_player2.getRect();
    goal_of_player2.setRect(0, -1, tmp1.w / 10, -1);
    Ball ball(Vector2f(470 - 16, 300 - 16), 0.5, ball_texture);
    Player players2[3] = {Player(Vector2f(540 - 32, 300 - 32), 1, player2_texture),
                          Player(Vector2f(700 - 32, 200 - 32), 1, player2_texture),
                          Player(Vector2f(700 - 32, 400 - 32), 1, player2_texture)};

    Player players1[3] = {Player(Vector2f(400 - 32, 300 - 32), 1, player1_texture),
                          Player(Vector2f(240 - 32, 200 - 32), 1, player1_texture),
                          Player(Vector2f(240 - 32, 400 - 32), 1, player1_texture)};
    int player2_active = 0, player1_active = 0;
    Entity pointer1(Vector2f(players1[player1_active].getPos().x + 25, players1[player1_active].getPos().y - 12), 0.2, pointer_texture);
    Entity pointer2(Vector2f(players2[player2_active].getPos().x + 25, players2[player2_active].getPos().y - 12), 0.2, pointer_texture);
    bool quit = false;
    SDL_Event e;
    int player1_goals = 0, player2_goals = 0;

    // SDL_Texture *ball = window.loadTexture("assets/images/ball.png");
    // std::cout << window.getRefreshRate() << std::endl;
    const float timeStep = 0.01f;
    float accumulator = 0.01f;
    float currentTime = utils::hireTimeInSeconds();

    int mouseX, mouseY;

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
                        players1[player1_active].addSpeed(-1.5, 0);
                        break;
                    case SDLK_d:
                        players1[player1_active].addSpeed(1.5, 0);
                        break;
                    case SDLK_w:
                        players1[player1_active].addSpeed(0, -1.5);
                        break;
                    case SDLK_s:
                        players1[player1_active].addSpeed(0, 1.5);
                        break;
                    case SDLK_f:
                        player1_active = (player1_active + 1) % 3;
                        pointer1.setPos(players1[player1_active].getPos().x + 25, players1[player1_active].getPos().y - 12);
                        break;
                    case SDLK_LEFT:
                        players2[player2_active].addSpeed(-1.5, 0);
                        break;
                    case SDLK_RIGHT:
                        players2[player2_active].addSpeed(1.5, 0);
                        break;
                    case SDLK_UP:
                        players2[player2_active].addSpeed(0, -1.5);
                        break;
                    case SDLK_DOWN:
                        players2[player2_active].addSpeed(0, 1.5);
                        break;
                    case SDLK_RSHIFT:
                        player2_active = (player2_active + 1) % 3;
                        pointer2.setPos(players2[player2_active].getPos().x + 25, players2[player2_active].getPos().y - 12);
                        break;
                    default:
                        break;
                    }
                }

                else if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_ESCAPE)
                    break;

                if (e.type == SDL_MOUSEMOTION)
                {
                    SDL_GetMouseState(&mouseX, &mouseY);
                    std::cout << mouseX << ", " << mouseY << std::endl;
                }
            }
            accumulator -= timeStep;
        }
        const float alpha = accumulator / timeStep;

        ball.update();
        for (int i = 0; i < 3; i++)
        {
            players1[i].update(ball);
            players2[i].update(ball);
        }

        float dist_1 = players1[0].distanceToBall(ball);
        float dist_2 = players2[0].distanceToBall(ball);
        player1_active = 0;
        player2_active = 0;
        for (int i = 1; i < 3; i++)
        {
            float val1 = players1[i].distanceToBall(ball);
            float val2 = players2[i].distanceToBall(ball);
            if (val1 < dist_1)
            {
                player1_active = i;
                dist_1 = val1;
            }
            if (val2 < dist_2)
            {
                player2_active = i;
                dist_2 = val2;
            }
        }
        pointer1.setPos(players1[player1_active].getPos().x + 25, players1[player1_active].getPos().y - 12);
        pointer2.setPos(players2[player2_active].getPos().x + 25, players2[player2_active].getPos().y - 12);

        if (ball.getGoal() > 0)
        {
            if (ball.getGoal() == 1)
            {
                player1_goals++;
                goal_of_player1.setRect(158 * player1_goals, -1, -1, -1);
                ball.reset();
                for (int i = 0; i < 3; i++)
                {
                    players2[i].reset();
                    players1[i].reset();
                }
                player1_active = 0;
                player2_active = 0;
            }
            else if (ball.getGoal() == 2)
            {
                player2_goals++;
                goal_of_player2.setRect(158 * player2_goals, -1, -1, -1);
                ball.reset();
                for (int i = 0; i < 3; i++)
                {
                    players2[i].reset();
                    players1[i].reset();
                }
                player1_active = 0;
                player2_active = 0;
            }
        }

        window.clear();
        window.render(field);
        window.render(ball);
        for (int i = 0; i < 3; i++)
        {
            window.render(players1[i]);
            window.render(players2[i]);
        }
        window.render(goal_of_player1);
        window.render(goal_of_player2);
        window.render(pointer1);
        window.render(pointer2);
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