#include <state.hpp>
#include <assert.h>
#include "panel.hpp"

namespace Panel {


void Begin() {
    ++s.level;
}

void End() {
    assert(s.level > 0);
    --s.level;
}

void BeginChild() {

}

void EndChild() {

}

}
