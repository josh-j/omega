#pragma once

#include "common.h"
#include "forward_declarations.h"

namespace omega {
enum CursorType {
  kCursorNone,
  kCursorArrow,
  kCursorIBeam,
  kCursorCrosshair,
  kCursorMove,
  kCursorNorthWest,
  kCursorNorth,
  kCursorNorthEast,
  kCursorEast,
  kCursorSouthEast,
  kCursorSouth,
  kCursorSouthWest,
  kCursorWest,
  kCursorError
};
void Text(hfont font, const Point& position, const Color& color,
          const std::string& text);
void Rectangle(const Point& pos, const Size& size, const Color& color);
void RoundedRect(const Point& pos, const Size& size, const Color& color,
                 float radius = 8.0);
void Border(const Point& pos, const Size& size, const Color& color,
            float border_width = 1.0);
void Border(const Point& pos, const Size& size, const Color& color,
            float border_width, float offset);
void RoundedBorder(const Point& pos, const Size& size, const Color& color,
                   float border_width = 1.0, float radius = 8.0);
void Bevel(const Point& pos, const Size& size, const Color& color,
           const Color& alt_color, float bevel_width = 1.0,
           float alt_bevel_width = 1.0, float offset = 0.0);
void RoundedBevel(const Point& pos, const Size& size, const Color& color,
                  const Color& alt_color, float bevel_width = 1.0,
                  float alt_bevel_width = 1.0, float offset = 0.0,
                  float radius = 8.0);

void PanelBackground(const Rect& rect, const Color& color_background,
                     float padding, bool is_rounded);
void PanelBackground(const Point& pos, const Size& size,
                     const Color& color_background, float padding,
                     bool is_rounded);
void PanelFrame(const Rect& rect, const Color& color_border,
                const Color& color_bevel, const Color& color_bevelalt,
                float border_size, float bevel_size, float bevelalt_size,
                float border_padding, bool is_rounded, bool is_bordered,
                bool is_beveled, bool is_bevel_outside, bool is_bevel_reversed);
void PanelFrame(const Point& pos, const Size& size, const Color& color_border,
                const Color& color_bevel, const Color& color_bevelalt,
                float border_size, float bevel_size, float bevelalt_size,
                float border_padding, bool is_rounded, bool is_bordered,
                bool is_beveled, bool is_bevel_outside, bool is_bevel_reversed);

void Image(const Point& point, const std::string& name);
void Cursor(const Point& point, CursorType cursor);
}  // namespace omega