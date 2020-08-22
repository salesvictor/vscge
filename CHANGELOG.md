# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

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
