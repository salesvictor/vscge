# Copyright 2020 Victor Sales
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      https://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

target_sources(
  logger
  PUBLIC
    include/vscge/logger/logger.h
    include/vscge/logger/tee.h
  PRIVATE
    src/tee.cc
)

vscge_target_sources_platform(
  logger
  logger.cc
)

if(VS_ENABLE_LOGGER)
  add_executable(LoggerExe src/logger_entry_point.cc)
  target_link_libraries(LoggerExe vscge)
  target_compile_features(LoggerExe PRIVATE cxx_std_17)
endif()

target_link_libraries(
  logger
  PRIVATE
    vs::instrumentation
)
