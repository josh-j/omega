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

// What needs to be private goes into the implementation
// We can put GuiContext in here, but have the used instantation in the implementation and only accessible through functions

// Maybe this should be GUIState, then we have IOState and DeclarativeState
// Or should we have State then IO and Declaratives are in State < if everything is in State we can better restrict usage of state
namespace GUI {

const Panel::PanelData& PanelContext();
Panel::PanelData& PanelMutableContext();

void Begin();
void Draw();
void UpdateTheme();
void SetTheme(ThemeStates& themes);
void End();
void EndFrame();

// Helpers
void set_renderer(Renderer& renderer);
Rect& delc_rect();
Rect& drawn_rect();
bool is_current_child();
Panel::PanelData* current_panel_data();
void set_cursor(CursorType cursor_type);
extern DeclarativeManager dm;

namespace ModifiesState {
/*
** Begin
** End
** UpdateTHeme
** SetTheme
** End
** EndFrame
**
*/
} // namespace ModifiesState

} // namespace GUI
} // namespace omega
