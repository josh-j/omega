#pragma once
#include <cassert>
#include <cstddef>

#ifndef IMGUI_DISABLE_DEFAULT_MATH_FUNCTIONS
#define ImFabs(X) fabsf(X)
#define ImSqrt(X) sqrtf(X)
#define ImFmod(X, Y) fmodf((X), (Y))
#define ImCos(X) cosf(X)
#define ImSin(X) sinf(X)
#define ImAcos(X) acosf(X)
#define ImAtan2(Y, X) atan2f((Y), (X))
#define ImAtof(STR) atof(STR)
#define ImFloorStd(X) \
  floorf(X)  // We already uses our own ImFloor() { return (float)(int)v }
             // internally so the standard one wrapper is named differently
             // (it's used by e.g. stb_truetype)
#define ImCeil(X) ceilf(X)
static inline float Pow(float x, float y) {
  return powf(x, y);
}  // DragBehaviorT/SliderBehaviorT uses Pow with either float/double and need
   // the precision
static inline double Pow(double x, double y) { return pow(x, y); }
static inline float Log(float x) {
  return logf(x);
}  // DragBehaviorT/SliderBehaviorT uses Log with either float/double and need
   // the precision
static inline double Log(double x) { return log(x); }
static inline float Abs(float x) { return fabsf(x); }
static inline double Abs(double x) { return fabs(x); }
static inline float Sign(float x) {
  return (x < 0.0f) ? -1.0f : ((x > 0.0f) ? 1.0f : 0.0f);
}  // Sign operator - returns -1, 0 or 1 based on sign of argument
static inline double Sign(double x) {
  return (x < 0.0) ? -1.0 : ((x > 0.0) ? 1.0 : 0.0);
}
#endif
// - Min/Max/Clamp/Lerp/ImSwap are used by widgets which support variety of
// types: signed/unsigned int/long long float/double (Exceptionally using
// templates here but we could also redefine them for those types)
template <typename T>
static inline T Min(T lhs, T rhs) {
  return lhs < rhs ? lhs : rhs;
}
template <typename T>
static inline T Max(T lhs, T rhs) {
  return lhs >= rhs ? lhs : rhs;
}
template <typename T>
static inline T Clamp(T v, T mn, T mx) {
  return (v < mn) ? mn : (v > mx) ? mx : v;
}
template <typename T>
static inline T Lerp(T a, T b, float t) {
  return (T)(a + (b - a) * t);
}
template <typename T>
static inline void Swap(T& a, T& b) {
  T tmp = a;
  a = b;
  b = tmp;
}
template <typename T>
static inline T AddClampOverflow(T a, T b, T mn, T mx) {
  if (b < 0 && (a < mn - b)) return mn;
  if (b > 0 && (a > mx - b)) return mx;
  return a + b;
}
template <typename T>
static inline T SubClampOverflow(T a, T b, T mn, T mx) {
  if (b > 0 && (a < mn + b)) return mn;
  if (b < 0 && (a > mx + b)) return mx;
  return a - b;
}
// - Misc maths helpers
static inline Vec2 Min(const Vec2& lhs, const Vec2& rhs) {
  return Vec2(lhs.x < rhs.x ? lhs.x : rhs.x, lhs.y < rhs.y ? lhs.y : rhs.y);
}
static inline Vec2 Max(const Vec2& lhs, const Vec2& rhs) {
  return Vec2(lhs.x >= rhs.x ? lhs.x : rhs.x, lhs.y >= rhs.y ? lhs.y : rhs.y);
}
static inline Vec2 Clamp(const Vec2& v, const Vec2& mn, Vec2 mx) {
  return Vec2((v.x < mn.x)   ? mn.x
              : (v.x > mx.x) ? mx.x
                             : v.x,
              (v.y < mn.y)   ? mn.y
              : (v.y > mx.y) ? mx.y
                             : v.y);
}
static inline Vec2 Lerp(const Vec2& a, const Vec2& b, float t) {
  return Vec2(a.x + (b.x - a.x) * t, a.y + (b.y - a.y) * t);
}
static inline Vec2 Lerp(const Vec2& a, const Vec2& b, const Vec2& t) {
  return Vec2(a.x + (b.x - a.x) * t.x, a.y + (b.y - a.y) * t.y);
}
static inline Vec4 Lerp(const Vec4& a, const Vec4& b, float t) {
  return Vec4(a.x + (b.x - a.x) * t, a.y + (b.y - a.y) * t,
              a.z + (b.z - a.z) * t, a.w + (b.w - a.w) * t);
}
static inline float ImSaturate(float f) {
  return (f < 0.0f) ? 0.0f : (f > 1.0f) ? 1.0f : f;
}
static inline float ImLengthSqr(const Vec2& lhs) {
  return (lhs.x * lhs.x) + (lhs.y * lhs.y);
}
static inline float ImLengthSqr(const Vec4& lhs) {
  return (lhs.x * lhs.x) + (lhs.y * lhs.y) + (lhs.z * lhs.z) + (lhs.w * lhs.w);
}
static inline float ImInvLength(const Vec2& lhs, float fail_value) {
  float d = (lhs.x * lhs.x) + (lhs.y * lhs.y);
  if (d > 0.0f) return 1.0f / ImSqrt(d);
  return fail_value;
}
static inline float ImFloor(float f) { return (float)(int)(f); }
static inline Vec2 ImFloor(const Vec2& v) {
  return Vec2((float)(int)(v.x), (float)(int)(v.y));
}
static inline int ImModPositive(int a, int b) { return (a + b) % b; }
static inline float ImDot(const Vec2& a, const Vec2& b) {
  return a.x * b.x + a.y * b.y;
}
static inline Vec2 ImRotate(const Vec2& v, float cos_a, float sin_a) {
  return Vec2(v.x * cos_a - v.y * sin_a, v.x * sin_a + v.y * cos_a);
}
static inline float ImLinearSweep(float current, float target, float speed) {
  if (current < target) return Min(current + speed, target);
  if (current > target) return Max(current - speed, target);
  return current;
}
static inline Vec2 ImMul(const Vec2& lhs, const Vec2& rhs) {
  return Vec2(lhs.x * rhs.x, lhs.y * rhs.y);
}

