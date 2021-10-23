#pragma once
#include <vector>
#include <functional>
#include <future>
#include "asm-dom.hpp"
#include "cppdom.hpp"

namespace reactcpp {

template<class T>
struct State {
using This = State<T>;
using SideEffects = std::vector<
    std::function<bool(void)>
>;
template<class Derived>
friend class Component;
  
  This& operator=(const T& v) {
    value_ = v;
    for(auto& f : side_effects_) {
      cppdom::async(f);
    }
    return *this;
  }

  template<class Func>
  This& operator+=(Func&& se) {
    side_effects_.push_back(
      std::bind(std::forward<Func>(se), *this)
    );
    return *this;
  }

  operator T() { return value_; }

  std::string str() const {
    return std::to_string(value_);
  }
private:
    State(const T& init) 
    : value_(init)
    , side_effects_()
    {}
    T value_;
    SideEffects side_effects_;
};

template<class Derived>
struct Component {

  template<class T>
  State<T> make_state(const T& init) {
    State<T> s(init);
    s += [this](const State<T>& s) {
      (*this)();
      return true;
    };
    return s;
  }

  asmdom::VNode* operator()() {
    auto* new_node = derived().render();
    if(cur != nullptr) {
      asmdom::patch(cur, new_node);
    }
    cur = new_node;
    return cur;
  }
  
private:
  Derived& derived() { return static_cast<Derived&>(*this); }
  const Derived& derived() const { return static_cast<const Derived&>(*this); }
  asmdom::VNode* cur {nullptr};
};
#define ReactComponent(name) struct name : reactcpp::Component<name>
    
} // namespace reactcpp
