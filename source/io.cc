#include "io.h"
#include "gui.h"

namespace omega {
namespace IO {

struct IOData {
  IOData() : key_(0), num_clicks_(0), mwheel_delta_(0), key_down_(false), scroll_lock_(false),
    num_lock_(false), caps_lock_(false), shift_(false), control_(false), alt_(false) {}
  ~IOData() = default;

  //void SubscribeTo_MousePress(DeclarativeManager& dm, std::function<void()> callback);

  Point mouse_position_{0.0f, 0.0f};
  Point mouse_move_delta_{0.0f, 0.0f};
  MouseButton mouse_button_;
  uint key_;
  uint num_clicks_;
  uint mwheel_delta_;
  bool key_down_;
  bool scroll_lock_;
  bool num_lock_;
  bool caps_lock_;
  bool shift_;
  bool control_;
  bool alt_;

  bool key_pressed_{false};
  bool key_released_{false};
  bool mouse_moved_{false};
  bool mouse_pressed_{false};
  bool mouse_released_{false};
};

IOData s;


void KeyPress(uint key) {
  s.key_ = key;
  //data_.num_clicks_ += 1;
  s.key_down_ = true;
  s.key_pressed_ = true;
  s.key_released_ = false;
}

void KeyRelease(uint key) {
  s.key_ = key;
  //if (data_.num_clicks_ > 0) data_.num_clicks_ -= 1;
  s.key_down_ = false;
  s.key_pressed_ = false;

}

void SetInputModifier(InputModifier modifier, bool activated) {
  switch (modifier) {
  case IMOD_SCROLLLOCK: s.scroll_lock_ = activated; break;
  case IMOD_NUMLOCK: s.num_lock_ = activated; break;
  case IMOD_CAPSLOCK: s.caps_lock_ = activated; break;
  case IMOD_SHIFT: s.shift_ = activated; break;
  case IMOD_CTRL: s.control_ = activated; break;
  case IMOD_ALT: s.alt_ = activated; break;
  case IMOD_NONE: break;
  }
}

void MouseMove(float x, float y) { // TODO(unknown): make float
  s.mouse_move_delta_.set(x - s.mouse_position_.x, y - s.mouse_position_.y);
  s.mouse_position_.set(x, y);
  //ind.mouse_moved_ = (ind.mouse_move_delta_.x < 1.0f && ind.mouse_move_delta_.y < 1.0f) ? false :true;
  s.mouse_moved_ = true;
}

void MousePress(MouseButton button) {
  s.num_clicks_ += 1;
  s.mouse_button_ = button;
  s.mouse_pressed_ = true;
  s.mouse_released_ = false;
}

void MouseRelease(MouseButton button) {
  if (s.num_clicks_ > 0) s.num_clicks_ -= 1;
  s.mouse_button_ = MBTN_NONE;
  s.mouse_pressed_ = false;
  s.mouse_released_ = true;
}

void MouseWheelDelta(uint offset_delta) { s.mwheel_delta_ += offset_delta; }

void EndFrame() {
  s.mouse_released_ = false;
  s.key_released_ = false;
  s.mouse_moved_ = false;
  s.mouse_move_delta_ = 0.0f;
}

void OnMousePress(std::function<void()> callback) {
  if (s.mouse_pressed_)
    callback();
}

void OnMouseMove(std::function<void()> callback) {
  // if (ind.mouse_moved_)
    callback();
}


const Point& mouse_position() {
  return s.mouse_position_;
}

const Point& mouse_delta() {
  return s.mouse_move_delta_;
}

bool is_mouse_pressed() {
  return s.mouse_pressed_;
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
