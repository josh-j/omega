
#pragma once

namespace omega {

struct Point {
  Point() : x(0.0f), y(0.0f) {}  // TODO remove init
  Point(float xpos, float ypos) : x(xpos), y(ypos) {}
  ~Point() {}
  void set(float xpos, float ypos) {
    x = xpos;
    y = ypos;
  }
  void clear() {
    x = 0.0f;
    y = 0.0f;
  }
  bool operator==(const Point& other) const {
    return abs(other.x - x) < 0.1f && abs(other.y - y) < 0.1f;
  }
  bool operator!=(const Point& other) const { return !operator==(other); }

  Point& operator=(const Point& point) {
    x = point.x;
    y = point.y;
    return *this;
  }

  Point& operator=(float xyvalue) {
    x = xyvalue;
    y = xyvalue;
    return *this;
  }

  Point operator+(const Point& other) {
    return Point(x + other.x, y + other.y);
  }

  Point operator-(const Point& other) {
    return Point(x - other.x, y - other.y);
  }

  float x, y;
};

}  // namespace omega
