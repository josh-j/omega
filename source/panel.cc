#include "panel.h"

#include <assert.h>

#include "state.h"

namespace omega {
namespace Panel {
namespace Declare {
Shape makeShape(float x, float y, float w, float h, const Color& color) {

}

void moveAdjust(float x, float y) {
}
} // namespace Declare

void Begin() { ++s.level; }

void End() {
  assert(s.level > 0);
  --s.level;
}

void BeginChild() {}

void EndChild() {}


void Draw() {
  Brush::Rectangle(s.rect.pos(), s.rect.size(), s.color);
}

void SetShape(float x, float y, float w, float h, const Color &color) {
  s.rect.set(x, y, w, h);
  s.color = color;
}

void MoveTo(float x, float y) {

}

void MoveAdjust(float x, float y) {
  s.rect.x += x;
  s.rect.y += y;
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


} // namespace Panel
} // namespace omega
