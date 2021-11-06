#pragma once
#include <asm-dom.hpp>
#include "reactdom/state.hpp"
#include <iostream>
#include <toHTML/toHTML.hpp>
#include "reactdom/css.hpp"
#include "reactdom/fetch.hpp"

namespace reactdom {

template<class T>
asmdom::VNode* h(const std::string& sel, State<T>& state) {
  auto* node = asmdom::h(sel, state.render());
  state.on_change_once([node, sel, &state](const State<T>& s){
    auto* tmp = h(sel, state);
    if(!asmdom::patch(node, tmp)) {
      std::cerr << "patch failed" << std::endl;
    };
    return true;
  });
  return node;
}

template<class T>
asmdom::VNode* h(
  const std::string& sel, 
  const asmdom::Data& data, 
  State<T>& state
) {
  auto* node = asmdom::h(sel, data, state.render());
  state.on_change_once([node, sel, data, &state](const State<T>& s){
    asmdom::patch(node, h(sel, data, state));
    return true;
  });
  return node;
}
using asmdom::h;

asmdom::Config config() {
  asmdom::Config config = asmdom::Config();
  config.unsafePatch = true;
  return config;
}
}