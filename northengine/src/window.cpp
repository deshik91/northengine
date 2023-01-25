//
// Created by deshik on 22.01.2023.
//

#include "northengine/window.h"

#include <iostream>

Window::Window() {
    window = SDL_CreateWindow("North Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600,
                              SDL_WINDOW_OPENGL);

    context = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, context);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    SDL_GL_SetSwapInterval(1);

    if (!gladLoadGLLoader((GLADloadproc) SDL_GL_GetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_DEPTH_TEST);
}

Window::Window(const char *title, int width, int height) {
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height,
                              SDL_WINDOW_OPENGL);
    context = SDL_GL_CreateContext(window);

    SDL_GL_MakeCurrent(window, context);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    SDL_GL_SetSwapInterval(1);

    if (!gladLoadGLLoader((GLADloadproc) SDL_GL_GetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }
}

Window::~Window() {
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
}

void Window::SetTitle(const char *title) {
    SDL_SetWindowTitle(window, title);
}

const char *Window::GetTitle() {
    return SDL_GetWindowTitle(window);
}

void Window::SetFullscreen(FullscreenMode fullscreen) {
    switch (fullscreen) {
        case FullscreenMode::WINDOWED:
            SDL_SetWindowFullscreen(window, 0);
            break;
        case FullscreenMode::FULLSCREEN:
            SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
            break;
        case FullscreenMode::FULLSCREEN_DESKTOP:
            SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
            break;
    }
}

void Window::SetResizable(bool resizable) {
    SDL_SetWindowResizable(window, resizable ? SDL_TRUE : SDL_FALSE);
}

void Window::SetBorderless(bool borderless) {
    SDL_SetWindowBordered(window, borderless ? SDL_FALSE : SDL_TRUE);
}

void Window::SetVSync(bool vsync) {
    SDL_GL_SetSwapInterval(vsync ? 1 : 0);
}

void Window::SetIcon(const char *iconPath) {
    SDL_Surface *icon = SDL_LoadBMP(iconPath);
    SDL_SetWindowIcon(window, icon);
    SDL_FreeSurface(icon);
}

void Window::SetPosition(int x, int y) {
    SDL_SetWindowPosition(window, x, y);
}

int Window::GetX() {
    int x;
    SDL_GetWindowPosition(window, &x, nullptr);
    return x;
}

int Window::GetY() {
    int y;
    SDL_GetWindowPosition(window, nullptr, &y);
    return y;
}

glm::vec2 Window::GetPosition() {
    int x, y;
    SDL_GetWindowPosition(window, &x, &y);
    return {x, y};
}

void Window::SetSize(int width, int height) {
    SDL_SetWindowSize(window, width, height);
}

int Window::GetWidth() {
    int width;
    SDL_GetWindowSize(window, &width, nullptr);
    return width;
}

int Window::GetHeight() {
    int height;
    SDL_GetWindowSize(window, nullptr, &height);
    return height;
}

glm::vec2 Window::GetSize() {
    int width, height;
    SDL_GetWindowSize(window, &width, &height);
    return {width, height};
}


SDL_Window *Window::GetSDLWindow() {
    return window;
}

SDL_GLContext Window::GetGLContext() {
    return context;
}

void Window::SwapBuffers() {
    SDL_GL_SwapWindow(window);
}
