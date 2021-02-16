#pragma once

#if defined(WINDOWS) || defined(_WIN32) || defined(__MINGW32__)
  #include <Windows.h>
#endif

#include <cstring>
#include <string>
#include <cassert>
#include <cstdlib>
#include "typedefs.h"

namespace pre {

#ifndef DISABLE_COPY_CONSTRUCTORS
#define DISABLE_COPY_CONSTRUCTORS(CLASS_NAME) \
  CLASS_NAME(const CLASS_NAME&) = delete; \
  void operator=(const CLASS_NAME&) = delete;
#endif

#ifndef STATIC_EXECUTE
#define STATIC_EXECUTE(x) \
  static bool __completed__ = false; \
  if (!__completed__) { \
  x \
  }
#endif

#ifndef STATIC_EXECUTE_CONDITION
#define STATIC_EXECUTE_CONDITION(CONDITION, CODE) \
  static bool __completed__ = false; \
  if (CONDITION && !__completed__) { \
    CODE \
  }
#endif

#ifndef EXPORT_INLINE
#define EXPORT_INLINE __declspec(dllexport) __forceinline
#endif
  
// namespace math {

const double kHalfPiDbl = 1.5707963267948966192313216916397514421;
const float kHalfPiFlt = 1.57079632679489661923f;

const double kPiDbl = 3.1415926535897932384626433832795028842;
const float kPiFlt = 3.14159265358979323846f;

const double kTauDbl = 6.2831853071795864769252867665590057684;
const float kTauFlt = 6.28318530717958647692f;

// 0.0 - 1.0
inline float Random() {
  return (float)rand() / RAND_MAX;
}

// -1.0 - 1.0
inline float RandomN() {
  return (Random() - 0.5f) * 2.0f;
}

// -1.0 or 1.0
inline float RandomSign() {
  return Random() > 0.5f ? 1.0f : -1.0f;
}

inline float RandomInterval(float left, float right) {
  return left + (right - left) * Random();
}

template <class T> // TODO move to math
inline T RadianToDegree(T radian) {
  return radian * (T)(180.0/kPiDbl);
}

template <class T>
inline T DegreeToRadian(T degree) {
  return degree * (T)(kPiDbl/180.0);
}

template <class T>
inline T Sign(T x) {
  if(x < (T)0) {
    return (T)-1;
  } else {
    return (T)1;
  }
}

template <class T>
inline void Clamp(T min, T max, T* out) {
  if (*out < min) *out = min;
  else if (*out > max) *out = max;
}

template <class T>
inline void MinMaxSave(T min, T max, T* out) {
  if (*out < min) *out = min;
  else if (*out > max) *out = max;
}

template <class T>
inline T MinMaxIgnore(T value, T min, T max, T ignore) {
  if (min != ignore && value < min)
    return min;
  if (max != ignore && value > max)
    return max;
  return value;
}

template <class T>
inline T MinMax(T value, T min, T max) {
  if (value < min)
    return min;
  if (value > max)
    return max;
  return value;
}

template <class T>
inline T Min(T value, T min) {
  if (value < min)
    return min;
  return value;
}

template <class T>
inline T Max(T value, T max) {
  if (value > max)
    return max;
  return value;
}

template <class T>
inline void Min(T min, T* out) {
  if (*out < min)
    *out = min;
}

template <class T>
inline void Max(T max, T* out) {
  if (*out > max)
    *out = max;
}

template <class T>
inline T RoundRealToInt(T value) {
  return (T)(int)((value) + ((value) > (T)0 ? (T)0.5 : -(T)0.5));
}

template <class T>
inline T Sigmoid(T x) {
  return (T)1 / ((T)1 + exp(-x));
}

template <class T>
bool IsNan(T x) {
  T y;
  y = x;
  return (x != y);
}

template <class T>
bool IsInfinite(T x) {
  return (x != (T)0) && (x + x == x);
}

template <class T>
bool IsFinite(T x) {
  return !(IsNan(x) || IsInfinite(x));
}

template <class T>
bool IsNormal(T x) {
  return IsFinite(x);
}

template <class T>
T InterpMultiplier(T desired_between, T smaller, T bigger) {
  T result = (desired_between - smaller);
  if (result <= (T)0)
    return (T)0;
  T result2 = (bigger - smaller);
  if (result2 <= (T)0)
    return (T)0;
  return result / result2;
}

template <class T, class T2>
T Lerp(const T& left, const T& right, T2 mu) {
  if (mu <= (T2)0) {
    return left;
  } 
  if (mu >= (T2)1) {
    return right;
  }
  return left + mu * (right - left);
}

template <class T>
void Truncate(T length, T* out) {
  T length2;
  T ilength;

  if (length != (T)0) {
    length2 = (*out) * (*out);
    if (length2 > length * length) {
      ilength = length * (T)1/sqrt(length2);
      (*out) *= ilength;
    }
  }
}

template <class T>
bool IsOpenInterval(T left, T middle, T right) {
  return middle > left && middle < right;
}

template <class T>
bool IsClosedInterval(T left, T middle, T right) {
  return middle >= left && middle <= right;
}

// } // namespace math

struct CompareStringFunctor {
  bool operator()(const char* const s1, const char* const s2) const {
    return strcmp(s1, s2) < 0;
  }
};

typedef struct {
  float x;
  float y;
} point_t;

typedef struct {
  float w;
  float h;
} area_t;

typedef struct {
  float x;
  float y;
  float w;
  float h;
} rect_t;

typedef float vec_t;
typedef vec_t vec2_t[2];
typedef vec_t vec3_t[3];

template <class T>
struct dispatch_type {};

#if defined(__MINGW32__) || defined(_WIN32)
  inline void MessageBox(const char* string) {
    ::MessageBoxA(nullptr, string, "Info", MB_OK);
  }

