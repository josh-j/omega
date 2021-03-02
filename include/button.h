#pragma once

#include <string>
#include "panel.h"

namespace omega {
namespace Button {
using namespace omega::GUI;
using namespace omega::Panel;
void Draw();
void OnMouseMove();

namespace Declare{
using namespace omega::Panel::Declare;

} // namespace Declare
} // nammespace Button

namespace TextButton {
void SetLabel(std::string label);
}

namespace CheckButton {
void Draw();
void Press();
}  // namespace CheckButton
}  // namespace omega
// compose CheckButton + TextButton for a button w/ text on left|right|top|below
