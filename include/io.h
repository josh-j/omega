#pragma once
#define KEYUP true
#define KEYDOWN false

#include "common.h"
#include "point.h"
#include <functional>

namespace omega {
namespace IO {

enum ExtendedKeys { // Everything else is expected to be mapped to its default position, a == 0x61 ..ect
  EK_NONE = 0,
  EK_ESC = 0xFFFF + 1, // start above 2 bytes
  EK_F1,
  EK_F2,
  EK_F3,
  EK_F4,
  EK_F5,
  EK_F6,
  EK_F7,
  EK_F8,
  EK_F9,
  EK_F10,
  EK_F11,
  EK_F12,
  EK_PRINT,
  EK_SCROLL,
  EK_PAUSE,

  EK_BACKSPACE,
  EK_INSERT,
  EK_HOME,
  EK_PAGEUP,
  EK_NUMLOCK,

  EK_TAB,
  EK_DELETE,
  EK_END,
  EK_PAGEDOWN,

  EK_CAPSLOCK,
  EK_ENTER,

  EK_LSHIFT,
  EK_RSHIFT,

  EK_LCTRL,
  EK_LSPECIAL,
  EK_LALT,
  EK_RALT,
  EK_RSPECIAL,
  EK_LCONTEXT,
  EK_RCONTEXT,
  EK_RCTRL,
  EK_LEFT,
  EK_DOWN,
  EK_RIGHT,
  EK_UP,
  EK_MOUSE1,
  EK_MOUSE2,
  EK_MOUSE3,
  EK_MOUSE4,
  EK_MOUSE5

};

enum InputModifier {
  IMOD_NONE = 0,
  IMOD_SCROLLLOCK,
  IMOD_NUMLOCK,
  IMOD_CAPSLOCK,
  IMOD_SHIFT,
  IMOD_CTRL,
  IMOD_ALT,
};

enum MouseButton {
  MBTN_NONE,
  MBTN_LEFT,
  MBTN_MIDDLE,
  MBTN_RIGHT,
  MBTN_WHEEL
};

struct IOData;
const IOData& Context();
void KeyPress(uint key);
void KeyRelease(uint key);
void SetInputModifier(InputModifier modifier, bool activated);
void MouseMove(float x, float y);
void MousePress(MouseButton button);
void MouseRelease(MouseButton button);
void MouseWheelDelta(uint offset_delta);
void EndFrame();
void GLUT_MousePress();

// Helpers

const Point& mouse_position();
const Point& mouse_delta();
bool is_mouse_pressed();


namespace Declare {
void OnMousePress(std::function<void()> callback);
void OnMouseMove(std::function<void()> callback);
} // namespace Declare

} // namespace IO
} // namespace omega
