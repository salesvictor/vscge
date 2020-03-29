# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

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
