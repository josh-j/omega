#pragma once

unsigned CREATE_HASH(const char* s) {
  unsigned h = 0;
  while (*s) h = h * 101 + (unsigned char)*s++;
  return h;
}
