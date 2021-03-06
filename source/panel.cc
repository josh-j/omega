#include "panel.h"

#include <cassert>

#include "brush.h"
#include "gui.h"
#include "common.h"
#include "rect.h"
#include "theme.h"
#include "io.h" // TODO remove

namespace omega {
namespace Panel {

void Draw() {
  if (GUI::current_panel_data()->is_visible)
    GUI::Draw();
}

Rect& Area(Rect& rect) {

  // Rect& drawn_rect = GUI::drawn_rect();
  // Rect& decl_rect = GUI::delc_rect();

  // drawn_rect.set(rect);
  // // TODO abs rect should be declared_rect and rect should be drawn_rect

  // float xdiff = 0.0f;
  // float ydiff = 0.0f;

  // if (GUI::is_current_child()) {
  //   xdiff = delc_rect().x;
  //   ydiff = delc_rect().y;
  // }
  // GUI::update_delc_rect(rect);   // TODO fix needing a pointer
  // //delc_rect = &rect; // TODO fix needing a pointer
  // drawn_rect.x += xdiff;
  // drawn_rect.y += ydiff;
  return rect;
}

Rect& Area2(Rect &rect, PanelData* ctx) {
  // if (!ctx.drawn_rect.empty())
    // return rect;
  if (ctx->decl_rect != nullptr)
  lgr::emit() << "Decl: " << ctx->decl_rect->print() << " ptr: " << ctx->decl_rect;
  lgr::emit() << "Hmm: " << rect.print();
  ctx->drawn_rect.set(rect); // make drawn_rect the same as decl_rect
  ctx->decl_rect = &rect;

  float xdiff = 0.0f;
  float ydiff = 0.0f;

  if (ctx->is_child) {
    xdiff = ctx->parent->decl_rect->x;
    ydiff = ctx->parent->decl_rect->y;
  }

  ctx->drawn_rect.x += xdiff;
  ctx->drawn_rect.y += ydiff;

  return rect;
}

CursorType get_cursor() {
  PanelData &cpd = *GUI::current_panel_data();
  if ((cpd.is_mouseover_left && cpd.is_mouseover_top) ||
      (cpd.is_mouseover_bottom && cpd.is_mouseover_right)) {
    return kCursorNorthWest;
  } else if ((cpd.is_mouseover_top && cpd.is_mouseover_right) ||
             (cpd.is_mouseover_bottom && cpd.is_mouseover_left)) {
    return kCursorNorthEast;
  } else if (cpd.is_mouseover_left || cpd.is_mouseover_right) {
    return kCursorEast;
  } else if (cpd.is_mouseover_top || cpd.is_mouseover_bottom) {
    return kCursorNorth;
  } else if (cpd.is_mouseover_top || cpd.is_moving) { // TODO fix
    return kCursorMove;
  }
  return kCursorArrow;
}

void do_move(float x, float y) {
  PanelData& ctx = GUI::PanelMutableContext();
  if ((x > GUI::drawn_rect().x && !ctx.is_move_right_locked) ||
      !ctx.is_move_left_locked)
  {
   ctx.decl_rect->x = x;
  }
  if ((y > GUI::drawn_rect().y && !ctx.is_move_down_locked) ||
      !ctx.is_move_up_locked)
  {
    ctx.decl_rect->y = y;
  }
}

void do_resize() {
  const Point& pos = IO::mouse_position();
  float padding = 10.0f; //GUI::current_theme()->outer_padding;
  PanelData& cpd = *GUI::current_panel_data();

  if (cpd.is_held) {
    Rect new_rect = GUI::drawn_rect();
    cpd.is_resizing = false;
    float temp = GUI::drawn_rect().w + (GUI::drawn_rect().x - pos.x);
    if (cpd.is_mouseover_left
      && ((pos.x < GUI::drawn_rect().x && (temp < cpd.max_size.w || cpd.max_size.w <= 0.0f)) // moving left
      || (pos.x > GUI::drawn_rect().x && temp > cpd.min_size.w))) { // moving right
      new_rect.w = temp;
      new_rect.x = pos.x;
      cpd.is_resizing = true;
    }

    temp = GUI::drawn_rect().h + (GUI::drawn_rect().y - pos.y);
    if (cpd.is_mouseover_top
      && ((pos.y < GUI::drawn_rect().y && (temp < cpd.max_size.h || cpd.max_size.h <= 0.0f)) // moving up
      || (pos.y > GUI::drawn_rect().y && temp > cpd.min_size.h))) { // moving down
        new_rect.h = temp;
        new_rect.y = pos.y;
        cpd.is_resizing = true;
    }

    temp = pos.x - GUI::drawn_rect().x;
    if (cpd.is_mouseover_right
      && ((pos.x > GUI::drawn_rect().rightpos() && (temp < cpd.max_size.w || cpd.max_size.w <= 0.0f)) // moving right
      || (pos.x < GUI::drawn_rect().rightpos() && temp > cpd.min_size.w))) { // moving left
        new_rect.w = temp;
        cpd.is_resizing = true;
    }

    temp = pos.y - GUI::drawn_rect().y;
    if (cpd.is_mouseover_bottom && ((pos.y > GUI::drawn_rect().bottompos() && (temp < cpd.max_size.h || cpd.max_size.h <= 0.0f)) // moving down
      || (pos.y < GUI::drawn_rect().bottompos() && temp > cpd.min_size.h))) { // moving up
      new_rect.h = temp;
      cpd.is_resizing = true;
    }

    if (cpd.is_resizing) {
      // MoveTo(new_rect.pos());
      // Resize(new_rect.size());
      do_move(new_rect.pos().x, new_rect.pos().y);

      //Resize
      Size old_size = GUI::drawn_rect().size();
      float width = new_rect.w;
      float height = new_rect.h;
      if ((width > GUI::drawn_rect().w && !cpd.is_resize_right_locked) ||
          !cpd.is_resize_left_locked)
        GUI::delc_rect().w =
            pre::MinMaxIgnore(width, cpd.min_size.w, cpd.max_size.w, -1.0f);
      if ((height > GUI::drawn_rect().h && !cpd.is_resize_bottom_locked) ||
          !cpd.is_resize_top_locked)
        GUI::delc_rect().h =
            pre::MinMaxIgnore(height, cpd.min_size.h, cpd.max_size.h, -1.0f);
    }
  } else {
    cpd.is_mouseover_left = !cpd.is_resize_left_locked && pos.x <= GUI::drawn_rect().x + padding ? true : false;
    cpd.is_mouseover_top = !cpd.is_resize_top_locked && pos.y <= GUI::drawn_rect().y + padding ? true : false;
    cpd.is_mouseover_right = !cpd.is_resize_right_locked && pos.x >= GUI::drawn_rect().rightpos() - padding ? true : false;
    cpd.is_mouseover_bottom = !cpd.is_resize_bottom_locked && pos.y >= GUI::drawn_rect().bottompos() - padding ? true : false;
  }

  //OnMoveOrResize();
  //if (!cpd.is_resizing)
  //  Panel::OnMouseMove(data);
}

// TODO pass cpd and io?
void OnMouseMove() {
  PanelData& ctx = GUI::PanelMutableContext();

  if (ctx.drawn_rect.contains(IO::mouse_position())) {
    ctx.is_hovered = true;
    if (IO::is_mouse_pressed()) {
      ctx.is_held = true;
    } else {
      ctx.is_held = false;
    }
  } else {
    ctx.is_hovered = false;
  }

  do_resize();
  if (!ctx.is_resizing && ctx.is_held) {
    if ((IO::mouse_position().y > ctx.drawn_rect.y) &&
        (IO::mouse_position().y < (ctx.drawn_rect.y + 25.0f))) {
      ctx.is_moving = true;
      GUI::set_cursor(kCursorMove);
    }
    if (ctx.is_moving) {
      do_move(ctx.drawn_rect.x + IO::mouse_delta().x, ctx.drawn_rect.y + IO::mouse_delta().y);
      GUI::set_cursor(kCursorMove);
    }
  } else {
    ctx.is_moving = false;
  }

  GUI::set_cursor(get_cursor());

  // if (cpd.is_held) {
  //   float far_right = GUI::drawn_rect().rightpos();
  //   if ((IO::mouse_position().y > GUI::drawn_rect().y) && (IO::mouse_position().y < (GUI::drawn_rect().y + 15.0f))) {
  //     cpd.is_moving = true;
  //     GUI::set_cursor(kCursorMove);
  //   } else if (IO::mouse_position().x < far_right && IO::mouse_position().x > (far_right - 15.0f)) {
  //     cpd.is_resizing = true;
  //     GUI::set_cursor(kCursorEast);
  //   }
  //   if (cpd.is_moving) {
  //     GUI::delc_rect().x += IO::mouse_delta().x;
  //     GUI::delc_rect().y += IO::mouse_delta().y;
  //     GUI::set_cursor(kCursorMove);
  //   } else if (cpd.is_resizing) {
  //     GUI::set_cursor(kCursorWest);
  //   }
  // } else {
  //   GUI::set_cursor(kCursorArrow);
  //   cpd.is_moving = false;
  //   cpd.is_resizing = false;
  // }
}
void SetMinimumSize(float min_width, float min_height) {
  GUI::current_panel_data()->min_size.set(min_width, min_height);
}

namespace Declare {


void SetVisible(bool is_visible) {
  GUI::current_panel_data()->is_visible = is_visible;
}

// TODO this could be very bug prone
void Begin() {
  // Declarable::add(omega::Panel::Begin);
  dm.add(omega::Panel::Begin);
  omega::Panel::Begin();
}

void End() {
  dm.add(omega::Panel::End);
  omega::Panel::End();
}

Rect& Area(Rect rect) { // TODO Why save arguments when I can just put them in PanelData?
  //dm.add(omega::Panel::Area, rect);
  return omega::Panel::Area(rect);
}

Rect &Area2(Rect rect, PanelData* ctx) {
  dm.add(omega::Panel::Area2, rect, ctx);
  return omega::Panel::Area2(rect, ctx);
}

void Draw() {
  dm.add(omega::Panel::Draw);
  omega::Panel::Draw();
}

void SetTheme(ThemeStates& theme) {
  dm.add(omega::Panel::SetTheme, theme);
  omega::Panel::SetTheme(theme);
}

} // namespace Declare


} // namespace Panel
} // namespace omega
