#include "button.h"

#include "text.h"

namespace omega {
namespace Button {

void SetLabel(std::string label) { Text::Set(label); }
}  // namespace Button
}  // namespace omega
