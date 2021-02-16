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

  Rect null_rect{0.0f, 0.0f, 0.0f, 0.0f};
  Rect* abs_rect{&null_rect};
  Rect rect{0.0f, 0.0f, 0.0f, 0.0f};
  Color color{255,255,255,255};
  bool is_child{false};
  bool is_pressed{false};
  bool is_moving{false};
  Renderer* renderer{nullptr};
};

extern DeclarativeManager dm;
extern State s;
}  // namespace omega
