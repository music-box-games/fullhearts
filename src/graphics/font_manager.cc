#include "font_manager.hpp"

namespace waifuengine
{
  namespace graphics
  {
    font_manager::font_manager() {}
    font_manager::~font_manager() {}

    std::optional<std::shared_ptr<font>> font_manager::load_font(std::string name, std::string filename)
    {
      std::shared_ptr<font> fptr = std::shared_ptr<font>(new font(name));
      if(fptr->load(filename))
      {
        fonts_[fptr->name()] = fptr;
        return fptr;
      }
      else
      {
        return {};
      }
    }

    void font_manager::unload_font(std::string filename)
    {
      fonts_.erase(filename);
    }

    std::optional<std::shared_ptr<font>> font_manager::get_font(std::string filename)
    {
      if(has_font(filename))
      {
        return fonts_.at(filename);
      }
      else
      {
        return {};
      }
    }

    bool font_manager::has_font(std::string filename) const
    {
      return fonts_.count(filename);
    }

    int font_manager::count() const
    {
      return fonts_.size();
    }
  }
}