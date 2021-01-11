#pragma once

#include <string>
#include <vector>

#include "prelude/color.h"

#undef Create
namespace omega {

typedef unsigned hfont;
typedef std::vector<unsigned> FontLetterWidths;  // defined in two places -- bad

class Renderer {
 public:
  Renderer() : default_font_(0) {}
  virtual ~Renderer() {}

 public:
  virtual void set_default_font(hfont font) { default_font_ = font; }
  virtual hfont default_font() const { return default_font_; }

 public:
  // Using X at the end because CreateFontA is defined as CreateFont
  virtual hfont BuildFont(const char* const name, unsigned height,
                          unsigned weight, unsigned flags,
                          FontLetterWidths* letter_widths) = 0;
  virtual void DestroyFont(omega::hfont font) = 0;
  virtual void SetColor(int r, int g, int b, int a) = 0;
  virtual void SetColor(const pre::Color& color) {
    SetColor(color.r, color.g, color.b, color.a);
  }
  virtual void RenderText(omega::hfont font, float x, float y,
                          const char* const text) = 0;
  virtual void RenderLine(float x, float y, float x2, float y2,
                          float line_width) = 0;
  virtual void RenderQuad(float x, float y, float w, float h) = 0;
  virtual void RenderQuadLine(float x, float y, float w, float h,
                              float line_width) = 0;
  virtual void RenderPolygon(float vertices[][2], unsigned num_points) = 0;
  virtual void RenderPolyline(float vertices[][2], unsigned num_points,
                              float line_width) = 0;
  virtual void RenderCircle(float center_x, float center_y, float radius) = 0;
  virtual void RenderCircleLine(float center_x, float center_y, float radius,
                                float line_width) = 0;
  virtual void RenderImage(float x, float y, float w, float h, unsigned flags,
                           const std::byte* const image) = 0;
  virtual void StartRendering() = 0;
  virtual void EndRendering() = 0;

 private:
  hfont default_font_;
};

#define OPEN_RENDERER_INTERFACE(renderer)                                    \
  class renderer : public omega::Renderer {                                  \
   public:                                                                   \
    virtual omega::hfont BuildFont(const char* const name, unsigned height,  \
                                   unsigned weight, unsigned flags,          \
                                   omega::FontLetterWidths* letter_widths);  \
    virtual void DestroyFont(omega::hfont font);                             \
    virtual void SetColor(int r, int g, int b, int a);                       \
    virtual void RenderText(omega::hfont font, float abs_x, float abs_y,     \
                            const char* const text);                         \
    virtual void RenderLine(float abs_x, float abs_y, float abs_x2,          \
                            float abs_y2, float line_width);                 \
    virtual void RenderQuad(float abs_x, float abs_y, float abs_w,           \
                            float abs_h);                                    \
    virtual void RenderQuadLine(float abs_x, float abs_y, float abs_w,       \
                                float abs_h, float line_width);              \
    virtual void RenderPolygon(float vertices[][2], unsigned num_points);    \
    virtual void RenderPolyline(float vertices[][2], unsigned num_points,    \
                                float line_width);                           \
    virtual void RenderCircle(float center_x, float center_y, float radius); \
    virtual void RenderCircleLine(float center_x, float center_y,            \
                                  float radius, float line_width);           \
    virtual void RenderImage(float abs_x, float abs_y, float abs_w,          \
                             float abs_h, unsigned flags,                    \
                             const byte* const image);                       \
    virtual void StartRendering();                                           \
    virtual void EndRendering();

#define CLOSE_INTERFACE \
  }                     \
  ;

}  // namespace omega
