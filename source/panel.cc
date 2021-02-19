#include "panel.h"

#include <cassert>

#include "brush.h"
#include "state.h"
#include "common.h"
#include "rect.h"

namespace omega {
namespace Panel {

bool Contains(float xpos, float ypos) {
  return (xpos >= s.abs_rect->x && ypos >= s.abs_rect->y && xpos <= s.abs_rect->x + s.abs_rect->w && ypos <= s.abs_rect->y + s.abs_rect->h);
}

// bool Contains(const Point &point) {
//   return (point.x >= s.rect->x && point.y >= s.rect->y && point.x <= s.rect->x + s.rect->w && point.y <= s.rect->y + s.rect->h);
// }

Rect& Area(Rect& rect) {
  s.rect.set(rect);
  if (s.is_child) {
    s.rect.x += s.abs_rect->x;
    s.rect.y += s.abs_rect->y;
  }
  s.abs_rect = &rect;
  return *s.abs_rect;
}

auto SetColor(int r, int g, int b, int a) -> Color& {
  s.color.set(r, g, b, a);
  return s.color;
}

void Begin() {
  if (s.level > 0) {
    s.is_child = true;
  }
  ++s.level;
  ++s.current_id;
}

void End() {
  assert(s.level > 0);
  if (s.level == 1) {
    s.is_child = false;
  }
  --s.level;
}

void BeginChild() {}

void EndChild() {}


void Draw() {
  Brush::Rectangle(s.rect.pos(), s.rect.size(), s.color);
}

void SetShape(float x, float y, float w, float h, const Color &color) {
  s.abs_rect->set(x, y, w, h);
  s.color = color;
}

void MoveTo(float x, float y) {

}

void MoveAdjust(float x, float y) {
  s.abs_rect->x += x;
  s.abs_rect->y += y;
}

void Resize(float w, float h) {

}

void SetMinMaxSize(float w_min, float h_min, float w_max, float h_max) {

}

void OnMouseMove() {

}

void OnMousePress() {

}

void OnMouseSingleClick() {

}

void OnMouseDoubleClick() {

}

void OnMouseWheel() {

}

namespace Declare {

// Shape makeShape(float x, float y, float w, float h, const Color& color) {

// }

// Shape moveShape(Shape& shape, float x, float y) {
// }

void SetVisible(bool visible) {

}

void Begin() {
  dm.add(omega::Panel::Begin);
}

void End() {
  dm.add(omega::Panel::End);
}

Rect& Area(Rect rect) {
  dm.add(omega::Panel::Area, rect);
  return omega::Panel::Area(rect);
}

pre::Color& Color(int r, int g, int b, int a) {
  dm.add(omega::Panel::SetColor, r, g, b, a);
  return omega::Panel::SetColor(r, g, b, a);
}

void Draw() {
  dm.add(omega::Panel::Draw);
}

bool Contains(float xpos, float ypos) {
  dm.add(omega::Panel::Contains, xpos, ypos);
  return s.abs_rect->contains(xpos, ypos);
}

// bool Contains(const Point& point) {
//   dm.add<bool(const Point&)>(Panel::Contains, point);
//   return s.rect->contains(point);
// }

} // namespace Declare


} // namespace Panel
} // namespace omega
