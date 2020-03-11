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

#include "vscge/instrumentation/profiler.h"

#include <fstream>
#include <iomanip>
#include <mutex>
#include <optional>
#include <sstream>
#include <string>

// TODO(Victor): See about making asynchronous profiling, right now the
// profiling consumes the engine resources.
namespace vs::Profiler {
using FloatingPointMicroseconds = std::chrono::duration<double, std::micro>;

struct ProfileResult {
  std::string_view name;

  FloatingPointMicroseconds Start;
  std::chrono::microseconds elapsed_time;
  std::thread::id ThreadID;
};

struct Internals {
  std::mutex mutex;
  std::optional<std::string> current_session;
  std::ofstream output_stream;
};

Internals internals;

void WriteHeader() {
  internals.output_stream << R"({"otherData": {},"traceEvents":[{})";
  internals.output_stream.flush();
}

void WriteFooter() {
  internals.output_stream << "]}";
  internals.output_stream.flush();
}

// Note: you must already own lock on mutex before
// calling InternalEndSession()
void EndSessionImpl() {
  if (internals.current_session) {
    WriteFooter();
    internals.output_stream.close();
    internals.current_session = std::nullopt;
  }
}

void BeginSession(std::string_view name, std::string_view filepath) {
  std::lock_guard lock(internals.mutex);
  if (internals.current_session) {
    // If there is already a current session, then close it before beginning
    // new one. Subsequent profiling output meant for the original session
    // will end up in the newly opened session instead.  That's better than
    // having badly formatted profiling output.
    EndSessionImpl();
  }
  internals.output_stream.open(filepath.data());

  if (internals.output_stream.is_open()) {
    internals.current_session = name;
    WriteHeader();
  }
}

void EndSession() {
  std::lock_guard lock(internals.mutex);
  EndSessionImpl();
}

void WriteProfile(const ProfileResult& result) {
  std::stringstream json;

  std::string_view name = result.name;
  // std::replace(name.begin(), name.end(), '"', '\'');

  json << std::setprecision(3) << std::fixed;
  json << ",{";
  json << R"("cat":"function",)";
  json << R"("dur":)" << result.elapsed_time.count() << ',';
  json << R"("name":")" << name << "\",";
  json << R"("ph":"X",)";
  json << R"("pid":0,)";
  json << R"("tid":)" << result.ThreadID << ",";
  json << R"("ts":)" << result.Start.count();
  json << "}";

  std::lock_guard lock(internals.mutex);
  if (internals.current_session) {
    internals.output_stream << json.str();
    internals.output_stream.flush();
  }
}

Timer::~Timer() {
  auto endTimepoint = std::chrono::steady_clock::now();
  auto highResStart =
      FloatingPointMicroseconds(start_time_point_.time_since_epoch());
  auto elapsedTime =
      std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint)
          .time_since_epoch() -
      std::chrono::time_point_cast<std::chrono::microseconds>(start_time_point_)
          .time_since_epoch();

  Profiler::WriteProfile(
      {name_, highResStart, elapsedTime, std::this_thread::get_id()});
}
}  // namespace vs::Profiler
