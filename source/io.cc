#include "io.h"
#include "gui.h"

namespace omega {
namespace IO {

struct IOData {
  IOData() : key(0), num_clicks(0), mwheel_delta(0), key_down(false), scroll_lock(false),
    num_lock(false), caps_lock(false), shift(false), control(false), alt(false) {}
  ~IOData() = default;

  //void SubscribeTo_MousePress(DeclarativeManager& dm, std::function<void()> callback);

  Point mouse_position{0.0f, 0.0f};
  Point mouse_move_delta{0.0f, 0.0f};
  MouseButton mouse_button;
  uint key;
  uint num_clicks;
  uint mwheel_delta;
  bool key_down;
  bool scroll_lock;
  bool num_lock;
  bool caps_lock;
  bool shift;
  bool control;
  bool alt;

  bool key_pressed{false};
  bool key_released{false};
  bool mouse_moved{false};
  bool mouse_pressed{false};
  bool mouse_released{false};
};

IOData s;


const IOData& Context() {
  return s;
}

void KeyPress(uint key) {
  s.key = key;
  //data_.num_clicks_ += 1;
  s.key_down = true;
  s.key_pressed = true;
  s.key_released = false;
}

void KeyRelease(uint key) {
  s.key = key;
  //if (data_.num_clicks_ > 0) data_.num_clicks_ -= 1;
  s.key_down = false;
  s.key_pressed = false;

}

void SetInputModifier(InputModifier modifier, bool activated) {
  switch (modifier) {
  case IMOD_SCROLLLOCK: s.scroll_lock = activated; break;
  case IMOD_NUMLOCK: s.num_lock = activated; break;
  case IMOD_CAPSLOCK: s.caps_lock = activated; break;
  case IMOD_SHIFT: s.shift = activated; break;
  case IMOD_CTRL: s.control = activated; break;
  case IMOD_ALT: s.alt = activated; break;
  case IMOD_NONE: break;
  }
}

void MouseMove(float x, float y) { // TODO(unknown): make float
  s.mouse_move_delta.set(x - s.mouse_position.x, y - s.mouse_position.y);
  s.mouse_position.set(x, y);
  //ind.mouse_moved_ = (ind.mouse_move_delta_.x < 1.0f && ind.mouse_move_delta_.y < 1.0f) ? false :true;
  s.mouse_moved = true;
}

void MousePress(MouseButton button) {
  s.num_clicks += 1;
  s.mouse_button = button;
  s.mouse_pressed = true;
  s.mouse_released = false;
}

void MouseRelease(MouseButton button) {
  if (s.num_clicks > 0) s.num_clicks -= 1;
  s.mouse_button = MBTN_NONE;
  s.mouse_pressed = false;
  s.mouse_released = true;
}

void MouseWheelDelta(uint offset_delta) { s.mwheel_delta += offset_delta; }

void EndFrame() {
  s.mouse_released = false;
  s.key_released = false;
  s.mouse_moved = false;
  s.mouse_move_delta = 0.0f;
}

void OnMousePress(std::function<void()> callback) {
  if (s.mouse_pressed)
    callback();
}

void OnMouseMove(std::function<void()> callback) {
  // if (ind.mouse_moved_)
    callback();
}


const Point& mouse_position() {
  return s.mouse_position;
}

const Point& mouse_delta() {
  return s.mouse_move_delta;
}

bool is_mouse_pressed() {
  return s.mouse_pressed;
}

namespace Declare {
void OnMousePress(std::function<void()> callback) {
  omega::GUI::dm.add(IO::OnMousePress, callback);
  IO::OnMousePress(callback);
}

void OnMouseMove(std::function<void()> callback) {
  omega::GUI::dm.add(IO::OnMouseMove, callback);
  IO::OnMouseMove(callback);
}

} // Declare

} // namespace IO
} // namespace omega
