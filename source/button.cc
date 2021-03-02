#include "button.h"
#include "gui.h"
#include "text.h"
#include "theme.h"
#include "io.h" // TODO remove

namespace omega::Button {
void Draw() {
  GUI::Draw();
}

void OnMouseMove() {
  if (GUI::current_panel_data() == nullptr)
    return;

  PanelData& cpd = *GUI::current_panel_data();

  if (GUI::drawn_rect().contains(IO::mouse_position())) {
    cpd.is_hovered = true;
    if (IO::is_mouse_pressed()) {
      cpd.is_held = true;
    } else {
      cpd.is_held = false;
    }
  } else {
    cpd.is_hovered = false;
  }

}

}  // namespace omega::Button
