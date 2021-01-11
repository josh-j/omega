#pragma once

#include <string>

namespace omega {
namespace Button {}

namespace TextButton {
void SetLabel(std::string label);
}

namespace CheckButton {
void Draw();
void Press();
}  // namespace CheckButton
}  // namespace omega
// compose CheckButton + TextButton for a button w/ text on left|right|top|below