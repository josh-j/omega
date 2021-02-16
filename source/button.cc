#include "button.h"

#include "text.h"

namespace omega::Button {

void SetLabel(std::string label) { Text::Set(label); }

}  // namespace omega::Button
