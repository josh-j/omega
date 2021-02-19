#include "font_manager.h"
#include "renderer.h"

namespace omega {

FontManager::FontManager() : renderer_(nullptr) {

}

FontManager::~FontManager() {
  Dispose();
}

Font* FontManager::Build(const std::string& face, uint height, uint weight, uint flags) {
  SAFE_ASSERT_RETVAL(renderer_ != nullptr, nullptr);
  Font* font = Find(face, height, weight, flags);
  if (font != nullptr) {
    font->num_owners_ += 1;
    return font;
  }

  font = new Font;
  font->renderer_ = renderer_;
  font->face_ = face;
  font->height_ = height;
  font->weight_ = weight;
  font->flags_ = flags;
  font->handle_ = renderer_->BuildFont(face.c_str(), height, weight, flags, &font->letter_widths_);
  font->num_owners_ = 1;
  font->height_ += 2; // TODO is this needed?
  fonts_.push_back(font);
  return font;
}

void FontManager::Destroy(hfont handle) {
  SAFE_ASSERT(renderer_ != nullptr);
  Font* find = Find(handle);

  if (find != nullptr) {
    if (find->num_owners_ <= 1) {
      renderer_->DestroyFont(handle);

      for (Fonts::iterator it = fonts_.begin(); it != fonts_.end(); ++it) {
        if (find == *it) {
          fonts_.erase(it);
          break;
        }
      }

      delete find;
    } else {
      find->num_owners_ -= 1;
    }
  }
}

Font* FontManager::Find(hfont font) const {
  for (Fonts::const_iterator iter = fonts_.begin(); iter != fonts_.end(); ++iter) {
    if ((*iter)->handle() == font) {
        return *iter;
    }
  }
  return nullptr;
}

Font* FontManager::Find(const std::string& face, uint height, uint weight, uint flags) const {
  Font* font;
  for (Fonts::const_iterator iter = fonts_.begin(); iter != fonts_.end(); ++iter) {
    font = *iter;
    if (font->face() == face &&
        font->height() == height &&
        font->weight() == weight &&
        font->flags() == flags) {
        return font;
    }
  }
  return nullptr;
}

void FontManager::Dispose() {
  for (Fonts::iterator it = fonts_.begin(); it != fonts_.end(); ++it) {
    if (renderer_ != nullptr)
      renderer_->DestroyFont((*it)->handle());
    delete *it;
  }
  fonts_.clear();
}

void FontManager::set_renderer(Renderer* renderer) {
  renderer_ = renderer;
}

} // namespace omega