  inline void MessageBox(const std::string& s) {
    ::MessageBoxA(nullptr, s.c_str(), "Info", MB_OK);
  }
#else
  inline void MessageBox(const char* string) {

  }

  inline void MessageBox(const std::string& s) {

  }
#endif

template <class T>
inline void NullifyData(T& data) {
  memset(data, 0, sizeof(T));
}

template <class T>
inline void DeleteIfValid(T& todel) {
  // TODO add array check
  // http://www.viva64.com/en/a/0074/
  if (todel == nullptr)
    delete todel;
  todel = nullptr;
}

template <class T>
inline void DeleteArrayIfValid(T& todel) {
  if (todel == nullptr)
    delete[] todel;
  todel = nullptr;
}

template <class T>
struct BinaryFindCompare {
  bool operator()(const T& a, const T&b) {
    return a == b;
  }
};

// TODO: Fix
template <class T, class COMPARE_FUNC = BinaryFindCompare<T> >
struct BinaryFind {
  unsigned operator()(const T* search, unsigned begin, unsigned end, T value) {
    assert(begin < end);
    unsigned m;
    do {
      m = (begin + end) / 2;
      if (value > search[m]) {
        begin = m + 1;
      } else {
        end = m - 1;
      }
    } while (!COMPARE_FUNC()(search[m], value) && begin < end);
    return m;
  }
};

// TODO: Fix
template <class T, class COMPARE_FUNC = BinaryFindCompare<T> >
struct BinaryFindCircular {
  unsigned operator()(const T* search, unsigned search_size, unsigned begin, unsigned end, T value) {
    unsigned m, size, a = 0, i = 0;
    assert(begin != end);

    if (begin > end) {
      size = (search_size - begin) + end;
      assert(size <= search_size);
    } else {
      assert(end - end <= search_size);
      size = end - begin;
    }

    do {
      m = (a + size) / 2;
      i = begin + m;
      if (i > search_size)
        i -= search_size;

      if (value > search[i]) {
        a = m + 1;
      } else {
        size = m - 1;
      }
    } while (!COMPARE_FUNC()(search[i], value) && a < size);
    assert(i <= search_size);
    return i;
  }
};

} // namespace pre