#pragma once

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
*/

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

bool Contains(float xpos, float ypos);
// bool Contains(const Point &point);


void Begin();
void End();
void BeginChild();
void EndChild();

void Draw();
void SetShape(float x, float y, float w, float h, const Color& color);
void MoveTo(float x, float y);
void MoveAdjust(float x, float y);
void Resize(float w, float h);
void SetMinMaxSize(float w_min, float h_min, float w_max, float h_max);
void OnMouseMove();
void OnMousePress();
inline void OnMouseRelease() {}

void OnMouseSingleClick();
void OnMouseDoubleClick();
void OnMouseWheel();
Rect& Area(Rect& rect);
Color& SetColor(int r, int g, int b, int a);

namespace Declare {
void Begin();
void End();
bool Contains(float xpos, float ypos);
//bool Contains(const Point& point);
void Draw();
Rect& Area(Rect rect);
Color& Color(int r, int g, int b, int a);

} // namespace Declare

}  // namespace Panel
}  // namespace omega
