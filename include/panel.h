#pragma once

#include "gui.h"
#include "common.h"
#include "brush.h"
#include "rect.h"
#include "forward_declarations.h"

// What does this do?
// It declares the entry of a new gui "object" or tree structure
namespace omega {


namespace Panel {
/* We need to start small: we first build a simple "View" where we have a rectangle capable of being moved, resized, colored
** and capable of holding "children."
**
*/

using namespace omega::GUI;
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
      : is_initialized(false), is_managed(true), is_enabled(true),
        is_visible(true), is_held(false), is_hovered(false),
        is_selected(false), is_focused(false), is_typing_in(false),
        is_maximized(false), is_minimized(false), is_moving(false),
        is_resizing(false), is_always_ontop(false),
        is_persistent_order(false), is_selection_allowed(true),
        is_input_passed_through(false), is_capturing_input(true),
        is_using_relative_x(false), is_using_relative_y(false),
        is_using_relative_w(false), is_using_relative_h(false),
        is_using_scaled_x(false), is_using_scaled_y(false),
        is_using_scaled_w(false), is_using_scaled_h(false),
        is_move_left_locked(false), is_move_right_locked(false),
        is_move_up_locked(false), is_move_down_locked(false),
        is_resize_left_locked(false), is_resize_right_locked(false),
        is_resize_top_locked(false), is_resize_bottom_locked(false),
        is_size_synced(false) {}

  Rect drawn_rect{0.0f, 0.0f, 0.0f, 0.0f};
  Rect* decl_rect{nullptr};
  Size   min_size{10.0f, 10.0f};
  Size   max_size{500.0f, 500.0f};

  bfbool is_initialized : 1;
  bfbool is_managed : 1; // panel manager automatically deletes and creates
  bfbool is_enabled : 1; // when disabled takes no input and draws or outputs
                          // nothing
  bfbool is_visible : 1; // takes inputs but draws nothing
  bfbool is_held : 1;
  bfbool is_hovered : 1;
  bfbool is_selected : 1;
  bfbool is_focused : 1;
  bfbool is_typing_in : 1;
  bfbool is_maximized : 1;
  bfbool is_minimized : 1;
  bfbool is_moving : 1;
  bfbool is_resizing : 1;
  bfbool is_always_ontop : 1;
  bfbool is_persistent_order : 1;
  bfbool is_selection_allowed : 1;
  bfbool is_input_passed_through : 1; // none of the input given to this panel
                                       // is handled by it; instead it's passed
                                       // through to its children
  bfbool is_capturing_input : 1;      // like is_enabled_ but still drawing
  bfbool is_using_relative_x : 1;
  bfbool is_using_relative_y : 1;
  bfbool is_using_relative_w : 1;
  bfbool is_using_relative_h : 1;
  bfbool is_using_scaled_x : 1;
  bfbool is_using_scaled_y : 1;
  bfbool is_using_scaled_w : 1;
  bfbool is_using_scaled_h : 1;
  bfbool is_move_left_locked : 1;
  bfbool is_move_right_locked : 1;
  bfbool is_move_up_locked : 1;
  bfbool is_move_down_locked : 1;
  bfbool is_resize_left_locked : 1;
  bfbool is_resize_right_locked : 1;
  bfbool is_resize_top_locked : 1;
  bfbool is_resize_bottom_locked : 1;
  bfbool is_size_synced : 1;




  // HMM -- this belongs in WindowData
  bool is_mouseover_left{false};
  bool is_mouseover_right{false};
  bool is_mouseover_top{false};
  bool is_mouseover_bottom{false};
};

/******************************************************************************/
/*                                 FUNCS                                      */
/******************************************************************************/
void Draw();
void OnMouseMove();
Rect& Area(Rect& rect);
void SetMinimumSize(float min_w, float min_h);


namespace Declare {
void SetVisible(bool is_visible);
void Begin();
void End();
void Draw();
Rect& Area(Rect rect);
void SetTheme(ThemeStates& themes);

} // namespace Declare

}  // namespace Panel
}  // namespace omega
