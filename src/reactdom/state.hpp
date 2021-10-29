#pragma once
#include <vector>
#include <functional>
#include "utils.hpp"
#include <asm-dom.hpp>
#include "to_vnode.hpp"

namespace reactdom {

template<class T>
struct State {
  using This = State<T>;
  using SideEffects = std::vector<
      std::function<bool(void)>
  >;

  explicit State(const T& init = {}) 
  : value_(init)
  , side_effects_once_()
  , side_effects_()
  {}

  This& operator=(const T& v) {
    value_ = v;
    for(auto& f : side_effects_) {
      async(f);
    }
    auto once = std::move(side_effects_once_);
    side_effects_once_.clear();
    for(auto&& f : once) {
      async(std::move(f));
    }
    return *this;
  }

  template<class Func>
  This& on_change(Func&& se) {
    side_effects_.push_back(
      std::bind(std::forward<Func>(se), *this)
    );
    return *this;
  }

  template<class Func>
  This& on_change_once(Func&& se) {
    side_effects_once_.push_back(
      std::bind(std::forward<Func>(se), *this)
    );
    return *this;
  }

  // T val() const { return value_; }
  operator T() {
    return value_;
  }

  auto render() const {
    return to_vnode(value_);
  }
private:
  T value_;
  SideEffects side_effects_once_;
  SideEffects side_effects_;
};

} // namespace reactdom