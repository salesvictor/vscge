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

#include "vscge/core/renderer.h"

#include <Windows.h>
#include <gl/gl.h>

#include <algorithm>
#include <cassert>
#include <cwchar>
#include <vector>

#include "vscge/core/types.h"
#include "vscge/debug/debug.h"
#include "vscge/instrumentation/profiler.h"

namespace vs {
struct Internals {
  HDC device_context;
};

Internals internals;

void Renderer::Initialize(const Window& window, const Size& /*font_size*/) {
  VS_PROFILE_FUNCTION();
  // TODO(Victor): Move this to a platform layer, maybe break into a separate
  // RenderAPI? Create Device Context
  internals.device_context = GetDC(static_cast<HWND>(window.handle_));

  PIXELFORMATDESCRIPTOR pixel_format{};
  pixel_format.nSize    = sizeof(PIXELFORMATDESCRIPTOR);  // Size of this pfd
  pixel_format.nVersion = 1;                              // Version number.
  pixel_format.dwFlags  = PFD_DRAW_TO_WINDOW |            // Support window.
                         PFD_SUPPORT_OPENGL |             // Support OpenGL.
                         PFD_DOUBLEBUFFER;                // Double buffered.
  pixel_format.iPixelType   = PFD_TYPE_RGBA;              // RGBA type.
  pixel_format.cColorBits   = 32;                         // Color depth.
  pixel_format.cDepthBits   = 24;                         // Z-buffer.
  pixel_format.cStencilBits = 8;                          // Stencil buffer.
  pixel_format.iLayerType   = PFD_MAIN_PLANE;             // Main layer.

  int pixel_format_index =
      ChoosePixelFormat(internals.device_context, &pixel_format);
  DescribePixelFormat(internals.device_context, pixel_format_index,
                      sizeof(PIXELFORMATDESCRIPTOR), &pixel_format);
  SetPixelFormat(internals.device_context, pixel_format_index, &pixel_format);

  auto glRenderContext = wglCreateContext(internals.device_context);
  if (!wglMakeCurrent(internals.device_context, glRenderContext)) {
    VS_ASSERT(false);
  }

  // VSync
  auto vsglSwapInterval =
      reinterpret_cast<BOOL (*)(int)>(wglGetProcAddress("wglSwapIntervalEXT"));
  vsglSwapInterval(1);

  // New OpenGL Context
  auto vsglCreateContextAttribsARB =
      reinterpret_cast<HGLRC (*)(HDC, HGLRC, const int*)>(
          wglGetProcAddress("wglCreateContextAttribsARB"));

  constexpr int VSGL_CONTEXT_VERSION_MAJOR_ARB             = 0x2091;
  constexpr int VSGL_CONTEXT_VERSION_MINOR_ARB             = 0x2092;
  constexpr int VSGL_CONTEXT_PROFILE_MASK_ARB              = 0x9126;
  constexpr int VSGL_CONTEXT_CORE_PROFILE_BIT_ARB          = 0x00000001;
  constexpr int VSGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB = 0x00000002;

  // clang-format off
  constexpr int attribs[] = {
      VSGL_CONTEXT_VERSION_MAJOR_ARB, 4,
      VSGL_CONTEXT_VERSION_MINOR_ARB, 1,
      VSGL_CONTEXT_PROFILE_MASK_ARB,  VSGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB,
      NULL,
  };
  // clang-format on

  HGLRC share_context  = 0;
  HGLRC modern_context = vsglCreateContextAttribsARB(internals.device_context,
                                                     share_context, attribs);

  if (!modern_context) {
    VS_ASSERT(false);
  }

  wglMakeCurrent(nullptr, nullptr);
  wglDeleteContext(glRenderContext);
  if (!wglMakeCurrent(internals.device_context, modern_context)) {
    VS_ASSERT(false);
  }

  glRenderContext = modern_context;

  // Setup Viewport and Clear Screen for the first time.
  glViewport(0, 0, window.size_.width, window.size_.height);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void ClearScreen() { VS_PROFILE_FUNCTION(); }

void DrawBuffer(const std::vector<Vertex>& /*buffer*/) {
  VS_PROFILE_FUNCTION();
}

void DrawLine(const Point& /*p1*/, const Point& /*p2*/,
              const VertexProps& /*props*/) {
  VS_PROFILE_FUNCTION();
}

void DrawRect(const Rect& rect, const VertexProps& props) {
  VS_PROFILE_FUNCTION()
  int x0 = rect.x;
  int y0 = rect.y;
  int x1 = rect.x + rect.width - 1;   // NOLINT
  int y1 = rect.y + rect.height - 1;  // NOLINT

  DrawLine({x0, y0}, {x1, y0}, props);  // Top
  DrawLine({x1, y0}, {x1, y1}, props);  // Right
  DrawLine({x1, y1}, {x0, y1}, props);  // Bottom
  DrawLine({x0, y1}, {x0, y0}, props);  // Left
}

void FillRect(const Rect& rect, const VertexProps& props) {
  VS_PROFILE_FUNCTION();
  for (int y = rect.y; y < rect.y + rect.height; ++y) {
    DrawLine({rect.x, y}, {rect.x + rect.width, y}, props);  // NOLINT
  }
}

void Renderer::Render() {
  VS_PROFILE_FUNCTION();

  SwapBuffers(internals.device_context);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
}  // namespace vs
