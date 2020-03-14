[![GitHub license](https://img.shields.io/github/license/salesvictor/vscge?color=blue&style=plastic)](https://github.com/salesvictor/vscge/blob/master/LICENSE) ![build](https://github.com/salesvictor/vscge/workflows/build/badge.svg)

# VS Component Game Engine

----

# About

This engine is being designed so that I could have a big C++ project and learn all the components that make one.

## Modular Design/Unix Philosophy

I want as much as possible to be modularized, so that the individual components can be stripped out and used anywhere else, maybe even live on their own repo.

## Multiplatform

Although much of what's been done so far is Windows specific, I use Arch btw, and want this to compile and run on other OSes eventually.

## Barebones

As said before, the goal is to learn, and that's easier when everything is implemented in-house. Maybe I will allow some libs down the road if I feel that they are following the modular design approach -- i.e. are doing only **one** job, and doing it really well.

# Build Instructions

Hopefully you should be able to do an out-source build without any pain. By that, I mean creating a `build` directory and calling `cmake` from there:

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
| `BUILD_VSCGE_EXAMPLES` | Build examples               | ON      |
|                        |                              |         |
|                        | Feature Enabling Options     |         |
| `VS_ENABLE_ASSERTS`    | Enable `VS_ASSERT*` macros   | ON      |
| `VS_ENABLE_PROFILER`   | Enable profiler              | ON      |
| `VS_ENABLE_LOGGER`     | Enable logger                | ON      |

# Examples

Those are on the `examples` folder. So far there's only Game of Life implemented on the Windows Console.

# Road Map

TBD.

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
* [Simplify C++](https://arne-mertz.de/)

## CMake

* [The Ultimate Guide to Modern CMake](https://rix0r.nl/blog/2015/08/13/cmake-guide/)
* [An Introduction to Modern CMake](https://cliutils.gitlab.io/modern-cmake/)
* [CMake - Introduction and best practices](https://www.slideshare.net/DanielPfeifer1/cmake-48475415)
* [It's Time To Do CMake Right](https://pabloariasal.github.io/2018/02/19/its-time-to-do-cmake-right/)
* [CMake Tutorial](https://cmake.org/cmake/help/latest/guide/tutorial/index.html)
* [Modern CMake Tips](https://pspdfkit.com/blog/2018/modern-cmake-tips/)
