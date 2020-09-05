# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [0.18.0] - 2020-09-03

### Added

- Common CMake script for non-interface modules.
- `name` member to `Shader`. It's a surprise tool that will help us later.
- `VS_VALUE_TYPE()` macro to get a container's `value_type`.
- `VertexLayout` Class to specify how a vertex buffer should be read.
- `DataType` Enum Class to encapsulate GLSL primitive types on `VertexLayout`.
- `IndexBuffer` Class to encapsulate OpenGL's object.
- Reference Factories for `*Buffer` Classes.
- `VertexArray` Class to encapsalte OpenGL's object.

### Changed

- Fixed a bug on the common module script to now accept subfolders on the include directory.
- Triangle example to use new class pipeline.
- `vs::CreateRef` to `vs::MakeRef`, for consistency with `std` pointers.

### Removed

- `Vertex` Class, as it was substituted by raw float buffers and `VertexLayout`.

## [0.17.0] - 2020-09-03

### Added

- `v` shorthands for `Vec` classes.
- `graphics` module.
- `VertexBuffer` class.
- `VSCGEModules.cmake` with useful `macro`s for CMake.

### Changed

- `ui` shorthands to just `u`.
- Moved `Shader`, `Renderer`, and `Vertex` to `graphics`.
- Revamped non-interface modules' `CMakeLists.txt` to use `GLOB`, sue me.

## [0.16.1] - 2020-08-31

### Added

- Utility wrapper around `add_subdirectory()` to dump automatically generated files.

### Changed

- Way to handle external dependencies, from the `extern` folder to a `.cmake`.
- gl3w from a in-source dependency to an external one, as it was failing to lin (raised an [issue](https://github.com/skaslev/gl3w/issues/66)).

## [0.16.0] - 2020-08-30

### Added

- Proper Vertex Class.
- Uniforms in Shader Class.
- Transform lib.
- More tests on Vector.
- Swizzle conversion to Elem.
- VecBase Class to facilitate conversions.
- Elem constructor and other assignment operators for the Vectors.
- Conversion from Matrix to Vector.
- Matrix - Vector multiplication.

### Changed

- Triangle example to use Vertex and Shader classes more properly.
- Matrix Class template parameters to be `std::size_t` instead of `int`.

### Removed

- Bogus Vertex[Pros] Class from `types.h`.
- Placeholder drawing functions in Renderer.

## [0.15.5] - 2020-08-30

### Added

- Shader Class.
- Auxiliary header file with shorter type names.

### Changed

- Triangle example to use the new Shader Class.

## [0.15.4] - 2020-08-30

### Added

- Triangle example using shaders.
- Dependency on gl3w for OpenGL Extensions.

## Changed

- Swizzling build now occurs only if the python generator changes.

## [0.15.3] - 2020-08-28

### Added

- OpenGL Initialization.
- VSync.

### Changed

- Removed platform namespace

## [0.15.2] - 2020-08-22

### Added

- Tests on Vector `operator=`.

## [0.15.1] - 2020-08-22

### Added

- Project Trello.

### Changed

- Rewrote some parts of the README.
- Logger App name from Logger to LoggerExe to fix MSVC bug.

## [0.15.0] - 2020-04-13

### Added

- Initial OpenGL support.
- Cube example to demonstrate it.

### Changed

- `Renderer` and `Logger` are now proper classes.
- `clang-tidy` fix on the whole project.

## [0.14.1] - 2020-04-12

### Added

- `.clang-tidy` at the top level, instead of calling arguments with CMake.
- `VSCGEStaticAnalyzers.cmake` to facilitate module-level static checking.

### Changed

- `misc` module is now a global include directory.
- tests now are done at the module level.

## [0.14.0] - 2020-04-05

### Added

- Some more matrix types.

### Changed

- Platform layer is now inside the `platform` namespace.
- Module driven approach.

## [0.13.4] - 2020-03-30

### Added

- More tests.

### Fixed

- Addition of vectors.

## [0.13.3] - 2020-03-29

### Added

- Doxygen config file.
- Graphviz generated dependency.

### Changed

- Include header dependencies.

## [0.13.2] - 2020-03-29

### Changed

- Include header dependencies.

## [0.13.1] - 2020-03-29

### Fixed

- Linker problem with entry point.
- Wrong logger source included.

## [0.13.0] - 2020-03-29

### Added

- Platform layer with Windows and Windows Console.
- Window class to handle system input.
- Some utility CMake functions.

### Changed

- Moved logger to platform layer.
- Entry point handling.

## [0.12.0] - 2020-03-25

### Added

- Barebones maths library that supports vector swizzling.
- Windows window as default instead of Windows Console.
- Barebones platform layer.

### Removed

- Good part of the renderer/application API, as this was heavily dependent on Windows Console features.
