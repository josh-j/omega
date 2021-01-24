#pragma once

#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new (_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DBG_NEW
#endif
#endif  // _DEBUG

#include <cassert>
#include <string>

#include "prelude/color.h"
#include "prelude/common.h"
#include "prelude/event.h"
#include "prelude/log.h"
#include "prelude/singleton.h"
#include "prelude/typedefs.h"
#include "prelude/safe_assert.h"

// #define HERMES_CONFIG_TYPE Config_MapObjVecArray
// #define HERMES_STRING_TYPE std::string
// #include "../../hermes/src/hermes.h"

namespace omega {

using pre::Color;

}  // namespace omega
