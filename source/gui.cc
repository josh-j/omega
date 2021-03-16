#include "gui.h"
#include "theme.h"
#include "panel.h"
#include "io.h"

namespace omega {
namespace GUI {
DeclarativeManager dm;


struct State { // TODO this should be TypeState since its static, e.i. there is PanelInstanceState and PanelTypeState
  State(const State&) = delete;
  State& operator=(const State &) = delete;
  State(State &&) = delete;
  State & operator=(State &&) = delete;

  uint32_t level{0};
  uint32_t current_id{0};
  uint32_t parent_id{0};
  uint32_t parent_level{0};
  CursorType cursor_type{kCursorArrow};


  // > Transient State
  //bool is_pressed{false};
  //bool is_moving{false};
  Renderer* renderer{nullptr};
  ThemeStates* theme_states{nullptr};
  Theme* theme{nullptr};
  // <

  std::map <uint, Panel::PanelData> panel_data;
  Brush brush;
  Panel::PanelData* current_panel_data{nullptr};
  Panel::PanelData* parent_panel_data{nullptr};

  static auto& instance() {
    static State state;
    return state;
  }

 private:
  State() = default;
};

static State& s = State::instance();

const Panel::PanelData& PanelContext() {
  assert(s.current_panel_data != nullptr);
  return *s.current_panel_data;
}

Panel::PanelData& PanelMutableContext() {
  assert(s.current_panel_data != nullptr);
  return *s.current_panel_data;
}
/*
** Begin 0 null
**   Begin 1 0
**     Begin 2 1
**     End
**     Begin 3 1
**     End
**  End
** End
 */
void Begin() {
  s.current_panel_data = &s.panel_data[s.current_id];
  ++s.current_id;
  if (s.level > 0) {
    PanelMutableContext().is_child = true;
    PanelMutableContext().parent = &s.panel_data[s.parent_id];

  }
  if (s.level > 2) {
    ++s.parent_id;
  }

  ++s.level;

  // lgr::emit() << "level: " << s.level << "\n" << "current_id: " <<
  // s.current_id << "\n";
}


void End() { // TODO this belongs in state
  assert(s.level > 0);
  if (s.level > 2) {
    --s.parent_id;
  }
  --s.level;
}

void Draw() { // TODO this belongs in state????
  // s.brush.Rectangle(s.rect.pos(), s.rect.size(),
  // s.theme->themes[kStateNormal].color_background);
  Panel::PanelData& ctx = GUI::PanelMutableContext();
  UpdateTheme();

  // if (ctx.decl_rect != nullptr)
  //   lgr::emit() << ctx.decl_rect->print() << " ptr: " << ctx.decl_rect;
  s.theme->Panel(s.brush, ctx.drawn_rect);
  s.brush.Cursor(IO::mouse_position(), s.cursor_type);

}

void EndFrame() {
  s.parent_id = 0;
  s.current_id = 0;
  s.level = 0;
}

void SetTheme(ThemeStates& theme) { // TODO Belongs in state
  s.theme_states = &theme;
}

void UpdateTheme() {
  assert(s.current_panel_data != nullptr);

  const Panel::PanelData& cpd = *s.current_panel_data;

  // if (cpd.is_held_ && theme_states->themes[kStateHeld] != nullptr) {
  //   theme = theme_states->themes[kStateHeld];
  // } else if (cpd.is_hovered_ && theme_states->themes[kStateHovered] != nullptr) {
  //   theme = theme_states->themes[kStateHovered];
  // } else if (cpd.is_selected_ && theme_states->themes[kStateSelected] != nullptr) {
  //   theme = theme_states->themes[kStateSelected];
  // } else if (cpd.is_focused_ && theme_states->themes[kStateFocused] != nullptr) {
  //   theme = theme_states->themes[kStateFocused];
  // } else {
  //   theme = theme_states->themes[kStateNormal];
  // }
  //
  if (cpd.is_held) {
    s.theme = &s.theme_states->themes[Panel::kStateHeld];
  } else if (cpd.is_hovered) {
    s.theme = &s.theme_states->themes[Panel::kStateHovered];
  } else if (cpd.is_selected) {
    s.theme = &s.theme_states->themes[Panel::kStateSelected];
  } else if (cpd.is_focused) {
    s.theme = &s.theme_states->themes[Panel::kStateFocused];
  } else {
    s.theme = &s.theme_states->themes[Panel::kStateNormal];
  }
}

Panel::PanelData* current_panel_data() {
  return s.current_panel_data;
}

void set_renderer(Renderer& renderer) {
  s.renderer = &renderer;
  s.brush.set_renderer(&renderer); // TODO use ref
}
Rect& delc_rect() {
  return *PanelMutableContext().decl_rect;
}
Rect& drawn_rect() {
  return PanelMutableContext().drawn_rect;
}

bool is_current_child() {
  return PanelMutableContext().is_child;
}

void set_cursor(CursorType cursor_type) {
  s.cursor_type = cursor_type;
}

} // namespace GUI
} // namespace omega
