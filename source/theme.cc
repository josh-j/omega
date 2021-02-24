#include "theme.h"
#include "brush.h"
#include "rect.h"

namespace omega {

void Theme::Panel(Brush& brush, const Rect& rect) {
  PanelBackground(brush, rect.pos(), rect.size());
  PanelFrame(brush, rect.pos(), rect.size());
}

void Theme::PanelBackground(Brush& brush, const Rect& rect) {
  PanelBackground(brush, rect.pos(), rect.size());
}

void Theme::PanelBackground(Brush& brush, const Point& pos, const Size& size) {
  if (!is_background_drawn) return;
  if (is_rounded) {
    brush.RoundedRect(pos, size, color_background, outer_padding);
  } else {
    brush.Rectangle(pos, size, color_background);
  }
}

void Theme::PanelFrame(Brush& brush, const Rect& rect) {
  PanelFrame(brush, rect.pos(), rect.size());
}

void Theme::PanelFrame(Brush& brush, const Point& pos, const Size& size) {
  if (is_rounded) {
    if (is_beveled) {
      float offset = 0.0f;
      if (is_bordered)
        offset = is_bevel_outside ? -border_size : border_size;

      brush.RoundedBevel(pos, size,
        (is_bevel_reversed ? color_bevelalt : color_bevel),
        (is_bevel_reversed ? color_bevel : color_bevelalt),
        bevel_size, bevelalt_size, offset, outer_padding);
    }

    if (is_bordered) {
      brush.RoundedBorder(pos, size, color_border, border_size, outer_padding);
    }
  } else {
    if (is_beveled) {
      float offset = 0.0f;
      if (is_bordered)
        offset = is_bevel_outside ? 0.0f : border_size;

      brush.Bevel(pos, size,
        (is_bevel_reversed ? color_bevelalt : color_bevel),
        (is_bevel_reversed ? color_bevel : color_bevelalt),
        bevel_size, bevelalt_size, offset);
    }

    if (is_bordered) {
      float offset = 0.0f;
      if (is_beveled && is_bevel_outside)
        offset = bevelalt_size > bevel_size ? bevelalt_size : bevel_size;

      brush.Border(pos, size, color_border, border_size, offset);
    }
  }
}

} // namespace omega
