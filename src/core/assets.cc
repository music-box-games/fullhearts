/******************************************************************************/
/*!
\file   assets.cc
\author Ryan Hanson
\par    email: iovita\@musicboxgames.net
\brief
  Data driven loading of assets

*/
/******************************************************************************/

#include <unordered_map>

#include <assets.hpp>
#include <utils.hpp>
#include <boost/tokenizer.hpp>
#include <boost/dll.hpp>
#include <text_image.hpp>

namespace waifuengine
{
namespace core
{
namespace text_assets
{
using tptr = std::shared_ptr<waifuengine::graphics::text_image>;

class text_bank
{
private:
  std::unordered_map<std::string, tptr> texts;

public:
  text_bank() {}
  ~text_bank() {}

  void load(std::string t)
  {
    auto f = waifuengine::core::font_assets::default_font();
    tptr ti = tptr(new waifuengine::graphics::text_image(t, f));
    texts[t] = ti;
  }

  void unload(std::string t)
  {
    texts.erase(t);
  }

  tptr get(std::string t)
  {
    if (texts.count(t) == 0)
    {
      load(t);
    }
    return texts[t];
  }
};

std::shared_ptr<text_bank> bank;

tptr get_text(std::string t)
{
  return bank->get(t);
}

void unload_text(std::string t)
{
  bank->unload(t);
}

void init()
{
  if (bank.use_count() == 0)
  {
    bank = std::shared_ptr<text_bank>(new text_bank());
  }
}

void shutdown()
{
  bank.reset();
}
} // namespace text_assets

namespace image_assets
{
using imgptr = std::shared_ptr<waifuengine::graphics::image>;

class image_bank
{
private:
  std::unordered_map<std::string, imgptr> images;

public:
  image_bank() {}
  ~image_bank() {}

  void load_image(std::string name, std::string file)
  {
    waifuengine::graphics::image *i = new waifuengine::graphics::image();
    i->load_file(file);
    images[name] = imgptr(i);
  }

  void remove_image(std::string name)
  {
    images.erase(name);
  }

  imgptr get(std::string name)
  {
    return (images.count(name)) ? images[name] : nullptr;
  }
};

static std::shared_ptr<image_bank> bank;

void load_images(std::string ilist)
{
  auto files = waifuengine::utils::parse_file_to_vector(ilist);
  // tokenize each string into name and file (file path is relative to executable).

  for (auto &s : files)
  {
    boost::char_separator<char> sep("|");
    boost::tokenizer<boost::char_separator<char>> tok(s, sep);
    // TODO: should be only 2 tokens, impl some sort of data validation.
    // get absolute path to file
    std::string path = utils::get_exe_path();
    path.append(*(++tok.begin()));
    bank->load_image(*tok.begin(), path);
  }
}

imgptr get_image(std::string name)
{
  return bank->get(name);
}

void remove_image(std::string name)
{
  bank->remove_image(name);
}

void init()
{
  if (bank.use_count() == 0)
  {
    bank = std::shared_ptr<image_bank>(new image_bank);
  }
}

void shutdown()
{
  bank.reset();
}
} // namespace image_assets

namespace font_assets
{
  using fptr = std::shared_ptr<waifuengine::graphics::font>;

  class font_bank
  {
  private:
    std::unordered_map<std::string, fptr> fonts;
  public:
    font_bank() {}
    ~font_bank() {}

    void load(std::string name, std::string path, int pt)
    {
      fptr f = fptr(new waifuengine::graphics::font(path, pt));
      fonts[name] = f;
    }

    void unload(std::string name)
    {
      fonts.erase(name);
    }

    fptr get(std::string name)
    {
      return (fonts.count(name)) ? fonts[name] : nullptr;
    }
  };

  std::shared_ptr<font_bank> bank;

  fptr get_font(std::string name)
  {
    return bank->get(name);
  }

  fptr default_font()
  {
    return bank->get("default font");
  }

  void unload_font(std::string name)
  {
    bank->unload(name);
  }

  void load_fonts(std::string flist)
  {
    auto files = waifuengine::utils::parse_file_to_vector(flist);
    for(std::string& s : files)
    {
      boost::char_separator<char> sep(":");
      boost::tokenizer<boost::char_separator<char>> tok(s, sep);
      auto iter = tok.begin();
      std::string name = *iter++; // font name
      std::string path = *iter++; // font path
      std::string point = *iter++; // font size
      bank->load(name, path, waifuengine::utils::str_to_int(point));
    }
  }

  void init()
  {
    if(bank.use_count() == 0)
    {
      bank = std::shared_ptr<font_bank>(new font_bank());
    }
  }

  void shutdown()
  {
    bank.reset();
  }
}

namespace assets
{
  void init()
  {
    image_assets::init();
    text_assets::init();
    font_assets::init();
  }

  void shutdown()
  {
    font_assets::shutdown();
    text_assets::shutdown();
    image_assets::shutdown();
  }
}

} // namespace core
} // namespace waifuengine