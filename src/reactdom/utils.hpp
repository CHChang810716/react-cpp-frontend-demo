#pragma once
#include <emscripten/val.h>
#include <emscripten.h>
namespace reactdom {

struct {
  emscripten::val getElementById(const std::string& id) {
    return get().call<emscripten::val>("getElementById", id);
  }
private:
  static emscripten::val& get() {
    static emscripten::val _res
      = emscripten::val::global("document");
    return _res;
  }
} document;

struct {
  emscripten::val log(const std::string& msg) {
    return get().call<emscripten::val>("log", msg);
  }
private:
  static emscripten::val& get() {
    static emscripten::val _res
      = emscripten::val::global("console");
    return _res;
  }
} console;

template<class T, bool need_delete>
void invoke_functor(void* arg) {
  T& functor = *(T*)arg;
  functor();
  if constexpr(need_delete) {
    delete (T*)arg;
  }
}

template<class Func>
auto async(Func&& f) {
  void* arg = nullptr;
  constexpr bool need_heap = std::is_rvalue_reference_v<Func&&>;
  if constexpr(!need_heap) {
    arg = &f;
  } else {
    arg = new Func(std::move(f));
  }
  emscripten_async_call(
    invoke_functor<std::decay_t<Func>, need_heap>,
    arg,
    0
  );
}
  
} // namespace cppdom
