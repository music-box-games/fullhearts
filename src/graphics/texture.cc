#include <unordered_map>
#include <algorithm>
#include <SOIL2/SOIL2.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "texture.hpp"
#include "log.hpp"
#include "window.hpp"
#include "utils.hpp"
#include "image.hpp"
#include "container_utils.hpp"
#include "log.hpp"
#include "point2d.hpp"

namespace we = ::waifuengine;

namespace waifuengine
{
  namespace graphics
  {
    namespace textures
    {
      namespace impl
      {
        using imagemap = std::unordered_map<std::string, std::shared_ptr<image>>;
        using texturemap = std::unordered_map<std::string, std::shared_ptr<raw_texture_data>>;

        std::vector<std::string> all_image_names;
        imagemap loaded_images;
        texturemap loaded_textures;
      } // namespace impl

      void release_textures()
      {
        impl::loaded_textures.clear();
      }

      void release_images()
      {
        impl::loaded_images.clear();
      }

      impl::texturemap get_texturemap()
      {
        return impl::loaded_textures;
      }

      std::vector<std::string> list_loaded_textures()
      {
        return utils::list_keys(impl::loaded_textures);
      }

      std::vector<std::string> list_loaded_images()
      {
        return utils::list_keys(impl::loaded_images);
      }

      std::shared_ptr<raw_texture_data> get_raw_texture(std::string const& name)
      {
        if(impl::loaded_textures.count(name))
        {
          return impl::loaded_textures.at(name);
        }
        else
        {
          return {};          
        }
        
      }


      texture get_texture(std::string const &name)
      {
        if (impl::loaded_textures.count(name))
        {
          log::LOGTRACE("Requested texture: \"" + name + "\" already loaded. Retreiving.");
          return texture(impl::loaded_textures.at(name));
        }
        else
        {
          log::LOGTRACE("Requested texture: \"" + name + "\" not loaded. Retreiving image data...");
          get_image(name);
          return texture(load_texture(name, "default_texture_shader"));
        }
      }

      std::optional<imageptr> get_image(std::string const &name)
      {
        if (impl::loaded_images.count(name))
        {
          log::LOGTRACE(std::string("Requested image: \"" + name + "\" already loaded. Retrieving data."));
          return impl::loaded_images.at(name);
        }
        else
        {
          log::LOGTRACE(std::string("Requested image: \"" + name + "\" not loaded. Loading data..."));
          return load_image(name);
        }
      }

      void load_images()
      {
        std::string images_path = we::utils::get_exe_path() + "\\assets\\images";
        std::vector<fs::path> paths = we::utils::recursive_list_files_in_folder(images_path);
        for (fs::path const &p : paths)
        {
          impl::loaded_images[we::utils::strip_filename(p)] = std::shared_ptr<image>(new image(p));
        }
      }

      std::set<std::string> list_image_files()
      {
        std::string images_path = we::utils::get_exe_path() + "\\assets\\images";
        std::vector<fs::path> paths = we::utils::recursive_list_files_in_folder(images_path);
        std::set<std::string> names;
        std::for_each(paths.begin(), paths.end(), [&names](fs::path const &p) -> void {
          names.insert(we::utils::strip_filename(p));
        });
        return names;
      }

      std::unordered_map<std::string, fs::path> list_image_paths()
      {
        std::string images_path = we::utils::get_exe_path() + "\\assets\\images";
        auto paths = we::utils::recursive_list_files_in_folder(images_path);
        std::unordered_map<std::string, fs::path> p;
        for (fs::path const &f : paths)
        {
          p[we::utils::strip_filename(f)] = f;
        }
        return p;
      }

      imageptr load_image(std::string const &name)
      {
        auto img_names = list_image_paths();
        if (img_names.count(name))
        {
          log::LOGTRACE(std::string("Requested image: \"" + name + "\" file found. Loading..."));
          impl::loaded_images[name] = std::shared_ptr<image>(new image(img_names[name]));
          return impl::loaded_images.at(name);
        }
        else
        {
          log::LOGERROR(std::string("Requested image: \"" + name + "\" file not found."));
          return {};
        }
      }

