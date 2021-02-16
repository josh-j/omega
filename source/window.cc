#include "window.h"
#include "state.h"
#include "brush.h"
#include "color.h"

namespace omega {
namespace Window {

void Begin() {}

void SetShape(float x, float y, float w, float h, const Color& color) {
  s.abs_rect->set(x,y,w,h);
  s.color = color;
}

void Draw() {
  Brush::Rectangle(s.abs_rect->pos(), s.abs_rect->size(), s.color);
}

void End() {}

}  // namespace Window
} // namespace Omega
