#include "SDL.h"
#include "SDL_image.h"
#include <iostream>

#include "include/headers/RenderWindow.h"
#include "include/headers/Entity.h"

RenderWindow::RenderWindow(const char *p_title, int w, int h) : window(NULL), renderer(NULL)
{
    window = SDL_CreateWindow(p_title, 100, 100, w, h, 0);

    if (window == NULL)
    {
        std::cout << "Can't init window. Error: " << SDL_GetError() << std::endl;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

SDL_Texture *RenderWindow::loadTexture(const char *p_filePath)
{
    SDL_Texture *texture = NULL;
    texture = IMG_LoadTexture(renderer, p_filePath);

    if (texture == NULL)
    {
        std::cout << "Can't load texture. Error: " << SDL_GetError() << std::endl;
    }

    return texture;
}

void RenderWindow::clear()
{
    SDL_RenderClear(renderer);
}

void RenderWindow::render(Entity &entity)
{
    // SDL_Rect rect = entity.getRect();
    // rect.x = entity.getPos().x;
    // rect.y = entity.getPos().y;
    // SDL_RenderCopy(renderer, entity.getTexture(), NULL, &rect);

    SDL_Rect rect_src;
    rect_src.x = entity.getRect().x;
    rect_src.y = entity.getRect().y;
    rect_src.w = entity.getRect().w;
    rect_src.h = entity.getRect().h;

    SDL_Rect rect_dst;
    rect_dst.x = entity.getPos().x;
    rect_dst.y = entity.getPos().y;
    rect_dst.w = entity.getRect().w * entity.getScale();
    rect_dst.h = entity.getRect().h * entity.getScale();
    SDL_RenderCopy(renderer, entity.getTexture(), &rect_src, &rect_dst);
}

void RenderWindow::display()
{
    SDL_RenderPresent(renderer);
}

void RenderWindow::cleanUp()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

int RenderWindow::getRefreshRate()
{
    int displayIndex = SDL_GetWindowDisplayIndex(window);

    SDL_DisplayMode mode;

    SDL_GetDisplayMode(displayIndex, 0, &mode);

    return mode.refresh_rate;
}