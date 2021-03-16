#pragma once

#include "common.h"
#include "point.h"
#include "size.h"

namespace omega {

class Rect {
 public:
  Rect() {}

  Rect(float init) { set(init, init, init, init); }

  Rect(float x, float y, float w, float h) { set(x, y, w, h); }

  Rect(const Point& position, const Size& size) { set(position, size); }

  Rect(const Rect& rect) { set(rect); }

  ~Rect() {}

  void clear() { x = y = w = h = 0.0f; }

  void set(float xpos, float ypos, float width, float height) {
    x = xpos;
    y = ypos;
    w = width;
    h = height;
  }

  void set(const Point& position, const Size& size) {
    x = position.x;
    y = position.y;
    w = size.w;
    h = size.h;
  }

  void set(const Rect& rect) {
    x = rect.x;
    y = rect.y;
    w = rect.w;
    h = rect.h;
  }

  void set_position(float xpos, float ypos) {
    x = xpos;
    y = ypos;
  }

  void set_position(const Point& position) {
    x = position.x;
    y = position.y;
  }

  void set_size(float size) {
    w = size;
    h = size;
  }

  void set_size(float width, float height) {
    w = width;
    h = height;
  }

  void set_size(const Size& size) {
    w = size.w;
    h = size.h;
  }

  void set_rightpos(float rightpos) { w = rightpos - x; }

  void set_bottompos(float bottompos) { h = bottompos - y; }

  bool empty() const { return x == 0.0f && y == 0.0f && w == 0.0f && h == 0.0f; }
  bool contains(float xpos, float ypos) const {
    return (xpos >= x && ypos >= y && xpos <= x + w && ypos <= y + h);
  }

  bool contains(const Point& point) const {
    return (point.x >= x && point.y >= y && point.x <= x + w &&
            point.y <= y + h);
  }

  Rect crop(float x, float y, float w, float h) const {
    Rect ret = *this;
    ret.x += x;
    ret.y += y;
    ret.w -= w + x;
    ret.h -= h + y;
    return ret;
  }

  Rect crop(float crop_amount) const {
    return crop(crop_amount, crop_amount, crop_amount, crop_amount);
  }

  float rightpos() const { return x + w; }
  float bottompos() const { return y + h; }

  Point pos() const { return Point(x, y); }
  Size size() const { return Size(w, h); }

  std::string print() const {
    return std::to_string(x) + ' ' + std::to_string(y) + ' ' + std::to_string(w) + ' ' +  std::to_string(h);
  }
  float x, y, w, h;
};

}  // namespace omega
