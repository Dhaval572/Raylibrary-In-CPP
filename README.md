# Raylib Project

[![License: Zlib](https://img.shields.io/badge/License-Zlib-lightgrey.svg)](https://opensource.org/licenses/Zlib)
[![Build Status](https://img.shields.io/badge/build-passing-brightgreen.svg)](https://github.com/raysan5/raylib)

## Introduction
Raylib is a simple and easy-to-use library to enjoy videogames programming. It is highly portable and cross-platform, making it a great choice for game development.

## Features
- Simple and easy-to-use API
- Cross-platform support
- Extensive documentation and examples

## Installation
Follow these steps to install the project:
1. Download the Raylib library from the [official website](https://www.raylib.com/).

## Download

Download this as a setup structure
➡️ [Download raylib_setup.rar](./raylib_setup.rar)


## Usage
To use Raylib in your project, include the following code in your main file:

```c
#include <raylib.h>

int main()
{
    InitWindow(600, 500, "Welcome to raylib"); // Set screen width and height

	// Main game loop
    while (!WindowShouldClose())
    {
        BeginDrawing(); 

        // Some statements
		//-----***-----//
		//-----***-----//
		//-----***-----//

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
