#pragma once

#include <string>
#include <cstdio>
#include <cstdlib>
#include <algorithm>

namespace pre {

class Color {
 public:
  Color() : colorcode(0xFFFFFFFF) {}
  Color(unsigned long rgba) { set(rgba); }
  Color(int r, int g, int b) { set(r, g, b); }
  Color(int r, int g, int b, int a) { set(r, g, b, a); }
  Color(float r, float g, float b) { set(r, g, b); }
  Color(float r, float g, float b, float a) { set(r, g, b, a); }
  Color(const std::string& color) { set(color); }
  ~Color() {}

  void set(unsigned long rgba) { colorcode = rgba; }

  void set(int r, int g, int b)
    { Color::r = (unsigned char)r; Color::g = (unsigned char)g; Color::b = (unsigned char)b; Color::a = 255; }

  void set(int r, int g, int b, int a)
    { Color::r = (unsigned char)r; Color::g = (unsigned char)g; Color::b = (unsigned char)b; Color::a = (unsigned char)a; }

  void set(float r, float g, float b)
    { Color::r = (unsigned char)(r * 255.0f); Color::g = (unsigned char)(g * 255.0f); Color::b = (unsigned char)(b * 255.0f); Color::a = 255; }

  void set(float r, float g, float b, float a)
    { Color::r = (unsigned char)(r * 255.0f); Color::g = (unsigned char)(g * 255.0f); Color::b = (unsigned char)(b * 255.0f); Color::a = (unsigned char)(a * 255.0f); }

  void set(const std::string& text) { // handles many formats r,g,b r g b a colorcode
    if (text.empty()) return;
    a = (unsigned char)255; // if A isn't set in text

    if (text[0] == '0' && (text[1] == 'x' || text[1] == 'X')) {
      sscanf(text.c_str() + 2, "%lx", &colorcode);
      return;
    }

    bool separated = false;
    std::string buffer = "";
    for (::size_t i = 0, x = 0; x < 4; ++i) { // does r g b a format
      switch (text[i]) {
      case ',': case ' ': case '\t':
        separated = true;
      case '\0':
        switch (x) {
        case 0: r = (unsigned char)atoi(buffer.c_str()); break;
        case 1: g = (unsigned char)atoi(buffer.c_str()); break;
        case 2: b = (unsigned char)atoi(buffer.c_str()); break;
        case 3: a = (unsigned char)atoi(buffer.c_str()); break;
        }
        ++x;
        buffer.clear();
        break;
        
      default:
        buffer += text[i];
      }

      if (text[i] == '\0') break;
    }

    if (!separated) { // does colorcode format if not r g b a
      sscanf(text.c_str(), "%lx", &colorcode);
    }
  }

  void blend(const Color& to, float scale) {
    //float s2 = 1.0f - scale;
    //r = (r * s2) + (to.r * scale);
    //g = (g * s2) + (to.g * scale);
    //b = (b * s2) + (to.b * scale);
    //a = (a * s2) + (to.a * scale);
  }

  void lighten(float scale) {
    blend(Color(255, 255, 255, a), scale);
  }

  void darken(float scale) {
    blend(Color(0, 0, 0, a), scale);
  }

  void adjust_contrast(float contrast) {
    //r = 0.5f + contrast * (r - 0.5f);
    //g = 0.5f + contrast * (g - 0.5f);
    //b = 0.5f + contrast * (b - 0.5f);
    //a = 0.5f + contrast * (a - 0.5f);
  }

  void adjust_saturation(float saturation) {
    //float grey = r * 0.2125f + g * 0.7154f + b * 0.0721f;    
    //r = grey + saturation * (r - grey);
    //g = grey + saturation * (g - grey);
    //b = grey + saturation * (b - grey);
    //a = grey + saturation * (a - grey);
  }

  //void adjust_brightness(float brightness) {
  //  //r*0.33f;
  //  //g*0.59f'
  //  //b*0.11f;
  //}

  void invert() {

  }
 
  // Operators
  Color& operator()(unsigned long rgba) { set(rgba); return *this; }
  Color& operator()(int r, int g, int b, int a = 255) { set(r, g, b, a); return *this; }
  Color& operator()(float r, float g, float b, float a = 1.0) { set(r, g, b, a); return *this; }
  Color& operator()(const std::string& text) { set(text); return *this; }
  operator unsigned long() const { return colorcode; }
  operator unsigned long() { return colorcode; }

