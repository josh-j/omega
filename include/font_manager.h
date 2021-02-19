#pragma once

#include <vector>
#include "common.h"
#include "font.h"

namespace omega {

class Renderer;
class FontManager {
  typedef std::vector <Font*> Fonts;
 public:
  FontManager();
  ~FontManager();

 public:
  Font* Build(const std::string& face, uint height, uint weight, uint flags);
  void Destroy(hfont handle);
  Font* Find(hfont font) const;
  Font* Find(const std::string& face, uint height, uint weight, uint flags) const;
  void Dispose();

  void set_renderer(Renderer* renderer);
 private:
  Fonts fonts_;
  Renderer* renderer_;
};

} // namespace omega