      std::shared_ptr<raw_texture_data> load_texture(std::string const &image_name, std::string const &shader_name)
      {
        if (impl::loaded_textures.count(image_name))
        {
          log::LOGTRACE(std::string("Requested texture: \"" + image_name + "\" already loaded. Retrieving."));
          return impl::loaded_textures.at(image_name);
        }
        else
        {
          log::LOGTRACE(std::string("Requested texture: \"" + image_name + "\" not loaded. Retrieving image data."));
          std::shared_ptr<image> i = get_image(image_name).value();
          impl::loaded_textures[image_name] = std::make_shared<raw_texture_data>(i, image_name, impl::loaded_textures.size(), shader_name);
          return impl::loaded_textures[image_name];
        }
      }

      void load_textures()
      {
      }

      texture::texture(std::shared_ptr<raw_texture_data> d) : name(d->get_name()), tdata(d), vertices({ 0 }), elements({ 0 })
      {
        log::LOGTRACE(std::string("Constructing texture: " + name));
      }

      texture::~texture()
      {
        log::LOGTRACE(std::string("Destructing texture: " + name));

      }

      glm::vec2 texture::texture_dimensions() const
      {
        return {tdata->get_width(), tdata->get_height()};
      }

#define TUNIT(x) (GL_TEXTURE0 + x)
      void texture::draw() const
      {
        {
          std::stringstream ss;
          
        }
        tdata->draw((float*)vertices.data(), vertices.size(), (unsigned int *)elements.data(), elements.size(), last_trans);
      }

      void texture::update(transform const& t)
      {
        last_trans = t;
        // calc vertices from transform's position and dimensions
        // get width and height of window
        float window_width = get_current_window()->get_width();
        float window_height = get_current_window()->get_height();
        float height_ratio = t.get_height_ratio();
        float width_ratio = t.get_width_ratio();
        float transformed_width = window_width * width_ratio;
        float transformed_height = window_height * height_ratio;

        window_point_2d pos = t.get_position_in_window_coordinates();

        // take the x value for the center, and subtract half of the width of the object to the the x value for the left two verts
        // take the y value for the center, and add half of the height of the object to get the y value for the top two verts
        window_point_2d top_left(pos.x - (transformed_width / 2.0f), pos.y + (transformed_height / 2.0f));
        window_point_2d top_right(pos.x + (transformed_width / 2.0f), top_left.y);
        window_point_2d bottom_right(top_right.x, pos.y - (transformed_height / 2.0f));
        window_point_2d bottom_left(top_left.x, bottom_right.y);

        screen_point_2d stop_left = window_point_2d_to_screen_point_2d(top_left);
        screen_point_2d stop_right = window_point_2d_to_screen_point_2d(top_right);
        screen_point_2d sbottom_right = window_point_2d_to_screen_point_2d(bottom_right);
        screen_point_2d sbottom_left = window_point_2d_to_screen_point_2d(bottom_left);

        vert_array v = {
            // position             // color r     g      b   // tex coord uv
            stop_left.x, stop_left.y,         1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // top left
            stop_right.x, stop_right.y,       0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // top right
            sbottom_right.x, sbottom_right.y, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, // bottom right
            sbottom_left.x, sbottom_left.y,   1.0f, 1.0f, 1.0f, 0.0f, 1.0f  // bottom left
        };
        vertices = v;

        elements = {
            0, 1, 2,
            2, 3, 0};
      }
#undef TUNIT

      texture::vert_array texture::get_vertices() const
      {
        return vertices;
      }

      namespace test
      {
        texture_test_object::texture_test_object(std::string const &n, std::string const &texture_name, std::string const &shader_name) : object_management::gameobject(n), tex(get_texture(texture_name))
        {
          log::LOGTRACE("Constructing texture_test_object");
        }

        texture_test_object::~texture_test_object()
        {
          log::LOGTRACE("Destructing texture_test_object");
        }

        void texture_test_object::update(float)
        {
          if (!disabled_)
          {
            tex.update();
          }
        }

        void texture_test_object::draw() const
        {
          if (!disabled_)
          {
            tex.draw();
          }
        }
      } // namespace test

    } // namespace textures
  }   // namespace graphics
} // namespace waifuengine