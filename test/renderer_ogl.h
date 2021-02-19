#pragma once
#include "../include/renderer.h"

namespace omega_test {

OPEN_RENDERER_INTERFACE(RendererOGL)

void RenderTextf(omega::hfont font_id, float x, float y,
                 const char *const fmt, ...);
CLOSE_INTERFACE

}  // namespace omega_test
