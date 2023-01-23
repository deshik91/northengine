//
// Created by deshik on 23.01.2023.
//

#ifndef NORTH_ENGINE_LANG_NORTHENGINE_H
#define NORTH_ENGINE_LANG_NORTHENGINE_H

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

void Init() {
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

}

void Quit() {
    SDL_Quit();
    IMG_Quit();
}

#include "northengine/window.h"

#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_sdl.h>

void InitImGui(Window *window) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void) io;

    ImGui_ImplSDL2_InitForOpenGL(window->GetSDLWindow(), window->GetGLContext());

    const char *glsl_version = "#version 330";
    ImGui_ImplOpenGL3_Init(glsl_version);
}

void QuitImGui() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
}

#include "northengine/graphics.h"
#include "northengine/camera.h"

#endif //NORTH_ENGINE_LANG_NORTHENGINE_H
