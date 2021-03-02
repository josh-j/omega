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
  std::string line{""};
  std::vector<std::string> many_lines{};
  CursorType cursor_type{kCursorArrow};


  // > Transient State
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

void Begin() {
  if (s.level > 0) {
    s.is_child = true;
    if (s.parent_level < s.level + 1) {

    }
  }

  ++s.level;
  ++s.current_id;

  s.current_panel_data = &s.panel_data[s.current_id];

  // lgr::emit() << "level: " << s.level << "\n" << "current_id: " <<
  // s.current_id << "\n";
}


void End() { // TODO this belongs in state
  assert(s.level > 0);
  if (s.level == 1) {
    s.is_child = false;
  }
  --s.level;
}

void Draw() { // TODO this belongs in state????
  // s.brush.Rectangle(s.rect.pos(), s.rect.size(),
  // s.theme->themes[kStateNormal].color_background);
  UpdateTheme();
  s.theme->Panel(s.brush, s.rect);
  s.brush.Cursor(IO::mouse_position(), s.cursor_type);

}

void EndFrame() {
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
  return *s.abs_rect;
}
Rect& drawn_rect() {
  return s.rect;
}

void update_delc_rect(Rect& rect) {
  s.abs_rect = &rect;
}

bool is_current_child() {
  return s.is_child;
}

void set_cursor(CursorType cursor_type) {
  s.cursor_type = cursor_type;
}

} // namespace GUI
} // namespace omega
