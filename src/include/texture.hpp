#ifndef _WE_TEXTURE_HPP_
#define _WE_TEXTURE_HPP_

#include <vector>
#include <string>
#include <memory>
#include <optional>

#include "filesystem.hpp"

namespace waifuengine
{
  namespace graphics
  {
    namespace textures
    {
      class texture
      {
      private:
        unsigned int txtr;
      public:
        texture(fs::path file);
        ~texture();

        void draw() const;
        void load(fs::path file);
      };

      using textureptr = std::shared_ptr<texture>;

      std::vector<std::string> list_loaded_textures();
      std::optional<std::shared_ptr<texture>> get_texture(std::string const& name);
      void load_textures();
    }
  }
}

#endif