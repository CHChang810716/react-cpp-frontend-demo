# reactdom-cmake-demo

Thanks to [asm-dom-cmake](https://github.com/ArthurSonzogni/asm-dom-cmake), we have a higher start point to demonstrate this idea.

Also thanks to [asm-dom](https://github.com/mbasso/asm-dom) and 
[gccx](https://github.com/mbasso/gccx) (JSX like syntax for C++), they are the most important infra tools.

# Motivation

We want to bring the reactjs-like state pattern to asm-dom/gccx to make C++ frontend programming easier to maintain and also, replace the stupid **setState** to operator= overlading.

This should make C++ react even better and safer than reactjs.
# Idea

1. Create a new type **State<T>** to maintain the side-effect and invoke the VNode patch when the value change.
2. Make a new set of asmdom::h interface(currently called reactdom::h) and accept the **State<T>** as the paramter.
3. Register/remove event inside the reactdom::h

# Implementation

1. Hacking the gccx, replace all asmdom::h -> reactdom::h
2. Implement the add/remove event behavior in reactdom::h

# How to build?

* Rebuild our customized gccx
~~~bash
cd lib/gccx
npm install
npm run build
~~~

* Make sure cmake, emscripten and npm are installed.
~~~bash
mkdir build
cd build
emcmake cmake ..
make
~~~

* Create a local server and navigate [http://localhost:8000](http://localhost:8000)
~~~
python -m SimpleHTTPServer 8000
~~~
