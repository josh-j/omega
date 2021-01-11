#include "panel.h"

#include <assert.h>

#include "state.h"

namespace omega {
namespace Panel {

void Begin() { ++s.level; }

void End() {
  assert(s.level > 0);
  --s.level;
}

void BeginChild() {}

void EndChild() {}

}  // namespace Panel
}  // namespace omega