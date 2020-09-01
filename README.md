[![GitHub license](https://img.shields.io/github/license/salesvictor/vscge?color=blue&style=plastic)](https://github.com/salesvictor/vscge/blob/master/LICENSE) ![build](https://github.com/salesvictor/vscge/workflows/build/badge.svg)

# VS Component Game Engine

# About

This engine is being designed so that I could have a big C++ project and learn
all the components that make one.

## Design

The goal here is to have a good SWE Project. So, as the name suggests, the
engine is broken down into modularized, self-contained, components, trying to
follow as close as possible the best SWE practices.

## Multiplatform

Although much of what's been done so far is Windows specific, I want this to
compile and run on other OSes eventually.

## Barebones

Focusing on the learning aspect, much of what's here is implemented in-house,
using only the C++ Standard Library as the external dependency.

## Dependencies

* [gl3w](https://github.com/skaslev/gl3w)
    * Unfortunately, you should install this before building VSCGE
* [Google Test](https://github.com/google/googletest)
    * Used for testing. If building those, it is automatically downloaded for you

# Build Instructions

Hopefully you should be able to do an out-source build without any pain. By
that, I mean creating a `build` directory and calling `cmake` from there:

```
mkdir build && cd build
cmake ..
cmake . --build
```

## Available Options

They are all on the top `CMakeLists.txt` file, here is a summary:

| Option                 | Description                  | Default |
| ---------------------- | ---------------------------- | ------- |
|                        | Generic Build Options        |         |
| `BUILD_SHARED_LIBS`    | Build using shared libraries | OFF     |
| `BUILD_VSCGE_TESTS`    | Build tests                  | OFF     |
| `BUILD_VSCGE_EXAMPLES` | Build examples               | OFF     |
|                        |                              |         |
|                        | Feature Enabling Options     |         |
| `VS_ENABLE_ASSERTS`    | Enable `VS_ASSERT*` macros   | ON      |
| `VS_ENABLE_PROFILER`   | Enable profiler              | ON      |
| `VS_ENABLE_LOGGER`     | Enable logger                | ON      |

# Examples

Those are on the `examples` folder.

# Road Map

[Trello](https://trello.com/b/ClSxANlX/vscge-dev).

# Sources and Inspirations

## Game/Engine Tutorials

* [Handmade Hero](https://handmadehero.org/)
* [TheCherno](https://www.youtube.com/channel/UCQ-W1KE9EYfdxhL6S4twUNw)
* [Gamasutra - Writing a Game Engine From Scratch](https://gamasutra.com/blogs/MichaelKissner/20151027/257369/Writing_a_Game_Engine_from_Scratch__Part_1_Messaging.php)
* [Game Programming Patterns](http://gameprogrammingpatterns.com/)

## Open Source Projects

* [dlib](https://github.com/davisking/dlib)
* [OpenCV](https://github.com/opencv/opencv)

## C++

* [Bartek's coding blog](https://www.bfilipek.com/)
* [Fluent C++](https://www.fluentcpp.com/)
* [Simplify C++](https://arne-mertz.de/)

## CMake

* [The Ultimate Guide to Modern CMake](https://rix0r.nl/blog/2015/08/13/cmake-guide/)
* [An Introduction to Modern CMake](https://cliutils.gitlab.io/modern-cmake/)
* [CMake - Introduction and best practices](https://www.slideshare.net/DanielPfeifer1/cmake-48475415)
* [It's Time To Do CMake Right](https://pabloariasal.github.io/2018/02/19/its-time-to-do-cmake-right/)
* [CMake Tutorial](https://cmake.org/cmake/help/latest/guide/tutorial/index.html)
* [Modern CMake Tips](https://pspdfkit.com/blog/2018/modern-cmake-tips/)
* [Crascit](https://crascit.com/)

# OpenGL

* [Learn OpenGL](https://learnopengl.com)