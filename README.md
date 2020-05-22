# GameKit

[![Build Status](https://travis-ci.com/Unarelith/GameKit.svg?branch=master)](https://travis-ci.com/Unarelith/GameKit)
[![Documentation](https://codedocs.xyz/Unarelith/GameKit.svg)](https://codedocs.xyz/Unarelith/GameKit/)
[![License](https://img.shields.io/badge/license-LGPLv2.1%2B-blue.svg)](https://www.gnu.org/licenses/old-licenses/lgpl-2.1.en.html)

## Description

GameKit is a library I made to avoid duplicating code in my projets.

It's a small game engine built on top of SFML and OpenGL.

## Documentation

- [API Documentation](https://codedocs.xyz/Unarelith/GameKit)

## Linux packages

- **ArchLinux:** `gamekit-git` (AUR)

## How to compile

- Dependencies:
    - A compiler with C++14 support
    - `git` and [CMake](http://www.cmake.org/download/)
    - OpenGL >= 2.1
    - _Linux users: Check your distribution repositories for packages._
- Run `cmake -B build . && cmake --build build -j8 && sudo cmake --install build`
- Or `mkdir build && cd build && cmake .. && make -j8 && sudo make install` (for old CMake versions)

## License

The code is licensed under LGPL v2.1.

