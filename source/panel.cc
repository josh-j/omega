#include "panel.h"

#include <cassert>

#include "brush.h"
#include "state.h"
#include "common.h"
#include "rect.h"
#include "theme.h"

namespace omega {
namespace Panel {

bool Contains(float xpos, float ypos) {

  //if (s.is_child)
  //return (xpos >= s.abs_rect->x && ypos >= s.abs_rect->y && xpos <= s.abs_rect->x + s.abs_rect->w && ypos <= s.abs_rect->y + s.abs_rect->h);

    return (xpos >= s.rect.x && ypos >= s.rect.y && xpos <= s.rect.x + s.rect.w && ypos <= s.rect.y + s.rect.h);
}

// bool Contains(const Point &point) {
//   return (point.x >= s.rect->x && point.y >= s.rect->y && point.x <= s.rect->x + s.rect->w && point.y <= s.rect->y + s.rect->h);
// }

Rect& Area(Rect& rect) {
  s.rect.set(rect);

  // TODO abs rect should be declared_rect and rect should be drawn_rect

  float xdiff = 0.0f;
  float ydiff = 0.0f;

  if (s.is_child) {
    xdiff = s.abs_rect->x;
    ydiff = s.abs_rect->y;
  }
  s.abs_rect = &rect; // TODO fix needing a pointer
  s.rect.x += xdiff;
  s.rect.y += ydiff;
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

  s.current_panel_data = &s.panel_data[s.current_id];

  s.current_panel_data->is_hovered_ = true;
  //lgr::emit() << "level: " << s.level << "\n" << "current_id: " << s.current_id << "\n";

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

  // s.brush.Rectangle(s.rect.pos(), s.rect.size(), s.theme->themes[kStateNormal].color_background);
  s.UpdateTheme();
  s.theme->Panel(s.brush, s.rect);


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

void SetTheme(ThemeStates& theme) {
  s.theme_states = &theme;
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
  return omega::Panel::SetColor(r, g, b, a); // TODO this is wrong
}

void Draw() {
  dm.add(omega::Panel::Draw);
}

struct test {
  static void ok() {
    //dm.add_method(this, &test::ok);
    dm.add(&test::ok);
  }
};

bool Contains(float xpos, float ypos) {
  dm.add(omega::Panel::Contains, xpos, ypos);
  test t;
  return s.abs_rect->contains(xpos, ypos);
}

void SetTheme(ThemeStates& theme) {
  dm.add(omega::Panel::SetTheme, theme);
}
// bool Contains(const Point& point) {
//   dm.add<bool(const Point&)>(Panel::Contains, point);
//   return s.rect->contains(point);
// }

} // namespace Declare


} // namespace Panel
} // namespace omega
