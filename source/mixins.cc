#include "mixins.h"

namespace omega {

// template <typename T>
// void Painter<T>::Paint() {

// }


void __ignore() {
  struct dummy {};
  Painter<dummy> d;
}

} // namespace omega
