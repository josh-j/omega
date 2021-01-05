#include "button.hpp"
#include "text.hpp"

namespace Button {

void SetLabel(std::string label) {
    Text::Set(label);
}
}