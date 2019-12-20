/******************************************************************************/
/*!
\file   texture.cc
\author Ryan Hanson
\par    email: iovita\@musicboxgames.net
\brief
  Texture class

*/
/******************************************************************************/

#include <unordered_map>

#include <SOIL2/SOIL2.h>

#include <texture.hpp>
#include <log.hpp>

namespace we = ::waifuengine;

namespace waifuengine
{
namespace graphics
{
namespace textures
{

texture::texture(std::string file) : components::component<texture>(), texture_id(0), valid(false)
{
  load_texture(file);
}

texture::texture(texture const &other) : components::component<texture>(), texture_id(other.texture_id), valid(other.valid) {}

texture::~texture() {}

void texture::load_texture(std::string file)
{
  texture_id = SOIL_load_OGL_texture(file.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
                                     SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
  // check that loading worked properly
  if (texture_id == 0)
  {
    std::stringstream ss;
    ss << "Failed to load texture: " << file;
    we::log::error(ss.str());
    valid = false;
    return;
  }
  valid = true;
}

void texture::update(float) {}

void texture::draw() const {}

bool texture::is_valid() const
{
  return valid;
}

static std::unordered_map<std::string, std::shared_ptr<texture>> loaded_textures;

std::optional<std::shared_ptr<texture>> load_texture(std::string file, std::string name)
{
  std::shared_ptr<texture> t(new texture(file));
  if (!t->is_valid())
  {
    return {};
  }
  loaded_textures[name] = t;
  return std::optional(t);
}

std::optional<std::shared_ptr<texture>> get_texture(std::string name)
{
  if (loaded_textures.count(name))
  {
    return std::optional(loaded_textures[name]);
  }
  else
    return {};
}

void init() {}

void shutdown()
{
  loaded_textures.clear();
}

} // namespace textures
} // namespace graphics
} // namespace waifuengine
