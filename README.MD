# Tetriste

## Screenshot

![Screenshot](screenshots/screenshot.png)

## Description

Tetriste is a game similar to the famous Tetris.\
It was made as part of a C programming project.

## Installation

### Manual installation

To install the game, just clone the git repository and compile the program with the `cmake . && make` command.

### Automatic installation

Hop over to the [release page](https://github.com/Exatio/tetriste/releases) and download the latest release.

## Usage

To launch the game in CLI mode, use the `./tetriste cli` command.
To start it in GUI mode, use the './tetriste gui' command.

## Controls

You can currently use the following controls:
- Insert a piece to the left
- Insert a piece to the right

The following controls are not yet implemented:
- Rotate through the shape cycle
- Rotate through the color cycle


## C Coding Style Conventions

These are the conventions used in the [raylib source code](https://github.com/raysan5/raylib/blob/master/CONVENTIONS.md), adapted for this project.

Code element |           Convention           | Example
--- |:------------------------------:| ---
Defines |            ALL_CAPS            | `#define PLATFORM_DESKTOP`
Macros |            ALL_CAPS            | `#define MIN(a,b) (((a)<(b))?(a):(b))`
Variables |           lowerCase            | `int screenWidth = 0;`, `float targetFrameTime = 0.016f;`
Local variables |           lowerCase            | `Vector2 playerPosition = { 0 };`
Global variables |           lowerCase            | `bool fullscreen = false;`
Constants |           lowerCase            | `const int maxValue = 8;`
Pointers |        MyType *pointer         | `Texture2D *array = NULL;`
float values |          always x.xf           | `float gravity = 10.0f`
Operators |         value1*value2          | `int product = value*6;`
Operators |         value1/value2          | `int division = value/4;`
Operators |        value1 + value2         | `int sum = value + 10;`
Operators |        value1 - value2         | `int res = value - 5;`
Struct |           TitleCase            | `struct Texture2D`, `struct Material`
Struct typedef |           TitleCase            | `typedef struct Texture { ... } Texture;`
Struct members |           lowerCase            | `texture.width`, `color.r`
Functions |           lowerCase            | `initWindow()`, `loadImageFromMemory()`
Functions params |           lowerCase            | `width`, `height`
Ternary Operator | (condition)? result1 : result2 | `printf("Value is 0: %s", (value == 0)? "yes" : "no");`

