//
// Created by deshik on 22.01.2023.
//

#ifndef NORTH_ENGINE_LANG_WINDOW_H
#define NORTH_ENGINE_LANG_WINDOW_H

#define SDL_MAIN_HANDLED
#include <glad/glad.h>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>

enum FullscreenMode {
    WINDOWED,
    FULLSCREEN,
    FULLSCREEN_DESKTOP
};

class Window{
public:
    Window();
    Window(const char *title, int width, int height);
    ~Window();

    void MakeCurrent();


    void SetTitle(const char *title);

    const char *GetTitle();


    void SetFullscreen(FullscreenMode fullscreen);

    void SetResizable(bool resizable);

    void SetBorderless(bool borderless);

    // TODO: move it to engine settings
    static void SetVSync(bool vsync);

    void SetIcon(const char *iconPath);


    void SetPosition(int x, int y);

    int GetX();

    int GetY();

    glm::vec2 GetPosition();


    void SetSize(int width, int height);

    int GetWidth();

    int GetHeight();

    glm::vec2 GetSize();

    SDL_Window *GetSDLWindow();

    SDL_GLContext GetGLContext();

    void SwapBuffers();

private:
    SDL_Window *window;
    SDL_GLContext context;
};

#endif //NORTH_ENGINE_LANG_WINDOW_H
