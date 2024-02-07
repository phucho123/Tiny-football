#pragma once
#include "SDL.h"
#include "SDL_image.h"

#include "Entity.h"

class RenderWindow
{
public:
    RenderWindow(const char *p_title, int w, int h);

    SDL_Texture *loadTexture(const char *p_filePath);

    void clear();

    void render(Entity &entity);

    void display();

    void cleanUp();

    int getRefreshRate();

private:
    SDL_Window *window;
    SDL_Renderer *renderer;
};
