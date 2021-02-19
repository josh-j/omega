#pragma once

#include <vector>
#include <string>
#include "common.h"
#include "forward_declarations.h"

namespace omega {


typedef std::vector <unsigned> FontLetterWidths;

class Font { // Todo rename FontBrush
  friend class FontManager;
 private: // Only FontManager can create fonts so that dozens of unnecessary fonts aren't left in memory
   Font();
   Font(const std::string& font_face, uint font_height, uint font_weight, uint flags);
   ~Font();

 public:
   enum HorizontalAlign {
     kHorzAlignLeft,
     kHorzAlignCenter,
     kHorzAlignRight
   };

   enum VerticleAlign {
     kVertAlignTop,
     kVertAlignMiddle,
     kVertAlignBottom
   };

  enum {
    kFlagNone = 0,
    kFlagItalicized = (1 << 0),
    kFlagUnderline = (1 << 1),
    kFlagInlineColors = (1 << 2)
  };

  void Init(const std::string& font_face, uint font_height, uint font_weight, uint flags);
  void TextRaw(float x, float y, int r, int g, int b, int a, const char* const text);
  void TextRaw(const Point& point, const Color& color, const std::string& text);
  void Text(const Point& offset, const Color& color, const std::string& text);
  void Text(const Point& offset, const Color& color, Font::HorizontalAlign horizontal_align, Font::VerticleAlign verticle_align, const std::string& text);
  void BoxedText(const Rect& rect, const Color& color, const std::string& text);
  void BoxedText(const Rect& rect, const Color& color, Font::HorizontalAlign horizontal_align, Font::VerticleAlign verticle_align, const std::string& text);
  void BoxedText(const Point& offset, const Rect& rect, const Color& color, const std::string& text);
  void BoxedText(const Point& offset, const Rect& rect, const Color& color, Font::HorizontalAlign horizontal_align, Font::VerticleAlign verticle_align, const std::string& text);
  float GetTextWidth(const char* const text);
  float GetTextWidth(const std::string& text);
  float GetLineHeight() const;
  size_t GetTextExtent(const std::string& text, float max_width);
  size_t GetTextExtentReverse(const std::string& text, float max_width);

  bool operator==(const Font& other) const {
    if (face() == other.face() &&
        height() == other.height() &&
        weight() == other.weight() &&
        flags() == other.flags())
      return true;
    return false;
  }

  // Properties
  void set_renderer(Renderer* renderer) { renderer_ = renderer; }
  void set_face(const std::string& face) { face_ = face; }
  void set_height(uint height) { height_ = height; }
  void set_weight(uint weight) { weight_ = weight; }
  void set_handle(hfont handle) { handle_ = handle; }
  void set_flags(uint flags) { flags_ = flags; }

  const std::string& face() const { return face_; }
  uint height() const { return height_; }
  uint weight() const { return weight_; }
  hfont handle() const { return handle_; }
  uint flags() const { return flags_; }

 private:
  FontLetterWidths letter_widths_;
  Renderer* renderer_;
  std::string face_;
  uint height_;
  uint weight_;
  hfont handle_;
  uint flags_;
  uint num_owners_;
};

} // namespace omega
