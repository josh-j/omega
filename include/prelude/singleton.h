#pragma once

// Rarely if ever used -- avoid

namespace pre {

template <typename T>
struct Singleton {
  Singleton(const Singleton&);
  Singleton& operator=(const Singleton&);
  Singleton();
public:
  static T& instance() {
    static T inst;
    // calling this causes the compiler to define the object at compile time
    // this means object_ is constructed and that then builds the instance at global time
    // rather than when instance is called by the user
    object_.null_function();
    return inst;
  }
private:
  struct object {
    object() { Singleton<T>::instance(); }
    void null_function() {}
  };
  static object object_;
};

template <typename T>
typename Singleton<T>::object Singleton<T>::object_;

} // namespace pre
