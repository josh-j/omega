#include "state.h"
#include "theme.h"
namespace omega {
State s;
DeclarativeManager dm;

void State::UpdateTheme() {
  assert(current_panel_data != nullptr);

  const PanelData& cpd = *current_panel_data;

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
  if (cpd.is_held_) {
    theme = &theme_states->themes[kStateHeld];
  } else if (cpd.is_hovered_) {
    theme = &theme_states->themes[kStateHovered];
  } else if (cpd.is_selected_) {
    theme = &theme_states->themes[kStateSelected];
  } else if (cpd.is_focused_) {
    theme = &theme_states->themes[kStateFocused];
  } else {
    theme = &theme_states->themes[kStateNormal];
  }
}

} // namespace omega
