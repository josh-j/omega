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
#include "gui.h"

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
  theme_states.themes[Panel::kStateNormal].is_bordered = true;
  theme_states.themes[Panel::kStateNormal].is_beveled = false;
  theme_states.themes[Panel::kStateNormal].color_border.set(64, 64, 64, 255);


  theme_states.themes[Panel::kStateHovered].color_border.set(0, 122, 204, 92);
  theme_states.themes[Panel::kStateHeld].color_border.set(0, 122, 204, 255);

  theme_states.themes[Panel::kStateFocused].color_background.set(92, 92, 92, 255);

  omega::GUI::set_renderer(renderer);
  lgr::Sink_Ofstream::Init("omega_log.txt", false, false);
  lgr::emit() << "Init";
  renderer.BuildFont("iosevka-regular.ttf", 14, 0, 0, nullptr);


  Panel::Declare::Begin();
  Panel::PanelData& ctx = GUI::PanelMutableContext();
  Panel::Declare::SetTheme(theme_states);
  //Panel::Declare::SetVisible(false);
  Panel::Declare::Area2(Rect(50, 50, 150, 150), &ctx);
  Panel::SetMinimumSize(50.0f, 50.0f);

  IO::Declare::OnMouseMove(Panel::OnMouseMove);
  Panel::Declare::Draw();
  {
    /*
    // RAII
    Button btn(state, io, theme, ect);
    btn.area(Rect(5,5,25,25));
    btn.OnMouseMove(changeButtonPress);
    btn.draw();

    // General wrapper for all functions to be added as declaration
    make_decl(Button::SetTheme, theme_states);
    make_decl(Button::Begin);
    make_decl(Button::Area, Rect(5,5,5,25));
     */

    Button::Declare::Begin();
    Panel::PanelData& ctx = GUI::PanelMutableContext();
    Button::Declare::SetTheme(theme_states);
    Button::Declare::Area2(Rect(25, 25, 25, 25), &ctx);

    IO::Declare::OnMouseMove(Button::OnMouseMove);
    Button::Declare::Draw();
    Button::Declare::End();
  }
  Panel::Declare::End();
}

void CL_Draw() {
  omega::GUI::dm.execute();
  IO::EndFrame();
  omega::GUI::EndFrame();

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
