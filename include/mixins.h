#pragma once

namespace omega {

template <typename T> struct DependencyInject : T {};

template <typename T> struct Mover : T {};

template <typename T> struct Painter : T {
  void Paint() {}
};

template <typename T> struct MouseBehavior : T {
  void Move();
  void Press();
};


template <typename T> struct DeclareLifetime : T {
  DeclareLifetime<T>() {

  }
};



} // namespace omega
