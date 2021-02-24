#pragma once

#include <string>
#include "panel.h"

namespace omega {
namespace Button {
using namespace omega::Panel;

namespace Declare{
using namespace omega::Panel::Declare;

}
}

namespace TextButton {
void SetLabel(std::string label);
}

namespace CheckButton {
void Draw();
void Press();
}  // namespace CheckButton
}  // namespace omega
// compose CheckButton + TextButton for a button w/ text on left|right|top|below
