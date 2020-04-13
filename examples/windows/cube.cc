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

#include <Windows.h>
#include <gl/GL.h>
#include <vscge/vscge.h>

class BlankWindow : public vs::Application {
  void OnStart() override {
    glViewport(0, 0, 800, 600);
    glMatrixMode(GL_PROJECTION);
    glFrustum(-0.5F, 0.5F, -0.5F, 0.5F, 1.0F, 3.0F);

    /* position viewer */
    glMatrixMode(GL_MODELVIEW);
    glTranslatef(0.0F, 0.0F, -2.0F);

    /* position object */
    glRotatef(30.0F, 1.0F, 0.0F, 0.0F);
    glRotatef(30.0F, 0.0F, 1.0F, 0.0F);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
  }
  void OnUpdate(const vs::Timestep&) override {
    /* clear color and depth buffers */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* draw six faces of a cube */
    glBegin(GL_QUADS);
    glNormal3f(0.0F, 0.0F, 1.0F);
    glVertex3f(0.5F, 0.5F, 0.5F);
    glVertex3f(-0.5F, 0.5F, 0.5F);
    glVertex3f(-0.5F, -0.5F, 0.5F);
    glVertex3f(0.5F, -0.5F, 0.5F);

    glNormal3f(0.0F, 0.0F, -1.0F);
    glVertex3f(-0.5F, -0.5F, -0.5F);
    glVertex3f(-0.5F, 0.5F, -0.5F);
    glVertex3f(0.5F, 0.5F, -0.5F);
    glVertex3f(0.5F, -0.5F, -0.5F);

    glNormal3f(0.0F, 1.0F, 0.0F);
    glVertex3f(0.5F, 0.5F, 0.5F);
    glVertex3f(0.5F, 0.5F, -0.5F);
    glVertex3f(-0.5F, 0.5F, -0.5F);
    glVertex3f(-0.5F, 0.5F, 0.5F);

    glNormal3f(0.0F, -1.0F, 0.0F);
    glVertex3f(-0.5F, -0.5F, -0.5F);
    glVertex3f(0.5F, -0.5F, -0.5F);
    glVertex3f(0.5F, -0.5F, 0.5F);
    glVertex3f(-0.5F, -0.5F, 0.5F);

    glNormal3f(1.0F, 0.0F, 0.0F);
    glVertex3f(0.5F, 0.5F, 0.5F);
    glVertex3f(0.5F, -0.5F, 0.5F);
    glVertex3f(0.5F, -0.5F, -0.5F);
    glVertex3f(0.5F, 0.5F, -0.5F);

    glNormal3f(-1.0F, 0.0F, 0.0F);
    glVertex3f(-0.5F, -0.5F, -0.5F);
    glVertex3f(-0.5F, -0.5F, 0.5F);
    glVertex3f(-0.5F, 0.5F, 0.5F);
    glVertex3f(-0.5F, 0.5F, -0.5F);
    glEnd();
  }
};

VS_REGISTER_APP(BlankWindow);

