#include "panel.hpp"

#include <assert.h>

#include <state.hpp>

namespace Panel {

void Begin() { ++s.level; }

void End() {
  assert(s.level > 0);
  --s.level;
}

void BeginChild() {}

void EndChild() {}

}  // namespace Panel
