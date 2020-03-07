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

#include "vscge/logger/tee.h"

#include <iostream>
#include <string>

namespace vs::Logger {
Tee::Tee(std::string_view filepath) { file_.open(filepath.data()); }

Tee::~Tee() { file_.close(); }

template <typename Readable>
Tee& Tee::operator<<(Readable message) {
  std::cout << message;
  file_ << message;
  return *this;
}

template class Tee& Tee::operator<<(std::string);
template class Tee& Tee::operator<<(char);
}  // namespace vs::Logger
