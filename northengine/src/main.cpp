//
// Created by deshik on 21.01.2023.
//

#include "northengine/northengine.h"

#include <glad/glad.h>

#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_sdl.h>

#include <string>
#include <iostream>

#include "northengine/interface/style.h"

int main(int argv, char **args) {
    (void) args;
    (void) argv;

    Init();

    auto *window = new Window("NorthEngine", 800, 600);
    window->SetResizable(true);
    Window::SetVSync(false);

    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
    InitImGui(window);

    std::cout << "Creating camera" << std::endl;
    auto *camera = new Camera();
    std::cout << "Camera created" << std::endl;

    auto *shader = new Shader("assets/vertex.glsl", "assets/fragment.glsl");

    auto *texture = new Texture("assets/house.png");

    auto *meshData = new MeshData();

    float vertices[] = {
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
            -0.5f, 0.5f, 0.0f, 0.0f, 1.0f
    };

    meshData->SetVertices(vertices, 20);

    unsigned int indices[] = {
            0, 1, 2,
            0, 2, 3
    };

    meshData->AddIndices(indices, 6);

    Mesh *mesh = new Mesh(meshData);
    mesh->GenerateBuffers();

    LoadColors();
    ImGui::StyleColorsDark();
    ImGuiStyle &style = ImGui::GetStyle();
    LoadStyle(style);

    std::cout << "Setting camera position" << std::endl;
    camera->SetPosition(glm::vec3(0.0f, 0.0f, 3.0f));
    glm::vec2 screenSize = window->GetSize();

    std::cout << "Update model matrix" << std::endl;
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));

    std::cout << "Update projection matrix" << std::endl;
    shader->Use();
    shader->SetMat4("model", model);
    shader->SetMat4("projection", camera->GetProjectionMatrix(screenSize.x, screenSize.y));

    std::cout << "Update shader" << std::endl;
    camera->UpdateShader(*shader);
    std::cout << "Shader updated" << std::endl;

    SDL_Event event;
    bool running = true;
    bool editStyle = false;

    std::cout << "Starting main loop" << std::endl;

    while (running) {
        static float lastFrame = 0.0f;
        float deltaTime = (float) (SDL_GetTicks() - lastFrame) / 1000.0f;
        lastFrame = (float) SDL_GetTicks();

        while (SDL_PollEvent(&event)) {
            ImGui_ImplSDL2_ProcessEvent(&event);

            if (event.type == SDL_QUIT) {
                running = false;
            } else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    running = false;
                } else if (event.key.keysym.sym == SDLK_F7) {
                    editStyle = !editStyle;
                } else if (event.key.keysym.sym == SDLK_SPACE) {

                } else {
                    auto cameraPosition = glm::vec3(0);
                    const float SPEED = 20.0f;

                    // TODO: исправить дёрганность камеры
                    switch (event.key.keysym.sym) {
                        case SDLK_w:
                            cameraPosition.z += SPEED;
                            break;
                        case SDLK_s:
                            cameraPosition.z -= SPEED;
                            break;
                        case SDLK_a:
                            cameraPosition.x -= SPEED;
                            break;
                        case SDLK_d:
                            cameraPosition.x += SPEED;
                            break;
                        case SDLK_q:
                            cameraPosition.y -= SPEED;
                            break;
                        case SDLK_e:
                            cameraPosition.y += SPEED;
                            break;
                    }

                    cameraPosition *= deltaTime;
                    camera->MoveLocal(cameraPosition);
                }
            } else if (event.type == SDL_WINDOWEVENT) {
                if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
                    screenSize = window->GetSize();
                    std::cout << "Window resized: " << screenSize.x << "x" << screenSize.y << std::endl;
                    glViewport(0, 0, screenSize.x, screenSize.y);
                    shader->SetMat4("projection", camera->GetProjectionMatrix(screenSize.x, screenSize.y));
                }
            } else if (!ImGui::GetIO().WantCaptureMouse) {
                if (event.type == SDL_MOUSEMOTION) {
                    if (event.motion.state & SDL_BUTTON_LMASK) {
                        camera->ProcessMouseMovement(event.motion.xrel, event.motion.yrel);
                        camera->UpdateShader(*shader);
                    }
                } else if (event.type == SDL_MOUSEWHEEL) {
                    camera->SetZoom(event.wheel.y);
                }
            }
        }

        static unsigned int maxFps = 120;
        if (deltaTime < 1000.0f / maxFps) {
            SDL_Delay((1000.0f / maxFps) - deltaTime);
        }

        static bool vsync = false;
        static glm::vec2 windowedSize = window->GetSize();
        static glm::vec2 fullscreenSize = windowedSize;
        static int fullscreenMode = 0;

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader->Use();

        texture->Bind(0);
        camera->UpdateShader(*shader);
        shader->SetTexture("texture1", 0);
        shader->SetBool("invertVertical", true);
        DrawMesh(*mesh, shader);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Mesh");
        {
            if (ImGui::CollapsingHeader("MeshData")) {
                MeshData *meshData = mesh->GetMeshData();
                ImGui::Text("Vertices: %d", meshData->GetVerticesCount());
                if (ImGui::CollapsingHeader("Vertices")) {
                    float *vertices;
                    size_t verticesCount;
                    meshData->GetVertices(&vertices, verticesCount);
                    for (size_t i = 0; i < verticesCount; i++) {
                        ImGui::Text("%f", vertices[i]);
                    }
                }
                ImGui::Text("Indices: %d", meshData->GetIndicesCount());
                if (ImGui::CollapsingHeader("Indices")) {
                    unsigned int *indices;
                    size_t indicesCount;
                    meshData->GetIndices(&indices, indicesCount);
                    for (size_t i = 0; i < indicesCount; i++) {
                        ImGui::Text("%d", indices[i]);
                    }
                }

            }

            ImGui::Separator();

            if (ImGui::CollapsingHeader("Texture")) {
                ImGui::Text("Texture size: %dx%d", texture->GetWidth(), texture->GetHeight());
            }

            ImGui::Separator();

            if (ImGui::CollapsingHeader("Matrix")) {
                ImGui::Text("Model matrix:");
                ImGui::Text("Projection matrix:");
            }

        }
        ImGui::End();

        ImGui::Begin("Settings");
        static bool isVsyncEnabled = false;
        ImGui::Checkbox("VSync", &vsync);
        if (isVsyncEnabled != vsync) {
            isVsyncEnabled = vsync;
            Window::SetVSync(vsync);
        }
        ImGui::SliderInt("Max FPS", (int *) &maxFps, 1, 255);
        ImGui::SliderFloat2("Windowed Size", &windowedSize.x, 0, 1920);
        ImGui::SliderFloat2("Fullscreen Size", &fullscreenSize.x, 0, 1920);

        static bool currentFullscreen = false;
        ImGui::Checkbox("Current resolution", &currentFullscreen);
        if (currentFullscreen) {
            fullscreenSize = {1920, 1080};
        }

        static int fullscreen = 0;
        ImGui::Combo("Fullscreen", &fullscreen, "Windowed\0FullScreen\0Borderless\0");
        if (fullscreen != fullscreenMode) {
            fullscreenMode = fullscreen;
            window->SetFullscreen(static_cast<FullscreenMode>(fullscreenMode));
        }

        ImGui::End();

        if (editStyle) {
            SetStyle();
        }

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        window->SwapBuffers();
    }

    delete camera;
    delete texture;
    delete shader;
    delete mesh;

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();

    delete window;

    Quit();

    return 0;
}

