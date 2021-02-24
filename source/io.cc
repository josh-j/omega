#include "io.h"
#include "state.h"

namespace omega {
namespace IO {

InputData ind;


void KeyPress(uint key) {
  ind.key_ = key;
  //data_.num_clicks_ += 1;
  ind.key_down_ = true;
  ind.key_pressed_ = true;
  ind.key_released_ = false;
}

void KeyRelease(uint key) {
  ind.key_ = key;
  //if (data_.num_clicks_ > 0) data_.num_clicks_ -= 1;
  ind.key_down_ = false;
  ind.key_pressed_ = false;

}

void SetInputModifier(InputModifier modifier, bool activated) {
  switch (modifier) {
  case IMOD_SCROLLLOCK: ind.scroll_lock_ = activated; break;
  case IMOD_NUMLOCK: ind.num_lock_ = activated; break;
  case IMOD_CAPSLOCK: ind.caps_lock_ = activated; break;
  case IMOD_SHIFT: ind.shift_ = activated; break;
  case IMOD_CTRL: ind.control_ = activated; break;
  case IMOD_ALT: ind.alt_ = activated; break;
  case IMOD_NONE: break;
  }
}

void MouseMove(float x, float y) { // TODO(unknown): make float
  ind.mouse_move_delta_.set(x - ind.mouse_position_.x, y - ind.mouse_position_.y);
  ind.mouse_position_.set(x, y);
  //ind.mouse_moved_ = (ind.mouse_move_delta_.x < 1.0f && ind.mouse_move_delta_.y < 1.0f) ? false :true;
  ind.mouse_moved_ = true;
}

void MousePress(MouseButton button) {
  ind.num_clicks_ += 1;
  ind.mouse_button_ = button;
  ind.mouse_pressed_ = true;
  ind.mouse_released_ = false;
}

void MouseRelease(MouseButton button) {
  if (ind.num_clicks_ > 0) ind.num_clicks_ -= 1;
  ind.mouse_button_ = MBTN_NONE;
  ind.mouse_pressed_ = false;
  ind.mouse_released_ = true;
}

void MouseWheelDelta(uint offset_delta) { ind.mwheel_delta_ += offset_delta; }

void EndFrame() {
  ind.mouse_released_ = false;
  ind.key_released_ = false;
  ind.mouse_moved_ = false;
  ind.mouse_move_delta_ = 0.0f;
}

void OnMousePress(std::function<void()> callback) {
  if (ind.mouse_pressed_)
    callback();
}

void OnMouseMove(std::function<void()> callback) {
  // if (ind.mouse_moved_)
    callback();
}


namespace Declare {
void OnMousePress(std::function<void()> callback) {
  dm.add(IO::OnMousePress, callback);
  IO::OnMousePress(callback);
}

void OnMouseMove(std::function<void()> callback) {
  dm.add(IO::OnMouseMove, callback);
  IO::OnMouseMove(callback);
}

} // Declare

} // namespace IO
} // namespace omega
