#pragma once
#include <string>
#include <vector>

#include "common.h"
#include "renderer.h"

namespace omega {
struct State {
  uint32_t level{0};
  std::string line{""};
  std::vector<std::string> many_lines{};
  Rect rect;
  // Renderer* renderer{nullptr};
};

extern State s;
}  // namespace omega
