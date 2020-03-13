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

// Generic helper definitions for shared library support
#if defined(_WIN32) || defined(__CYGWIN__)
#  define VS_HELPER_DLL_IMPORT __declspec(dllimport)
#  define VS_HELPER_DLL_EXPORT __declspec(dllexport)
#  define VS_HELPER_DLL_LOCAL
#else
#  if __GNUC__ >= 4  // TODO(Victor): Check if other compilers support this.
#    define VS_HELPER_DLL_IMPORT __attribute__((visibility("default")))
#    define VS_HELPER_DLL_EXPORT __attribute__((visibility("default")))
#    define VS_HELPER_DLL_LOCAL  __attribute__((visibility("hidden")))
#  else
#    define VS_HELPER_DLL_IMPORT
#    define VS_HELPER_DLL_EXPORT
#    define VS_HELPER_DLL_LOCAL
#  endif
#endif

// Now we use the generic helper definitions above to define VS_API and
// VS_LOCAL. VS_API is used for the public API symbols. It either DLL imports or
// DLL exports (or does nothing for static build) VS_LOCAL is used for non-api
// symbols.
#ifdef VS_DLL
#  ifdef VS_DLL_EXPORTS
#    define VS_API VS_HELPER_DLL_EXPORT
#  else
#    define VS_API VS_HELPER_DLL_IMPORT
#  endif  // VS_DLL_EXPORTS
#  define VS_LOCAL VS_HELPER_DLL_LOCAL
#else
#  define VS_API
#  define VS_LOCAL
#endif  // VS_DLL
