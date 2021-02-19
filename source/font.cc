#include "font.h"
#include "brush.h"
#include "rect.h"
#include "font_manager.h"
#include "renderer.h"

namespace omega {

Font::Font()
  : renderer_(nullptr),
    face_("Arial"),
    height_(10),
    weight_(500),
    handle_(0),
    flags_(kFlagNone),
    num_owners_(0) {}

Font::Font(const std::string& font_face, uint font_height, uint font_weight, uint flags)
  : renderer_(nullptr),
    face_(font_face),
    height_(height_),
    weight_(weight_),
    handle_(0),
    flags_(flags),
    num_owners_(0) {}

Font::~Font() {}

//************************************************************************************************************

void Font::Init(const std::string& font_face, uint font_height, uint font_weight, uint flags) {
  face_ = font_face; height_ = font_height; weight_ = font_weight; flags_ = flags;
}

void Font::TextRaw(float x, float y, int r, int g, int b, int a,
                   const char* const text) {
  SAFE_ASSERT(renderer_ != nullptr);
  renderer_->SetColor(r, g, b, a);
  renderer_->RenderText(handle_, x, y, text);
}

void Font::TextRaw(const Point& point, const Color& color, const std::string& text) {
  SAFE_ASSERT(renderer_ != nullptr);
  renderer_->SetColor(color.r, color.g, color.b, color.a);
  renderer_->RenderText(handle_, point.x, point.y, text.c_str());
}

void Font::Text(const Point& position, const Color& color, const std::string& text) {
  TextRaw(position, color, text);
}

void Font::Text(const Point& position, const Color& color,
                    Font::HorizontalAlign horizontal_align, Font::VerticleAlign verticle_align,
                    const std::string& text) {

  Point offset = position;
  if (horizontal_align == Font::kHorzAlignCenter) {
    offset.x -= (GetTextWidth(text) * 0.5f);
  } else if (horizontal_align == Font::kHorzAlignRight) {
    offset.x -= GetTextWidth(text);
  }

  if (verticle_align == Font::kVertAlignMiddle) {
    offset.y -= height_ * 0.5f;
  } else if (verticle_align == Font::kVertAlignBottom) {
    offset.y -= height_;
  }

  TextRaw(offset, color, text);
}

void Font::BoxedText(const Rect& rect, const Color& color, const std::string& text) {
  Point pos;
  pos.x = (rect.x + (rect.w * 0.5f)) - (GetTextWidth(text) * 0.5f);
  pos.y = (rect.y + (rect.h * 0.5f)) - (height_ * 0.5f);
  pos.y += height_;
  TextRaw(pos, color, text);
}

void Font::BoxedText(const Rect& rect, const Color& color,
                          Font::HorizontalAlign horizontal_align, Font::VerticleAlign verticle_align,
                          const std::string& text) {
  Point pos;
  if (horizontal_align == kHorzAlignLeft) {
    pos.x = rect.x;
  } else if (horizontal_align == Font::kHorzAlignCenter) {
    pos.x = (rect.x + (rect.w * 0.5f)) - (GetTextWidth(text) * 0.5f);
  } else {
    pos.x = rect.rightpos() - GetTextWidth(text);
  }

  if (verticle_align == Font::kVertAlignTop) {
    pos.y = rect.y;
  } else if (verticle_align == Font::kVertAlignMiddle) {
    pos.y = (rect.y + (rect.h * 0.5f)) - height_ * 0.5f;
  } else {
    pos.y = rect.bottompos() - height_;
  }

  pos.y += height_;
  TextRaw(pos, color, text);
}

void Font::BoxedText(const Point& offset, const Rect& rect, const Color& color,
  const std::string& text) {
  Point pos;
  pos.x = (rect.x + (rect.w * 0.5f)) - (GetTextWidth(text) * 0.5f);
  pos.y = (rect.y + (rect.h * 0.5f)) - (height_ * 0.5f);
  pos.x += offset.x;
  pos.y += offset.y + height_;
  TextRaw(pos, color, text);
}

void Font::BoxedText(const Point& offset, const Rect& rect, const Color& color,
                          Font::HorizontalAlign horizontal_align, Font::VerticleAlign verticle_align,
                          const std::string& text) {
  Point pos;

  if (horizontal_align == kHorzAlignLeft) {
    pos.x = rect.x;
  } else if (horizontal_align == Font::kHorzAlignCenter) {
    pos.x = (rect.x + (rect.w * 0.5f)) - (GetTextWidth(text) * 0.5f);
  } else {
    pos.x = rect.rightpos() - GetTextWidth(text);
  }

  if (verticle_align == Font::kVertAlignTop) {
    pos.y = rect.y;
  } else if (verticle_align == Font::kVertAlignMiddle) {
    pos.y = (rect.y + (rect.h * 0.5f)) - (height_ * 0.5f);
  } else {
    pos.y = rect.bottompos() - height_;
  }
  pos.x += offset.x;
  pos.y += offset.y + height_;
  TextRaw(pos, color, text);
}

float Font::GetTextWidth(const char* const text) {
  float width = 0.0f;
  for (size_t i = 0; text[i] != '\0'; ++i) {
    width += letter_widths_[text[i]];
  }
  return width;
}

float Font::GetTextWidth(const std::string& text) {
  // TODO profile to see if this caching is faster
  //if (cached_widths_.find(text) != cached_widths_.end()) {
  //  return cached_widths_[text];
  //}

  float width = 0.0f;

  for (size_t i = 0; i < text.size(); ++i) {
    width += letter_widths_[text[i]];
  }
  //cached_widths_[text] = width;
  return width;
}

float Font::GetLineHeight() const {
  return static_cast<float>(height_); // + font_padding
}

size_t Font::GetTextExtent(const std::string& text, float max_width) {
  if (text.empty() || letter_widths_.empty()) return 0;
  float width = 0.0f;
  for (size_t i = 0; i < text.size(); ++i) {
    //if (i >= letter_widths_.size()) continue;
    width += letter_widths_[text[i]];
    if (width >= max_width)
      return i;
  }

  return text.size();
}

size_t Font::GetTextExtentReverse(const std::string& text, float max_width) {
  if (text.empty() || letter_widths_.empty()) return 0;
  float width = 0.0f;
  size_t i = 0;
  for (std::string::const_reverse_iterator it = text.crbegin();
    it != text.crend(); ++it, ++i) {
    width += letter_widths_[*it];
    if (width >= max_width)
      return i;
  }

  return 0;
}

//************************************************************************************************************

} // namespace omega
