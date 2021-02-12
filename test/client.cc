#include <iostream>
#include <vector>

#include "client.h"
#include "brush.h"
#include "renderer_ogl.h"
#include "state.h"
#include "window.h"


namespace {
char work_path[256];
omega_test::RendererOGL renderer;
// system ui(&renderer); // glrenderer()
// logviewer* logviewer = new logviewer;
} // namespace

void CL_Initialize() {
  omega::s.renderer = &renderer;
  lgr::Sink_Ofstream::Init("omega_log.txt", false, false);
  lgr::emit() << "Init";

}

void CL_Draw() {
  using namespace omega;
  Window::SetShape(
      50, 50, 150, 150,
      Color(192, 128, 128, 192)); // this isn't always going to be here
  Window::Draw();
  {
    Window::SetShape(50, 50, 75, 75,
                     Color(192, 128, 128, 192)); // needs to be relative to prev
    Window::Draw();
  }

  /*
  **
  ** OnPress could set a flag is_moving = true, could call a callback for a button, could say highlight this text
  **
  ** Shape& shape = Panel::Declare::Shape(50,50,150,150,Color(kColorWhite));
  ** //IO::OnMouseMove(Panel::mover(shape)); // mover has to take ref shape
  ** IO::WhenMouseInShape(shape, IO::OnMousePress(Panel::onPress())); // there's a million things you might want to do after a mouse press - but it has its default behavior
  **
  **
       */
}

void CL_Shutdown() {}
