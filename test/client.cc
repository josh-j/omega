#include <iostream>
#include <vector>
#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#endif

#include "client.h"
#include "brush.h"
#include "renderer_ogl.h"
#include "state.h"
#include "window.h"
#include "io.h"
#include "panel.h"

namespace {
char work_path[256];
omega_test::RendererOGL renderer;
// system ui(&renderer); // glrenderer()
// logviewer* logviewer = new logviewer;
} // namespace

using namespace omega;

void CL_Initialize() {
  omega::s.renderer = &renderer;
  lgr::Sink_Ofstream::Init("omega_log.txt", false, false);
  lgr::emit() << "Init";
  renderer.BuildFont("/usr/share/fonts/droid/DroidSans.ttf", 14, 0, 0, 0);

  Panel::Declare::Begin();
  Panel::Declare::Color(192, 128, 128, 128);
  Panel::Declare::Area(Rect(50, 50, 150, 150));

  // needs to hold Pressed state
  //
  // auto changeEntered = []() {

  // };

  auto changePress = []() {
    if (Panel::Contains(IO::ind.mouse_position_.x, IO::ind.mouse_position_.y)) {
      s.panel_data[s.current_id].is_hovered_ = true;
      if (IO::ind.mouse_pressed_) {
        s.panel_data[s.current_id].is_held_ = true;
      } else {
        s.panel_data[s.current_id].is_held_ = false;
      }
    } else {
      s.panel_data[s.current_id].is_hovered_ = false;
    }

    if (s.panel_data[s.current_id].is_held_) {
      s.abs_rect->x += IO::ind.mouse_move_delta_.x;
      s.abs_rect->y += IO::ind.mouse_move_delta_.y;
    }
  };

  IO::Declare::OnMouseMove(changePress);
  Panel::Declare::Draw();
  {
    Panel::Declare::Begin();
    Panel::Declare::Color(128, 128, 192, 128);
    Panel::Declare::Area(Rect(5, 5, 25, 25));
    auto changeColor = []() { s.color.set(255, 255, 255, 255); };
    IO::Declare::OnMousePress(changeColor);
    Panel::Declare::Draw();
    Panel::Declare::End();
  }
  Panel::Declare::End();
}

void CL_Draw() {

  // Color clr(192,128,128, 128);
  // if (IO::ind.mouse_button_ == omega::IO::MBTN_LEFT)
  //   clr.set(192,128,128,255);

  // Window::SetShape(
  //     50, 50, 150, 150,
  //     clr); // this isn't always going to be here
  // Window::Draw();
  // {
  //   Window::SetShape(50, 50, 75, 75,
  //                    Color(192, 128, 128, 192)); // needs to be relative to prev
  //   Window::Draw();
  // }

  renderer.SetColor(255, 255, 255, 255);
  renderer.RenderText(0, 300, 300, "Testing one two THREE!");
  omega::dm.execute();
  IO::EndFrame();
  s.EndFrame();
  /*
  **
  ** OnPress could set a flag is_moving = true, could call a callback for a button, could say highlight this text
  **
  ** Shape& shape = Panel::Declare::Shape(50,50,150,150,Color(kColorWhite));
  ** //IO::OnMouseMove(Panel::mover(shape)); // mover has to take ref shape
  ** IO::WhenMouseInShape(shape, IO::OnMousePress(Panel::mover(shape) fp)); // there's a million things you might want to do after a mouse press - but it has its default behavior
  **
  **
       */
}

void CL_MouseButton(int button, int state, int x, int y) {
  if (state == GLUT_DOWN) {
    if (button == GLUT_LEFT_BUTTON) {
      omega::IO::MousePress(omega::IO::MBTN_LEFT);
    } else if (button == GLUT_RIGHT_BUTTON) {
      omega::IO::MousePress(omega::IO::MBTN_RIGHT);
    }
  } else if (state == GLUT_UP) {
    if (button == GLUT_LEFT_BUTTON) {
      omega::IO::MouseRelease(omega::IO::MBTN_LEFT);
    } else if (button == GLUT_RIGHT_BUTTON) {
      omega::IO::MouseRelease(omega::IO::MBTN_RIGHT);
    }

  }
}

void CL_MouseMove(int x, int y) {
  omega::IO::MouseMove(x, y);
}

void CL_Keyboard(unsigned char key, int x, int y) {
  if (key == 27 || key == 'q')
    exit(0);

  omega::IO::KeyPress(key);
}

void CL_Shutdown() {
  renderer.DestroyFont(0);
}
