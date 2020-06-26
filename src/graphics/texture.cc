#include <SOIL2/SOIL2.h>
#include <unordered_map>

#include "texture.hpp"
#include "log.hpp"
#include "window.hpp"
#include "utils.hpp"

namespace we = ::waifuengine;

namespace waifuengine
{
  namespace graphics
  {
    namespace textures
    {
      texture::texture(fs::path file) : txtr(0)
      {
        load(file);
      }

      texture::~texture()
      {
      }

      void texture::draw() const
      {
      }

      void texture::load(fs::path file)
      {
        txtr = SOIL_load_OGL_texture(file.string().c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        if (txtr == 0)
        {
          we::log::LOGERROR(SOIL_last_result());
        }
      }

      namespace impl
      {
        std::unordered_map<std::string, textureptr> loaded_textures;
      }

      std::vector<std::string> list_loaded_textures()
      {
        std::vector<std::string> list;
        for(auto pair : impl::loaded_textures)
        {
          list.push_back(pair.first);
        }
        return list;
      }

      std::optional<textureptr> get_texture(std::string const& name)
      {
        if(impl::loaded_textures.count(name))
        {
          return impl::loaded_textures.at(name);
        }
        else return {};
      }

      void load_textures()
      {
        // recursively iterate through /assets/images and load each image as texture
        std::string images_path = we::utils::get_exe_path() + "\\assets\\images";
        std::vector<fs::path> paths = we::utils::recursive_list_files_in_folder(images_path);
        for(fs::path const& p : paths)
        {
          impl::loaded_textures.insert_or_assign(we::utils::strip_filename(p), std::shared_ptr<texture>(new texture(p)));
        }
      }

    } // namespace textures
  }   // namespace graphics
} // namespace waifuengine