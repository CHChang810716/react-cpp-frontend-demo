#pragma once
#include <asm-dom.hpp>

namespace reactdom {

template<class T>
asmdom::VNode* to_vnode(const T& v) {
  return asmdom::h(std::to_string(v), true);
}
  
} // namespace reactdom
