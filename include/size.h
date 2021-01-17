#pragma once

namespace omega {

struct Size {
  Size() : w(0.0f), h(0.0f) {}  // TODO remove init
  Size(float width, float height) : w(width), h(height) {}
  Size(float size) : w(size), h(size) {}
  ~Size() {}
  void set(float width, float height) {
    w = width;
    h = height;
  }
  // void operator()(float width, float height) { set(width, height); }
  // bool operator<(const Size& size) const { return w < size.w && h < size.h; }
  // bool operator>(const Size& size) const { return w > size.w && h > size.h; }
  // bool operator==(const Size& size) const { return w == size.w && h ==
  // size.h; } bool operator!=(const Size& size) const { return
  // !operator==(size); }

  Size operator-(const Size& other) const {
    return Size(w - other.w, h - other.h);
  }

  Size& operator=(const Size& size) {
    w = size.w;
    h = size.h;
    return *this;
  }

  Size& operator=(float size) {
    w = size;
    h = size;
    return *this;
  }
  float w, h;
};

}  // namespace omega
