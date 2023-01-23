# NorthEngine

# Dependencies
* [SDL2](https://www.libsdl.org/download-2.0.php)
* [SDL2_image](https://github.com/libsdl-org/SDL_image/)
* [SDL2_ttf](https://github.com/libsdl-org/SDL_ttf/)
* [glad](https://glad.dav1d.de/)
* [glm](https://glm.g-truc.net/0.9.9/index.html)

# Features
* [x] Camera
* [ ] 2D Rendering
* [x] 3D Rendering
* [x] Shader
* [x] Texture
* [ ] Font
* [x] ImGui interface with styles
* [x] Window
* [ ] Input
* [x] Mesh
* [ ] Model loading
* [ ] Scene
* [ ] Entity
* [ ] Component
* [ ] Script
* [ ] Audio
* [ ] Physics
* [ ] Networking
* [ ] Editor

# Build
### Windows
Use build.bat or:
```bash
    cd northengine
    mkdir build
    cd build
    cmake .. -G "Unix Makefiles"
    cmake --build .
```

### Linux
```bash
    cd northengine
    mkdir build
    cd build
    cmake ..
    cmake --build .
    chmod +x northengine
```

# Run
``./northengine/northengine`` on Linux \
``run.bat`` or double click on `northengine.exe` on Windows 

# License
[DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE](https://en.wikipedia.org/wiki/WTFPL) 


