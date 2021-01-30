#pragma once
#include "common.h"

namespace omega {
namespace Window {

void Begin();
void SetShape(float x, float y, float w, float h, const Color& color);
void SetTitle(const std::string& title);
void Draw();

}
}  // namespace omega
