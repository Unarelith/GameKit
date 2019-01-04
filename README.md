# GameKit

[![Documentation](https://codedocs.xyz/Quent42340/GameKit.svg)](https://codedocs.xyz/Quent42340/GameKit/)
[![License](https://img.shields.io/badge/license-LGPLv2.1%2B-blue.svg)](https://www.gnu.org/licenses/old-licenses/lgpl-2.1.en.html)

### By Unarelith

- GameKit is a library I made to avoid duplicating a lot of code in my projects.

## Linux packages

- **ArchLinux:** `gamekit-git` (AUR)

## How to compile

- Dependencies:
    - [CMake](http://www.cmake.org/download/)
    - [SDL2](https://www.libsdl.org/download-2.0.php), [SDL2_image](https://www.libsdl.org/projects/SDL_image/), [SDL2_mixer](https://www.libsdl.org/projects/SDL_mixer/), [SDL2_ttf](https://www.libsdl.org/projects/SDL_ttf/)
    - OpenGL >= 2.1, [glm](http://sourceforge.net/projects/ogl-math/files/latest/download?source=files)
    - [glew](http://sourceforge.net/projects/glew/files/latest/download) or [glad](https://github.com/Dav1dde/glad) *(only required for Windows)*
    - [tinyxml2](http://leethomason.github.io/tinyxml2/)
    - _Linux users: Check your distribution repositories for packages._
- Run `mkdir build && cd build` at the root of the project folder
- Run `cmake .. && make && sudo make install`

## License

The code is licensed under LGPL v2.1.

