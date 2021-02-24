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
#include "mixins.h"
#include "button.h"
#include "theme.h"

namespace {
char work_path[256];
omega_test::RendererOGL renderer;
// system ui(&renderer); // glrenderer()
// logviewer* logviewer = new logviewer;
} // namespace

using namespace omega;

ThemeStates theme_states;
void CL_Initialize() {

  theme_states.themes[kStateNormal].is_bordered = true;
  theme_states.themes[kStateNormal].is_beveled = false;
  theme_states.themes[kStateNormal].color_border.set(64, 64, 64, 255);


  theme_states.themes[kStateHovered].color_border.set(0, 122, 204, 92);
  theme_states.themes[kStateHeld].color_border.set(0, 122, 204, 255);

  theme_states.themes[kStateFocused].color_background.set(92, 92, 92, 255);

  omega::s.renderer = &renderer;
  omega::s.brush.set_renderer(&renderer);
  lgr::Sink_Ofstream::Init("omega_log.txt", false, false);
  lgr::emit() << "Init";
  renderer.BuildFont("/usr/share/fonts/droid/DroidSans.ttf", 14, 0, 0, 0);

  struct basetype {};
  Painter<basetype> p;
  p.Paint();

  Panel::Declare::SetTheme(theme_states);
  Panel::Declare::Begin();
  Panel::Declare::Area(Rect(50, 50, 150, 150));


  auto changePress = []() { // belongs in panel
    if (s.current_panel_data == nullptr)
      return;

    if (Panel::Contains(IO::ind.mouse_position_.x, IO::ind.mouse_position_.y)) {
      s.current_panel_data->is_hovered_ = true;
      if (IO::ind.mouse_pressed_) {
        s.current_panel_data->is_held_ = true;
      } else {
        s.current_panel_data->is_held_ = false;
      }
    } else {
      s.current_panel_data->is_hovered_ = false;
    }

    if (s.current_panel_data->is_held_) {
      s.abs_rect->x += IO::ind.mouse_move_delta_.x;
      s.abs_rect->y += IO::ind.mouse_move_delta_.y;
    }
  };

  IO::Declare::OnMouseMove(changePress);
  Panel::Declare::Draw();
  {
    Button::Declare::SetTheme(theme_states);
    Button::Declare::Begin();
    Button::Declare::Area(Rect(5, 5, 25, 25));
    auto changeButtonPress = []() { // belongs in panel
      if (s.current_panel_data == nullptr)
        return;

      lgr::emit() << "here: " << IO::ind.mouse_position_.x << " " << IO::ind.mouse_position_.y;
      lgr::emit() << "pos: " << s.abs_rect->x << " " << s.abs_rect->y;
      if (Button::Contains(IO::ind.mouse_position_.x,
                          IO::ind.mouse_position_.y)) {
        lgr::emit() << "here2";
        s.current_panel_data->is_hovered_ = true;
        if (IO::ind.mouse_pressed_) {
          s.current_panel_data->is_held_ = true;
        } else {
          s.current_panel_data->is_held_ = false;
        }
      } else {
        s.current_panel_data->is_hovered_ = false;
      }
    };
    IO::Declare::OnMouseMove(changeButtonPress);
    Button::Declare::Draw();
    Button::Declare::End();
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
  renderer.RenderTextf(0, 300, 300, "mouse x: %f    mouse y: %f", omega::IO::ind.mouse_move_delta_.x, omega::IO::ind.mouse_move_delta_.y);
  if (s.current_panel_data != nullptr)
  renderer.RenderTextf(0, 300, 325, "hovered: %d", omega::s.current_panel_data->is_hovered_);
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
