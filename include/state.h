#pragma once
#include <string>
#include <vector>

#include "common.h"
#include "rect.h"
#include "renderer.h"
#include "forward_declarations.h"
#include "declarative.h"

namespace omega {
struct State {
  uint32_t level{0};
  std::string line{""};
  std::vector<std::string> many_lines{};
  Rect rect;
  Color color;
  bool is_child;
  Renderer* renderer{nullptr};
};

extern State s;
}  // namespace omega
