#pragma once
#include <string>
#include <map>
#include "common.h"
#include "rect.h"
#include "renderer.h"
#include "forward_declarations.h"
#include "declarative.h"
#include "brush.h"

namespace omega {

enum PanelStates {
  kStateNormal = 0,
  kStateHovered,
  kStateSelected,
  kStateFocused,
  kStateHeld,
  kStateNum
};

enum HorizontalAlign { kHorzAlignLeft, kHorzAlignCenter, kHorzAlignRight };

enum VerticleAlign { kVertAlignTop, kVertAlignMiddle, kVertAlignBottom };

enum RequestType { kRequestNone, kRequestInit, kRequestLoadFont };

struct PanelData {
  PanelData()
      : is_initialized_(false), is_managed_(true), is_enabled_(true),
        is_visible_(true), is_held_(false), is_hovered_(false),
        is_selected_(false), is_focused_(false), is_typing_in_(false),
        is_maximized_(false), is_minimized_(false), is_moving_(false),
        is_resizing_(false), is_always_ontop_(false),
        is_persistent_order_(false), is_selection_allowed_(true),
        is_input_passed_through_(false), is_capturing_input_(true),
        is_using_relative_x(false), is_using_relative_y(false),
        is_using_relative_w(false), is_using_relative_h(false),
        is_using_scaled_x(false), is_using_scaled_y(false),
        is_using_scaled_w(false), is_using_scaled_h(false),
        is_move_left_locked_(false), is_move_right_locked_(false),
        is_move_up_locked_(false), is_move_down_locked_(false),
        is_resize_left_locked_(false), is_resize_right_locked_(false),
        is_resize_top_locked_(false), is_resize_bottom_locked_(false),
        is_size_synced_(false) {}

  bfbool is_initialized_ : 1;
  bfbool is_managed_ : 1; // panel manager automatically deletes and creates
  bfbool is_enabled_ : 1; // when disabled takes no input and draws or outputs
                          // nothing
  bfbool is_visible_ : 1; // takes inputs but draws nothing
  bfbool is_held_ : 1;
  bfbool is_hovered_ : 1;
  bfbool is_selected_ : 1;
  bfbool is_focused_ : 1;
  bfbool is_typing_in_ : 1;
  bfbool is_maximized_ : 1;
  bfbool is_minimized_ : 1;
  bfbool is_moving_ : 1;
  bfbool is_resizing_ : 1;
  bfbool is_always_ontop_ : 1;
  bfbool is_persistent_order_ : 1;
  bfbool is_selection_allowed_ : 1;
  bfbool is_input_passed_through_ : 1; // none of the input given to this panel
                                       // is handled by it; instead it's passed
                                       // through to its children
  bfbool is_capturing_input_ : 1;      // like is_enabled_ but still drawing
  bfbool is_using_relative_x : 1;
  bfbool is_using_relative_y : 1;
  bfbool is_using_relative_w : 1;
  bfbool is_using_relative_h : 1;
  bfbool is_using_scaled_x : 1;
  bfbool is_using_scaled_y : 1;
  bfbool is_using_scaled_w : 1;
  bfbool is_using_scaled_h : 1;
  bfbool is_move_left_locked_ : 1;
  bfbool is_move_right_locked_ : 1;
  bfbool is_move_up_locked_ : 1;
  bfbool is_move_down_locked_ : 1;
  bfbool is_resize_left_locked_ : 1;
  bfbool is_resize_right_locked_ : 1;
  bfbool is_resize_top_locked_ : 1;
  bfbool is_resize_bottom_locked_ : 1;
  bfbool is_size_synced_ : 1;
};

struct State {
  void EndFrame() {
    current_id = 0;
    level = 0;
  }

  void UpdateTheme();

  uint32_t level{0};
  uint32_t current_id{0};
  std::string line{""};
  std::vector<std::string> many_lines{};

  Rect null_rect{0.0f, 0.0f, 0.0f, 0.0f};
  Rect* abs_rect{&null_rect};
  Rect rect{0.0f, 0.0f, 0.0f, 0.0f};
  Color color{255,255,255,255};
  bool is_child{false};
  bool is_pressed{false};
  bool is_moving{false};
  Renderer* renderer{nullptr};
  ThemeStates* theme_states{nullptr};
  Theme* theme{nullptr};

  std::map <uint, PanelData> panel_data;
  Brush brush;
  PanelData* current_panel_data{nullptr};
};

extern DeclarativeManager dm;
extern State s;
}  // namespace omega
