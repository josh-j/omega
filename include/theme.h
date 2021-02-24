#pragma once

#include "common.h"
#include "font.h"
#include "forward_declarations.h"

namespace omega {

struct Theme {
  Theme()
      : color_background(45, 45, 48, 200), color_foreground(200, 200, 200, 255),
        color_border(32, 32, 32, 164), color_bevel(128, 128, 128, 110),
        color_bevelalt(64, 64, 64, 110), font(nullptr), font_face("tahoma"),
        font_height(8), font_weight(500), inner_padding(6.0f),
        outer_padding(8.0f), border_size(1.0f), bevel_size(1.0f),
        bevelalt_size(1.0f), font_horizontal_align(Font::kHorzAlignCenter),
        font_verticle_align(Font::kVertAlignMiddle), is_rounded(false),
        is_bordered(true), is_beveled(true), is_bevel_outside(true),
        is_bevel_reversed(true), is_background_drawn(true), is_top_padded(true),
        is_right_padded(true), is_bottom_padded(true), is_left_padded(true),
        is_defined(false) {}

  void Panel(Brush& brush, const Rect& rect);
  void PanelBackground(Brush& brush, const Rect& rect);
  void PanelBackground(Brush& brush, const Point& pos, const Size& size);
  void PanelFrame(Brush& brush, const Rect& rect);
  void PanelFrame(Brush& brush, const Point& pos, const Size& size);
  void Text(const Point& position, const std::string& text);
  void Text(const Rect& rect, const std::string& text);
  void Text(const Rect& rect, Font::HorizontalAlign halign, Font::VerticleAlign valign, const std::string& text);
  void Text(const Rect& rect, const Point& offset_text, const std::string& text);
  void Text(const Rect& rect, const Point& offset_text, Font::HorizontalAlign halign, Font::VerticleAlign valign, const std::string& text);

  Color color_background;
  Color color_foreground;
  Color color_border;
  Color color_bevel;
  Color color_bevelalt;
  Font *font;
  std::string font_face;
  uint font_height;
  uint font_weight;
  float inner_padding;
  float outer_padding;
  float border_size;
  float bevel_size;
  float bevelalt_size;
  Font::HorizontalAlign font_horizontal_align;
  Font::VerticleAlign font_verticle_align;
  bfbool is_rounded : 1;
  bfbool is_rounded_ne : 1;
  bfbool is_rounded_nw : 1;
  bfbool is_rounded_sw : 1;
  bfbool is_rounded_se : 1;
  bfbool is_bordered : 1;
  bfbool is_beveled : 1;
  bfbool is_bevel_outside : 1;
  bfbool is_bevel_reversed : 1;
  bfbool is_background_drawn : 1;
  bfbool is_top_padded : 1;
  bfbool is_right_padded : 1;
  bfbool is_bottom_padded : 1;
  bfbool is_left_padded : 1;
  bfbool is_defined : 1;
};

struct ThemeStates {
  //constexpr static char *const kStateNames[4] = { "normal", "hovered", "selected", "held" };

  enum PanelStates {
    kStateNormal = 0,
    kStateHovered,
    kStateSelected,
    kStateFocused,
    kStateHeld,
    kStateNum
  };

  Theme themes[5];
};

} // namespace omega