  void set_percent_r(float r) { Color::r = (unsigned char)(r * 255.0f); }
  void set_percent_g(float g) { Color::g = (unsigned char)(g * 255.0f); }
  void set_percent_b(float b) { Color::b = (unsigned char)(b * 255.0f); }
  void set_percent_a(float a) { Color::a = (unsigned char)(a * 255.0f); }

  // Properties
  unsigned char red() const { return r; }
  unsigned char green() const { return g; }
  unsigned char blue() const { return b; }
  unsigned char alpha() const { return a; }
  float redf() const { return r / 255.0f; }
  float greenf() const { return g / 255.0f; }
  float bluef() const { return r / 255.0f; }
  float alphaf() const { return r / 255.0f; }

  enum {
    kAliceBlue            = 0xFFF0F8FF,
    kAntiqueWhite         = 0xFFFAEBD7,
    kAqua                 = 0xFF00FFFF,
    kAquamarine           = 0xFF7FFFD4,
    kAzure                = 0xFFF0FFFF,
    kBeige                = 0xFFF5F5DC,
    kBisque               = 0xFFFFE4C4,
    kBlack                = 0xFF000000,
    kBlanchedAlmond       = 0xFFFFEBCD,
    kBlue                 = 0xFF0000FF,
    kBlueViolet           = 0xFF8A2BE2,
    kBrown                = 0xFFA52A2A,
    kBurlyWood            = 0xFFDEB887,
    kCadetBlue            = 0xFF5F9EA0,
    kChartreuse           = 0xFF7FFF00,
    kChocolate            = 0xFFD2691E,
    kCoral                = 0xFFFF7F50,
    kCornflowerBlue       = 0xFF6495ED,
    kCornsilk             = 0xFFFFF8DC,
    kCrimson              = 0xFFDC143C,
    kCyan                 = 0xFF00FFFF,
    kDarkBlue             = 0xFF00008B,
    kDarkCyan             = 0xFF008B8B,
    kDarkGoldenrod        = 0xFFB8860B,
    kDarkGray             = 0xFFA9A9A9,
    kDarkGreen            = 0xFF006400,
    kDarkKhaki            = 0xFFBDB76B,
    kDarkMagenta          = 0xFF8B008B,
    kDarkOliveGreen       = 0xFF556B2F,
    kDarkOrange           = 0xFFFF8C00,
    kDarkOrchid           = 0xFF9932CC,
    kDarkRed              = 0xFF8B0000,
    kDarkSalmon           = 0xFFE9967A,
    kDarkSeaGreen         = 0xFF8FBC8B,
    kDarkSlateBlue        = 0xFF483D8B,
    kDarkSlateGray        = 0xFF2F4F4F,
    kDarkTurquoise        = 0xFF00CED1,
    kDarkViolet           = 0xFF9400D3,
    kDeepPink             = 0xFFFF1493,
    kDeepSkyBlue          = 0xFF00BFFF,
    kDimGray              = 0xFF696969,
    kDodgerBlue           = 0xFF1E90FF,
    kFirebrick            = 0xFFB22222,
    kFloralWhite          = 0xFFFFFAF0,
    kForestGreen          = 0xFF228B22,
    kFuchsia              = 0xFFFF00FF,
    kGainsboro            = 0xFFDCDCDC,
    kGhostWhite           = 0xFFF8F8FF,
    kGold                 = 0xFFFFD700,
    kGoldenrod            = 0xFFDAA520,
    kGray                 = 0xFF808080,
    kGreen                = 0xFF008000,
    kGreenYellow          = 0xFFADFF2F,
    kHoneydew             = 0xFFF0FFF0,
    kHotPink              = 0xFFFF69B4,
    kIndianRed            = 0xFFCD5C5C,
    kIndigo               = 0xFF4B0082,
    kIvory                = 0xFFFFFFF0,
    kKhaki                = 0xFFF0E68C,
    kLavender             = 0xFFE6E6FA,
    kLavenderBlush        = 0xFFFFF0F5,
    kLawnGreen            = 0xFF7CFC00,
    kLemonChiffon         = 0xFFFFFACD,
    kLightBlue            = 0xFFADD8E6,
    kLightCoral           = 0xFFF08080,
    kLightCyan            = 0xFFE0FFFF,
    kLightGoldenrodYellow = 0xFFFAFAD2,
    kLightGray            = 0xFFD3D3D3,
    kLightGreen           = 0xFF90EE90,
    kLightPink            = 0xFFFFB6C1,
    kLightSalmon          = 0xFFFFA07A,
    kLightSeaGreen        = 0xFF20B2AA,
    kLightSkyBlue         = 0xFF87CEFA,
    kLightSlateGray       = 0xFF778899,
    kLightSteelBlue       = 0xFFB0C4DE,
    kLightYellow          = 0xFFFFFFE0,
    kLime                 = 0xFF00FF00,
    kLimeGreen            = 0xFF32CD32,
    kLinen                = 0xFFFAF0E6,
    kMagenta              = 0xFFFF00FF,
    kMaroon               = 0xFF800000,
    kMediumAquamarine     = 0xFF66CDAA,
    kMediumBlue           = 0xFF0000CD,
    kMediumOrchid         = 0xFFBA55D3,
    kMediumPurple         = 0xFF9370DB,
    kMediumSeaGreen       = 0xFF3CB371,
    kMediumSlateBlue      = 0xFF7B68EE,
    kMediumSpringGreen    = 0xFF00FA9A,
    kMediumTurquoise      = 0xFF48D1CC,
    kMediumVioletRed      = 0xFFC71585,
    kMidnightBlue         = 0xFF191970,
    kMintCream            = 0xFFF5FFFA,
    kMistyRose            = 0xFFFFE4E1,
    kMoccasin             = 0xFFFFE4B5,
    kNavajoWhite          = 0xFFFFDEAD,
    kNavy                 = 0xFF000080,
    kOldLace              = 0xFFFDF5E6,
    kOlive                = 0xFF808000,
    kOliveDrab            = 0xFF6B8E23,
    kOrange               = 0xFFFFA500,
    kOrangeRed            = 0xFFFF4500,
    kOrchid               = 0xFFDA70D6,
    kPaleGoldenrod        = 0xFFEEE8AA,
    kPaleGreen            = 0xFF98FB98,
    kPaleTurquoise        = 0xFFAFEEEE,
    kPaleVioletRed        = 0xFFDB7093,
    kPapayaWhip           = 0xFFFFEFD5,
    kPeachPuff            = 0xFFFFDAB9,
    kPeru                 = 0xFFCD853F,
    kPink                 = 0xFFFFC0CB,
    kPlum                 = 0xFFDDA0DD,
    kPowderBlue           = 0xFFB0E0E6,
    kPurple               = 0xFF800080,
    kRed                  = 0xFFFF0000,
    kRosyBrown            = 0xFFBC8F8F,
    kRoyalBlue            = 0xFF4169E1,
    kSaddleBrown          = 0xFF8B4513,
    kSalmon               = 0xFFFA8072,
    kSandyBrown           = 0xFFF4A460,
    kSeaGreen             = 0xFF2E8B57,
    kSeaShell             = 0xFFFFF5EE,
    kSienna               = 0xFFA0522D,
    kSilver               = 0xFFC0C0C0,
    kSkyBlue              = 0xFF87CEEB,
    kSlateBlue            = 0xFF6A5ACD,
    kSlateGray            = 0xFF708090,
    kSnow                 = 0xFFFFFAFA,
    kSpringGreen          = 0xFF00FF7F,
    kSteelBlue            = 0xFF4682B4,
    kTan                  = 0xFFD2B48C,
    kTeal                 = 0xFF008080,
    kThistle              = 0xFFD8BFD8,
    kTomato               = 0xFFFF6347,
    kTransparent          = 0x00FFFFFF,
    kTurquoise            = 0xFF40E0D0,
    kViolet               = 0xFFEE82EE,
    kWheat                = 0xFFF5DEB3,
    kWhite                = 0xFFFFFFFF,
    kWhiteSmoke           = 0xFFF5F5F5,
    kYellow               = 0xFFFFFF00,
    kYellowGreen          = 0xFF9ACD32
  };

 public:
  union {
    unsigned long colorcode;
    struct {
      unsigned char b, g, r, a;
    };
  };
};

static const pre::Color color_white(255, 255, 255);
static const pre::Color color_black(0, 0, 0);

} // namespace pre
