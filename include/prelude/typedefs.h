#pragma once

#ifdef _MSC_VER
  #define INT64(x) x##i64
  #define UINT64(x) x##ui64
#else
  #include <cstdint>
  #define INT64(x) x##ll
  #define UINT64(x) x##ull
#endif

#include <string>

typedef unsigned hfont;
typedef unsigned int uint;
typedef unsigned int bfbool; // bit field bool, i.e.: unsigned int mybool :1;
typedef unsigned long ulong;
typedef unsigned char byte;
typedef unsigned char* pbyte;
typedef unsigned long dword;
typedef unsigned long* pdword;

#if (defined(WINDOWS) || defined(_WIN32) || defined(__MINGW32__)) && defined(UNICODE)
  #ifndef _T
    #define _T(x) L##x
  #endif
  typedef std::wstring tstring;
  typedef wchar_t tchar;
#else
  #ifndef _T
    #define _T(x) x
  #endif
  typedef std::string tstring;
  typedef char tchar;
#endif

#ifdef _MSC_VER
  typedef __int8  int8;
  typedef __int16 int16;
  typedef __int32 int32;
  typedef __int64 int64;

  typedef unsigned __int8  uint8;
  typedef unsigned __int16 uint16;
  typedef unsigned __int32 uint32;
  typedef unsigned __int64 uint64;
#else
  typedef int8_t  int8;
  typedef int16_t int16;
  typedef int32_t int32;
  typedef int64_t int64;

  typedef uint8_t  uint8;
  typedef uint16_t uint16;
  typedef uint32_t uint32;
  typedef uint64_t uint64;
#endif

static const int32 kint32max = 0x7FFFFFFF;
static const int32 kint32min = -kint32max - 1;
static const int64 kint64max = INT64(0x7FFFFFFFFFFFFFFF);
static const int64 kint64min = -kint64max - 1;
static const uint32 kuint32max = 0xFFFFFFFFu;
static const uint64 kuint64max = UINT64(0xFFFFFFFFFFFFFFFF);
