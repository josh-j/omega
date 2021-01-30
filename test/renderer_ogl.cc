#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include <cmath>

#include "prelude/common.h"
#include "renderer_ogl.h"

//#define _WIN64

namespace omega_test {

omega::hfont RendererOGL::BuildFont(const char* const name, unsigned height,
                                    unsigned weight, unsigned flags,
                                    omega::FontLetterWidths* letter_widths) {
  /*# if defined(__APPLE__) || defined(MACOSX)
    CGLContextObj curCGLContext = CGLGetCurrentContext();
    CGLShareGroupObj curCGLShareGroup = CGLGetShareGroup(curCGLContext);

    cl_context_properties properties[] = {
        CL_CONTEXT_PROPERTY_USE_CGL_SHAREGROUP_APPLE,
        (cl_context_properties)curCGLShareGroup, 0};
  #elif defined WIN32
    cl_context_properties properties[] = {
        CL_GL_CONTEXT_KHR,
        (cl_context_properties)wglGetCurrentContext(),
        CL_WGL_HDC_KHR,
        (cl_context_properties)wglGetCurrentDC(),
        CL_CONTEXT_PLATFORM,
        (cl_context_properties)(platforms[0])(),
        0};
  #else
    cl_context_properties properties[] = {
        CL_GL_CONTEXT_KHR,
        (cl_context_properties)glXGetCurrentContext(),
        CL_GLX_DISPLAY_KHR,
        (cl_context_properties)glXGetCurrentDisplay(),
        CL_CONTEXT_PLATFORM,
        (cl_context_properties)(platforms[0])(),
        0};
  #endif

    HDC hdc = wglGetCurrentDC();
    omega::hfont glFont = glGenLists(256);
    HFONT font =
        ::CreateFontA(-MulDiv(height, GetDeviceCaps(hdc, LOGPIXELSY), 72), 0, 0,
                      0, weight, 0, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
                      CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH,
  name);

    HFONT oldFont = (HFONT)SelectObject(hdc, font);

    wglUseFontBitmapsA(hdc, 0, 256, glFont);

    if (letter_widths) {
      SIZE s = {0, 0};
      char letter[2] = {0, 0};

      for (unsigned i = 0; i < 255; ++i) {
        letter[0] = i;
        GetTextExtentPoint32A(hdc, letter, 1, &s);
        //(*letter_widths)[i] = s.cx;
  letter_widths->push_back(s.cx);
}
}

SelectObject(hdc, oldFont);
DeleteObject(font);

return glFont;
*/
  return 0;
}

void RendererOGL::DestroyFont(omega::hfont font) { glDeleteLists(font, 256); }

void RendererOGL::SetColor(int r, int g, int b, int a) {
  glColor4ub(r, g, b, a);
}

void RendererOGL::RenderText(omega::hfont font, float x, float y,
                             const char* const text) {
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glDisable(GL_TEXTURE_2D);
  glListBase(font);
  glRasterPos2f(x, y);
  glCallLists(static_cast<GLsizei>(strlen(text)), GL_UNSIGNED_BYTE, text);
  glEnable(GL_TEXTURE_2D);
}

void RendererOGL::RenderLine(float x, float y, float x2, float y2,
                             float line_width) {
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glDisable(GL_TEXTURE_2D);
  glHint(GL_LINE_SMOOTH_HINT, GL_FASTEST);
  glEnable(GL_LINE_SMOOTH);
  glLineWidth(line_width);
  glBegin(GL_LINES);
  glVertex2f(x, y);
  glVertex2f(x2, y2);
  glEnd();
  glEnable(GL_TEXTURE_2D);
}

void RendererOGL::RenderQuad(float x, float y, float w, float h) {
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glDisable(GL_TEXTURE_2D);
  glBegin(GL_QUADS);
  glVertex2f(x, y);
  glVertex2f(x + w, y);
  glVertex2f(x + w, y + h);
  glVertex2f(x, y + h);
  glEnd();
  glEnable(GL_TEXTURE_2D);
}

void RendererOGL::RenderQuadLine(float x, float y, float w, float h,
                                 float line_width) {
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glDisable(GL_TEXTURE_2D);
  glBegin(GL_QUADS);  // top
  glVertex2f(x, y);
  glVertex2f(x + w, y);
  glVertex2f(x + w, y + line_width);
  glVertex2f(x, y + line_width);
  glEnd();

  glBegin(GL_QUADS);  // right
  glVertex2f(x + w - line_width, y + line_width);
  glVertex2f(x + w, y + line_width);
  glVertex2f(x + w, y + h - line_width);
  glVertex2f(x + w - line_width, y + h - line_width);
  glEnd();

  glBegin(GL_QUADS);  // bottom
  glVertex2f(x, y + h - line_width);
  glVertex2f(x + w, y + h - line_width);
  glVertex2f(x + w, y + h);
  glVertex2f(x, y + h);
  glEnd();

  glBegin(GL_QUADS);
  glVertex2f(x, y + line_width);
  glVertex2f(x + line_width, y + line_width);
  glVertex2f(x + line_width, y + h - line_width);
  glVertex2f(x, y + h - line_width);
  glEnd();
  glEnable(GL_TEXTURE_2D);

  // glDisable(GL_TEXTURE_2D);
  // glLineWidth(line_width);
  // glBegin(GL_LINE_LOOP);
  // glVertex2f(x + line_width, y); // top left
  // glVertex2f(x + w, y + line_width); // top right
  // glVertex2f(x + w, y + h - line_width); // bottom right
  // glVertex2f(x + line_width, y + h); // bottom left

  ////glVertex2f(x, y);
  ////glVertex2f(x + w, y);
  ////glVertex2f(x + w, y + h);
  ////glVertex2f(x, y + h);

  ////glVertex2f(x, y); // top left
  ////glVertex2f(x + w, y + line_width); // top right
  ////glVertex2f(x + w, y + h - line_width); // bottom right
  ////glVertex2f(x, y + h); // bottom left
  // glEnd();
  // glEnable(GL_TEXTURE_2D);
}

void RendererOGL::RenderPolygon(float vertices[][2], unsigned num_points) {
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glDisable(GL_TEXTURE_2D);
  glBegin(GL_TRIANGLE_FAN);
  for (unsigned i = 0; i < num_points; ++i) {
    glVertex2d(vertices[i][0], vertices[i][1]);
  }
  glEnd();
  glEnable(GL_TEXTURE_2D);
}

void RendererOGL::RenderPolyline(float vertices[][2], unsigned num_points,
                                 float line_width) {
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glDisable(GL_TEXTURE_2D);
  glLineWidth(line_width);
  glBegin(GL_LINE_STRIP);
  for (unsigned i = 0; i < num_points; ++i) {
    glVertex2d(vertices[i][0], vertices[i][1]);
  }
  glEnd();
  glEnable(GL_TEXTURE_2D);
}

void RendererOGL::RenderCircle(float center_x, float center_y, float radius) {
  // credits: http://slabode.exofire.net/circle_draw.shtml (fast circle, no cos
  // or sin) can still be improved

  static const float num_segments = 20.0f;
  static const float theta = pre::kTauFlt / num_segments;
  static const float c = cosf(theta);  // precalculate the sine and cosine
  static const float s = sinf(theta);

  float t;
  float x = radius;  // we start at angle = 0
  float y = 0;

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glDisable(GL_TEXTURE_2D);
  glBegin(GL_TRIANGLE_FAN);
  for (int ii = 0; ii < num_segments; ii++) {
    glVertex2f(x + center_x, y + center_y);  // output vertex
    // apply the rotation matrix
    t = x;
    x = c * x - s * y;
    y = s * t + c * y;
  }
  glEnd();
  glEnable(GL_TEXTURE_2D);
}

void RendererOGL::RenderCircleLine(float center_x, float center_y, float radius,
                                   float line_width) {
  // credits: http://slabode.exofire.net/circle_draw.shtml (fast circle, no cos
  // or sin) can still be improved
  static const float num_segments = 20.0f;
  static const float theta = pre::kTauFlt / num_segments;
  static const float c = cosf(theta);  // precalculate the sine and cosine
  static const float s = sinf(theta);

  float t;
  float x = radius;  // we start at angle = 0
  float y = 0;

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glDisable(GL_TEXTURE_2D);
  glLineWidth(line_width);
  glBegin(GL_LINE_LOOP);  // outline
  for (int ii = 0; ii < num_segments; ii++) {
    glVertex2f(x + center_x, y + center_y);  // output vertex
    // apply the rotation matrix
    t = x;
    x = c * x - s * y;
    y = s * t + c * y;
  }
  glEnd();
  glEnable(GL_TEXTURE_2D);
}

void RendererOGL::RenderImage(float x, float y, float w, float h,
                              unsigned flags, const std::byte* const image) {
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glDisable(GL_TEXTURE_2D);

  glRasterPos2d(x, y);
  glDrawPixels((GLsizei)w, (GLsizei)h, GL_RGBA, GL_UNSIGNED_BYTE, image);

  glEnable(GL_TEXTURE_2D);
}

void RendererOGL::StartRendering() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RendererOGL::EndRendering() {}

}  // namespace omega_test
