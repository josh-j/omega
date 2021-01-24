#include "brush.h"

#include "state.h"

namespace omega {
namespace Brush {

void Text(hfont font, const Point& point, const Color& color,
          const std::string& text) {
  SAFE_ASSERT(s.renderer != nullptr);
  s.renderer->SetColor(color.r, color.g, color.b, color.a);
  s.renderer->RenderText(font, point.x, point.y, text.c_str());
}

void Rectangle(const Point& pos, const Size& size, const Color& color) {
  SAFE_ASSERT(s.renderer != nullptr);
  s.renderer->SetColor(color.r, color.g, color.b, color.a);
  s.renderer->RenderQuad(pos.x, pos.y, size.w, size.h);
}

void RoundedRect(const Point &pos, const Size &size, const Color &color,
                 float radius) {
  SAFE_ASSERT(s.renderer != nullptr);
  float x = pos.x;
  float y = pos.y;
  float w = size.w;
  float h = size.h;

  x += 1.0f;
  y += 1.0f;
  w -= 2.0f;
  h -= 2.0f;

  float _x = x + radius, _y = y + radius, i = 0.0f;
  uint points = 0;

  static float condition1 = 0.5f * pre::kPiFlt;
  static float condition2 = 1.5f * pre::kPiFlt;
  static float condition3 = 2.0f * pre::kPiFlt;
  float vertices[32][2];

  for (i = pre::kPiFlt; i <= condition2; i += 0.50) {
    vertices[points][0] = radius * cos(i) + _x;
    vertices[points][1] = radius * sin(i) + _y;
    ++points;
  }

  _x = x + w - radius;

  for (i = condition2; i <= condition3; i += 0.50) {
    vertices[points][0] = radius * cos(i) + _x;
    vertices[points][1] = radius * sin(i) + _y;
    ++points;
  }

  _y = y + h - radius;

  for (i = 0.0f; i <= condition1; i += 0.50) {
    vertices[points][0] = radius * cos(i) + _x;
    vertices[points][1] = radius * sin(i) + _y;
    ++points;
  }

  _x = x + radius;

  for (i = condition1; i <= pre::kPiFlt; i += 0.50) {
    vertices[points][0] = radius * cos(i) + _x;
    vertices[points][1] = radius * sin(i) + _y;
    ++points;
  }

  s.renderer->SetColor(color.r, color.g, color.b, color.a);
  s.renderer->RenderPolygon(vertices, points);
}

void Border(const Point& pos, const Size& size, const Color& color,
            float border_width) {
  SAFE_ASSERT(s.renderer != nullptr);

  s.renderer->SetColor(color.r, color.g, color.b, color.a);
  s.renderer->RenderQuadLine(pos.x, pos.y, size.w, size.h, border_width);
}

void Border(const Point& pos, const Size& size, const Color& color,
            float border_width, float offset) {
  SAFE_ASSERT(s.renderer != nullptr);

  float x = pos.x;
  float y = pos.y;
  float w = size.w;
  float h = size.h;

  if (offset != 0.0f) {
    x += offset;
    y += offset;
    w -= offset * 2.0f;
    h -= offset * 2.0f;
  }

  s.renderer->SetColor(color.r, color.g, color.b, color.a);
  s.renderer->RenderQuadLine(x, y, w, h, border_width);
}

void RoundedBorder(const Point& pos, const Size& size, const Color& color,
                   float border_width, float radius) {
  SAFE_ASSERT(s.renderer != nullptr);

  float x = pos.x;
  float y = pos.y;
  float w = size.w;
  float h = size.h;

  radius += 2.0f;

  float _x = x + radius, _y = y + radius, i = 0.0f;
  uint points = 0;

  static float condition1 = 0.5f * pre::kPiFlt;
  static float condition2 = 1.5f * pre::kPiFlt;
  static float condition3 = 2.0f * pre::kPiFlt;
  float vertices[32][2];

  for (i = pre::kPiFlt; i <= condition2; i += 0.50) {
    vertices[points][0] = radius * cos(i) + _x;
    vertices[points][1] = radius * sin(i) + _y;
    ++points;
  }

  _x = x + w - radius;

  for (i = condition2; i <= condition3; i += 0.50) {
    vertices[points][0] = radius * cos(i) + _x;
    vertices[points][1] = radius * sin(i) + _y;
    ++points;
  }

  _y = y + h - radius;

  for (i = 0.0f; i <= condition1; i += 0.50) {
    vertices[points][0] = radius * cos(i) + _x;
    vertices[points][1] = radius * sin(i) + _y;
    ++points;
  }

  _x = x + radius;

  for (i = condition1; i <= pre::kPiFlt; i += 0.50) {
    vertices[points][0] = radius * cos(i) + _x;
    vertices[points][1] = radius * sin(i) + _y;
    ++points;
  }

  s.renderer->SetColor(color.r, color.g, color.b, color.a);
  s.renderer->RenderPolyline(vertices, points, border_width);
}

void Bevel(const Point& pos, const Size& size, const Color& color,
           const Color& alt_color, float bevel_width, float alt_bevel_width,
           float offset) {
  SAFE_ASSERT(s.renderer != nullptr);

  float x = pos.x;
  float y = pos.y;
  float w = size.w;
  float h = size.h;

  if (offset != 0.0f) {
    x += offset;
    y += offset;
    w -= offset * 2.0f;
    h -= offset * 2.0f;
  }

  // m_renderer->RenderQuad(x, y, bevel_width, h);
  // m_renderer->RenderQuad(x + bevel_width, y, w - (bevel_width +
  // alt_bevel_width), bevel_width); popColor();

  // m_renderer->RenderQuad(x + bevel_width, y + h - alt_bevel_width, w -
  // bevel_width, alt_bevel_width); m_renderer->RenderQuad(x + w -
  // alt_bevel_width, y, alt_bevel_width, h - alt_bevel_width); popColor();

  s.renderer->SetColor(color.r, color.g, color.b, color.a);
  s.renderer->RenderQuad(x, y, bevel_width, h);  // left
  s.renderer->RenderQuad(x + bevel_width, y, w - alt_bevel_width,
                         bevel_width);  // top

  s.renderer->SetColor(alt_color.r, alt_color.g, alt_color.b, alt_color.a);
  s.renderer->RenderQuad(x + bevel_width, y + h - alt_bevel_width,
                         w - alt_bevel_width, alt_bevel_width);  // bottom
  s.renderer->RenderQuad(x + w - alt_bevel_width, y + bevel_width,
                         alt_bevel_width,
                         h - bevel_width - alt_bevel_width);  // right

  // m_vertices[0][0] = x;
  // m_vertices[0][1] = y + h;

  // m_vertices[1][0] = x;
  // m_vertices[1][1] = y;d

  // m_vertices[2][0] = x + w;
  // m_vertices[2][1] = y;

  // m_renderer->renderPolyline(m_vertices, 3, line_width);
}

void RoundedBevel(const Point& pos, const Size& size, const Color& color,
                  const Color& alt_color, float bevel_width,
                  float alt_bevel_width, float offset, float radius) {
  SAFE_ASSERT(s.renderer != nullptr);

  float x = pos.x;
  float y = pos.y;
  float w = size.w;
  float h = size.h;

  radius += 2.0f;
  x -= 1.0f + offset;
  y -= 1.0f + offset;
  w += 2.0f + offset * 2.0f;
  h += 2.0f + offset * 2.0f;

  float _x = x + radius;
  float _y = y + radius;
  float i = 0.0f;
  uint points = 0;

  static float condition1 = 0.5f * pre::kPiFlt;
  static float condition2 = 1.5f * pre::kPiFlt;
  static float condition3 = 2.0f * pre::kPiFlt;
  float vertices[32][2];

  for (i = pre::kPiFlt; i <= condition2; i += 0.50) {
    vertices[points][0] = radius * cos(i) + _x;
    vertices[points][1] = radius * sin(i) + _y;
    ++points;
  }

  _x = x + w - radius;

  for (i = condition2; i <= condition3; i += 0.50) {
    vertices[points][0] = radius * cos(i) + _x;
    vertices[points][1] = radius * sin(i) + _y;
    ++points;
  }

  s.renderer->SetColor(color.r, color.g, color.b, color.a);
  s.renderer->RenderPolyline(vertices, points, bevel_width);
  points = 0;

  _y = y + h - radius;

  for (i = 0.0f; i <= condition1; i += 0.50) {
    vertices[points][0] = radius * cos(i) + _x;
    vertices[points][1] = radius * sin(i) + _y;
    ++points;
  }

  _x = x + radius;

  for (i = condition1; i <= pre::kPiFlt; i += 0.50) {
    vertices[points][0] = radius * cos(i) + _x;
    vertices[points][1] = radius * sin(i) + _y;
    ++points;
  }

  s.renderer->SetColor(alt_color.r, alt_color.g, alt_color.b, alt_color.a);
  s.renderer->RenderPolyline(vertices, points, alt_bevel_width);
}

void PanelBackground(const Rect& rect, const Color& color_background,
                     float padding, bool is_rounded) {
  PanelBackground(rect.pos(), rect.size(), color_background, padding,
                  is_rounded);
}

void PanelBackground(const Point& pos, const Size& size,
                     const Color& color_background, float padding,
                     bool is_rounded) {
  if (is_rounded) {
    RoundedRect(pos, size, color_background, padding);
  } else {
    Rectangle(pos, size, color_background);
  }
}

void PanelFrame(const Rect& rect, const Color& color_border,
                const Color& color_bevel, const Color& color_bevelalt,
                float border_size, float bevel_size, float bevelalt_size,
                float border_padding, bool is_rounded, bool is_bordered,
                bool is_beveled, bool is_bevel_outside,
                bool is_bevel_reversed) {
  PanelFrame(rect.pos(), rect.size(), color_border, color_bevel, color_bevelalt,
             border_size, bevel_size, bevelalt_size, border_padding, is_rounded,
             is_bordered, is_beveled, is_bevel_outside, is_bevel_reversed);
}

void PanelFrame(const Point& pos, const Size& size, const Color& color_border,
                const Color& color_bevel, const Color& color_bevelalt,
                float border_size, float bevel_size, float bevelalt_size,
                float border_padding, bool is_rounded, bool is_bordered,
                bool is_beveled, bool is_bevel_outside,
                bool is_bevel_reversed) {
  if (is_rounded) {
    if (is_beveled) {
      float offset = is_bevel_outside ? -border_size : border_size;
      RoundedBevel(pos, size,
                   (is_bevel_reversed ? color_bevelalt : color_bevel),
                   (is_bevel_reversed ? color_bevel : color_bevelalt),
                   bevel_size, bevelalt_size, offset, border_padding);
    }

    if (is_bordered) {
      RoundedBorder(pos, size, color_border, border_size, border_padding);
    }
  } else {
    if (is_beveled) {
      float offset = is_bevel_outside ? 0.0f : border_size;
      Bevel(pos, size, (is_bevel_reversed ? color_bevelalt : color_bevel),
            (is_bevel_reversed ? color_bevel : color_bevelalt), bevel_size,
            bevelalt_size, offset);
    }

    if (is_bordered) {
      float offset = 0.0f;
      if (is_bevel_outside)
        offset = bevelalt_size > bevel_size ? bevelalt_size : bevel_size;
      Border(pos, size, color_border, border_size, offset);
    }
  }
}

void Image(const Point& point, const std::string& name) {
  SAFE_ASSERT(s.renderer != nullptr);
}

void Cursor(const Point& point, CursorType cursor) {
  SAFE_ASSERT(s.renderer != nullptr);
  s.renderer->SetColor(255, 255, 255, 255);

  float x = point.x;
  float y = point.y;
  float vertices[32][2];

  switch (cursor) {
    case kCursorIBeam:
      s.renderer->RenderQuad(x, y - 6.0f, 1.0f, 12.0f);
      s.renderer->RenderQuad(x - 2.0f, y - 7.0f, 5.0f, 1.0f);
      s.renderer->RenderQuad(x - 2.0f, y + 6.0f, 5.0f, 1.0f);
      break;

    case kCursorCrosshair:
      s.renderer->RenderQuad(x - 8.0f, y - 1.0f, 6.0f, 2.0f);
      s.renderer->RenderQuad(x + 2.0f, y - 1.0f, 6.0f, 2.0f);

      s.renderer->RenderQuad(x - 1.0f, y - 8.0f, 2.0f, 6.0f);
      s.renderer->RenderQuad(x - 1.0f, y + 2.0f, 2.0f, 6.0f);
      break;

    case kCursorMove:
      vertices[0][0] = x - 10.0f;
      vertices[0][1] = y;

      vertices[1][0] = x - 6.0f;
      vertices[1][1] = y - 5.0f;

      vertices[2][0] = x - 6.0f;
      vertices[2][1] = y + 5.0f;

      s.renderer->RenderPolygon(vertices, 3);

      vertices[0][0] = x + 10.0f;
      vertices[0][1] = y;

      vertices[1][0] = x + 5.0f;
      vertices[1][1] = y - 5.0f;

      vertices[2][0] = x + 5.0f;
      vertices[2][1] = y + 5.0f;

      s.renderer->RenderPolygon(vertices, 3);

      vertices[0][0] = x;
      vertices[0][1] = y - 10.0f;

      vertices[1][0] = x - 5.0f;
      vertices[1][1] = y - 5.0f;

      vertices[2][0] = x + 5.0f;
      vertices[2][1] = y - 5.0f;

      s.renderer->RenderPolygon(vertices, 3);

      vertices[0][0] = x;
      vertices[0][1] = y + 10.0f;

      vertices[1][0] = x - 5.0f;
      vertices[1][1] = y + 5.0f;

      vertices[2][0] = x + 5.0f;
      vertices[2][1] = y + 5.0f;

      s.renderer->RenderPolygon(vertices, 3);
      break;

    case kCursorSouthEast:
    case kCursorNorthWest:
      vertices[0][0] = x - 7.0f;
      vertices[0][1] = y - 8.0f;

      vertices[1][0] = x - 7.0f;
      vertices[1][1] = y;

      vertices[2][0] = x;
      vertices[2][1] = y - 8.0f;

      s.renderer->RenderPolygon(vertices, 3);

      vertices[0][0] = x + 7.0f;
      vertices[0][1] = y + 7.0f;

      vertices[1][0] = x + 7.0f;
      vertices[1][1] = y;

      vertices[2][0] = x;
      vertices[2][1] = y + 7.0f;

      s.renderer->RenderPolygon(vertices, 3);
      break;

    case kCursorSouth:
    case kCursorNorth:
      vertices[0][0] = x;
      vertices[0][1] = y - 10.0f;

      vertices[1][0] = x - 5.0f;
      vertices[1][1] = y - 5.0f;

      vertices[2][0] = x + 5.0f;
      vertices[2][1] = y - 5.0f;

      s.renderer->RenderPolygon(vertices, 3);

      vertices[0][0] = x;
      vertices[0][1] = y + 10.0f;

      vertices[1][0] = x - 5.0f;
      vertices[1][1] = y + 5.0f;

      vertices[2][0] = x + 5.0f;
      vertices[2][1] = y + 5.0f;

      s.renderer->RenderPolygon(vertices, 3);
      break;

    case kCursorSouthWest:
    case kCursorNorthEast:
      vertices[0][0] = x + 7.0f;
      vertices[0][1] = y - 7.0f;

      vertices[1][0] = x + 7.0f;
      vertices[1][1] = y;

      vertices[2][0] = x;
      vertices[2][1] = y - 7.0f;

      s.renderer->RenderPolygon(vertices, 3);

      vertices[0][0] = x - 7.0f;
      vertices[0][1] = y + 8.0f;

      vertices[1][0] = x - 7.0f;
      vertices[1][1] = y;

      vertices[2][0] = x;
      vertices[2][1] = y + 8.0f;

      s.renderer->RenderPolygon(vertices, 3);
      break;

    case kCursorWest:
    case kCursorEast:
      vertices[0][0] = x - 10.0f;
      vertices[0][1] = y;

      vertices[1][0] = x - 5.0f;
      vertices[1][1] = y - 5.0f;

      vertices[2][0] = x - 5.0f;
      vertices[2][1] = y + 5.0f;

      s.renderer->RenderPolygon(vertices, 3);

      vertices[0][0] = x + 10.0f;
      vertices[0][1] = y;

      vertices[1][0] = x + 5.0f;
      vertices[1][1] = y - 6.0f;

      vertices[2][0] = x + 5.0f;
      vertices[2][1] = y + 6.0f;

      s.renderer->RenderPolygon(vertices, 3);
      break;

    case kCursorArrow:
    default:
      s.renderer->RenderQuad(x, y, 1.0f, 10.0f);
      s.renderer->RenderQuad(x + 1.0f, y + 1.0f, 1.0f, 8.0f);
      s.renderer->RenderQuad(x + 2.0f, y + 2.0f, 1.0f, 6.0f);
      s.renderer->RenderQuad(x + 3.0f, y + 3.0f, 1.0f, 6.0f);
      s.renderer->RenderQuad(x + 4.0f, y + 4.0f, 1.0f, 7.0f);
      s.renderer->RenderQuad(x + 5.0f, y + 5.0f, 1.0f, 2.0f);
      s.renderer->RenderQuad(x + 5.0f, y + 9.0f, 1.0f, 4.0f);
      s.renderer->RenderQuad(x + 6.0f, y + 6.0f, 1.0f, 1.0f);
      s.renderer->RenderQuad(x + 6.0f, y + 11.0f, 1.0f, 2.0f);
      break;
  }
}

}  // namespace Brush
}  // namespace omega