struct Vec2 {
  float x, y;
  Vec2() { x = y = 0.0f; }
  Vec2(float _x, float _y) {
    x = _x;
    y = _y;
  }
  float operator[](size_t idx) const {
    assert(idx <= 1);
    return (&x)[idx];
  }  // We very rarely use this [] operator, the assert overhead is fine.
  float& operator[](size_t idx) {
    assert(idx <= 1);
    return (&x)[idx];
  }  // We very rarely use this [] operator, the assert overhead is fine.
};

// 4D vector (often used to store floating-point colors)
struct Vec4 {
  float x, y, z, w;
  Vec4() { x = y = z = w = 0.0f; }
  Vec4(float _x, float _y, float _z, float _w) {
    x = _x;
    y = _y;
    z = _z;
    w = _w;
  }
};

struct Rect {
  Vec2 Min;  // Upper-left
  Vec2 Max;  // Lower-right

  Rect() : Min(0.0f, 0.0f), Max(0.0f, 0.0f) {}
  Rect(const Vec2& min, const Vec2& max) : Min(min), Max(max) {}
  Rect(const Vec4& v) : Min(v.x, v.y), Max(v.z, v.w) {}
  Rect(float x1, float y1, float x2, float y2) : Min(x1, y1), Max(x2, y2) {}

  Vec2 GetCenter() const {
    return Vec2((Min.x + Max.x) * 0.5f, (Min.y + Max.y) * 0.5f);
  }
  Vec2 GetSize() const { return Vec2(Max.x - Min.x, Max.y - Min.y); }
  float GetWidth() const { return Max.x - Min.x; }
  float GetHeight() const { return Max.y - Min.y; }
  Vec2 GetTL() const { return Min; }                 // Top-left
  Vec2 GetTR() const { return Vec2(Max.x, Min.y); }  // Top-right
  Vec2 GetBL() const { return Vec2(Min.x, Max.y); }  // Bottom-left
  Vec2 GetBR() const { return Max; }                 // Bottom-right
  bool Contains(const Vec2& p) const {
    return p.x >= Min.x && p.y >= Min.y && p.x < Max.x && p.y < Max.y;
  }
  bool Contains(const Rect& r) const {
    return r.Min.x >= Min.x && r.Min.y >= Min.y && r.Max.x <= Max.x &&
           r.Max.y <= Max.y;
  }
  bool Overlaps(const Rect& r) const {
    return r.Min.y < Max.y && r.Max.y > Min.y && r.Min.x < Max.x &&
           r.Max.x > Min.x;
  }
  void Add(const Vec2& p) {
    if (Min.x > p.x) Min.x = p.x;
    if (Min.y > p.y) Min.y = p.y;
    if (Max.x < p.x) Max.x = p.x;
    if (Max.y < p.y) Max.y = p.y;
  }
  void Add(const Rect& r) {
    if (Min.x > r.Min.x) Min.x = r.Min.x;
    if (Min.y > r.Min.y) Min.y = r.Min.y;
    if (Max.x < r.Max.x) Max.x = r.Max.x;
    if (Max.y < r.Max.y) Max.y = r.Max.y;
  }
  void Expand(const float amount) {
    Min.x -= amount;
    Min.y -= amount;
    Max.x += amount;
    Max.y += amount;
  }
  void Expand(const Vec2& amount) {
    Min.x -= amount.x;
    Min.y -= amount.y;
    Max.x += amount.x;
    Max.y += amount.y;
  }
  void Translate(const Vec2& d) {
    Min.x += d.x;
    Min.y += d.y;
    Max.x += d.x;
    Max.y += d.y;
  }
  void TranslateX(float dx) {
    Min.x += dx;
    Max.x += dx;
  }
  void TranslateY(float dy) {
    Min.y += dy;
    Max.y += dy;
  }
  void ClipWith(const Rect& r) {
    Min = Max(Min, r.Min);
    Max = Min(Max, r.Max);
  }  // Simple version, may lead to an inverted rectangle, which is fine for
     // Contains/Overlaps test but not for display.
  void ClipWithFull(const Rect& r) {
    Min = Clamp(Min, r.Min, r.Max);
    Max = Clamp(Max, r.Min, r.Max);
  }  // Full version, ensure both points are fully clipped.
  void Floor() {
    Min.x = FLOOR(Min.x);
    Min.y = FLOOR(Min.y);
    Max.x = FLOOR(Max.x);
    Max.y = FLOOR(Max.y);
  }
  bool IsInverted() const { return Min.x > Max.x || Min.y > Max.y; }
  Vec4 ToVec4() const { return Vec4(Min.x, Min.y, Max.x, Max.y); }
};
