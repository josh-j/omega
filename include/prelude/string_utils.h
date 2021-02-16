#pragma once

#include <string>
#include <cstdio>

namespace pre {

bool ToBool(const std::string& bool_string) {
  if (bool_string.empty())
    return false;

  switch (bool_string[0])
  {
  case 'o':
  case 'O':
    {
      if (bool_string[1] == 'f' || bool_string[1] == 'F')
        return false;

      return true;
    }

  case 'y':
  case 'Y':
  case 't':
  case 'T':
  case '1':
    return true;

  default:
    return false;
  }

  return false;
}

int ToInt(const std::string& int_string) {
  int value = 0;
  sscanf(int_string.c_str(), "%d", &value);
  return value;
}

std::string BoolToString(bool value) {
  if (value)
    return "true";
  return "false";
}

std::string IntToString(int value) {
  char buffer[64];
  sprintf(buffer, "%i", value);
  return std::string(buffer);
}

bool WildcardCompare(const std::string& wildcard_string, const std::string& other_string) {
  uint32_t i = 0, x = 0, last = 0;
  for (; i < other_string.length() && wildcard_string[x]; ++i) {
    if (wildcard_string[x] == '*') {
    last = ++x;
    } else if (wildcard_string[x] == other_string[i]) {
    ++x;
    } else {
    x = last;
    if (wildcard_string[x] == other_string[i])
      ++x;
    }
  }
  return !wildcard_string[x];
}

} // namespace pre
