#pragma once
#include <emscripten/val.h>
#include <emscripten.h>
namespace cppdom {

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

template<class T>
void invoke_functor(void* arg) {
  T& obj = *(T*)arg;
  obj();
}

template<class Func>
auto async(Func& f) {
  emscripten_async_call(
    invoke_functor<Func>,
    (void*)&f,
    0
  );
}
  
} // namespace cppdom
