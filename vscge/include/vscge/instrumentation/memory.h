// Copyright 2020 Victor Sales
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef VSCGE_INCLUDE_VSCGE_INSTRUMENTATION_MEMORY_H_
#define VSCGE_INCLUDE_VSCGE_INSTRUMENTATION_MEMORY_H_

#include <cstdlib>
#include <string>

#include "vscge/core/core.h"
#include "vscge/logger/logger.h"

struct VS_API Memory {
  std::size_t size = 0;
  std::string unit = "B";

  constexpr std::size_t Bytes() const { return size; }
  constexpr std::size_t Kilobytes() const { return size >> 10; }
  constexpr std::size_t Megabytes() const { return size >> 20; }
  constexpr std::size_t Gigabytes() const { return size >> 30; }
  constexpr std::size_t HumanReadable() const {
    if (!Kilobytes()) return Bytes();
    if (!Megabytes()) return Kilobytes();
    if (!Gigabytes()) return Megabytes();
    return Gigabytes();
  }
  const std::string& Unit() {
    UpdateUnit();
    return unit;
  }

  operator std::string() {
    return std::to_string(HumanReadable()) + Unit();
  }

 private:
  void UpdateUnit() {
    unit = "B";
    if (Kilobytes()) unit = "KB";
    if (Megabytes()) unit = "MB";
    if (Gigabytes()) unit = "GB";
  }
};

Memory memory = {};

void* operator new(std::size_t size) {
  memory.size +=size;
  return std::malloc(size);
}

void operator delete(void* thing, std::size_t size) {
  memory.size -= size;
  std::free(thing);
}

#endif  // VSCGE_INCLUDE_VSCGE_INSTRUMENTATION_MEMORY_H_
