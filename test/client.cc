

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
}

void CL_Shutdown() {}
