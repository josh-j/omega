#pragma once
#include <string>
#include <vector>

#include "common.h"

struct State {
  uint32_t level{0};
  std::string line{""};
  std::vector<std::string> many_lines{};
  Rect rect;
};

State s;
