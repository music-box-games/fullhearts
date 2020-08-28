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
        using texturemap = std::unordered_map<std::string, std::shared_ptr<texture>>;
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

      std::optional<textureptr> get_texture(std::string const &name)
      {
        if (impl::loaded_textures.count(name))
        {
          log::LOGTRACE("Requested texture: \"" + name + "\" already loaded. Retreiving.");
          return impl::loaded_textures.at(name);
        }
        else
        {
          log::LOGTRACE("Requested texture: \"" + name + "\" not loaded. Retreiving image data...");
          get_image(name);
          return load_texture(name, "default_texture_shader");
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

      textureptr load_texture(std::string const &image_name, std::string const &shader_name)
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
          impl::loaded_textures[image_name] = std::make_shared<texture>(i, image_name, impl::loaded_textures.size(), shader_name);
          return impl::loaded_textures[image_name];
        }
      }

      void load_textures()
      {
      }

      texture::texture(imageptr i, std::string const &n, unsigned int uid, std::string shader_name) : unit_id(0)
      {
        log::LOGTRACE(std::string("Constructing texture: " + n));
        im = i;
        name = n;
        width = static_cast<int>(im->dimensions()[0]);
        height = static_cast<int>(im->dimensions()[1]);
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        glGenBuffers(1, &vbo);

        auto wind = get_current_window();

        float top_left_x = 0 - (((width / 2) - (wind->get_width() / 2)) / wind->get_width()) - 1.0f;
        float top_left_y = 0 + (((height / 2) + (wind->get_height() / 2)) / wind->get_height());
        float top_right_x = 0 + (((width / 2) + (wind->get_width() / 2)) / wind->get_width());
        float top_right_y = 0 + (((height / 2) + (wind->get_height() / 2)) / wind->get_height());
        float bottom_right_x = 0 + (((width / 2) + (wind->get_width() / 2)) / wind->get_width());
        float bottom_right_y = 0 - (((height / 2) - (wind->get_height() / 2)) / wind->get_height()) - 1.0f;
        float bottom_left_x = 0 - (((width / 2) - (wind->get_width() / 2)) / wind->get_width()) - 1.0f;
        float bottom_left_y = 0 - (((height / 2) - (wind->get_height() / 2)) / wind->get_height()) - 1.0f;

        glm::vec2 top_left = {top_left_x, top_left_y};
        glm::vec2 top_right = {top_right_x, top_right_y};
        glm::vec2 bottom_right = {bottom_right_x, bottom_right_y};
        glm::vec2 bottom_left = {bottom_left_x, bottom_left_y};

        vert_array v = {
            // position                           // color              // tex coord
            top_left[0], top_left[1], 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,         // top left
            top_right[0], top_right[1], 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,       // top right
            bottom_right[0], bottom_right[1], 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, // bottom right
            bottom_left[0], bottom_left[1], 1.0f, 1.0f, 1.0f, 0.0f, 1.0f    // bottom left
        };

        vertices = v;

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vert_array::value_type), vertices.data(), GL_STATIC_DRAW);

        glGenBuffers(1, &ebo);

        std::array<unsigned int, ELEMENT_COUNT> e = {
            0, 1, 2,
            2, 3, 0};
        elements = e;

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, elements.size() * sizeof(element_array::value_type), elements.data(), GL_STATIC_DRAW);

        auto s = shaders::get_shader(shader_name);
        if (s.has_value())
        {
          shd = s.value();
        }
        else
        {
          // warning
          we::log::LOGWARNING(std::string("Could not find shader: " + shader_name));
        }
        shd->use();

        // specify the layour of the vertex data
        int position_attribute = shd->get_attribute("position");
        glEnableVertexAttribArray(position_attribute);
        glVertexAttribPointer(position_attribute, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 0);

        int tex_attribute = shd->get_attribute("texcoord");
        glEnableVertexAttribArray(tex_attribute);
        glVertexAttribPointer(tex_attribute, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(5 * sizeof(float)));

        load(im);

        shd->set_int_1("tex", 0);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      }

      texture::~texture()
      {
        log::LOGTRACE(std::string("Destructing texture: " + name));
        // release texture
        glDeleteTextures(1, &txtr);
        glDeleteBuffers(1, &vbo);
        glDeleteBuffers(1, &ebo);
        glDeleteVertexArrays(1, &vao);
      }

      glm::vec2 texture::texture_dimensions() const
      {
        return {width, height};
      }

#define TUNIT(x) (GL_TEXTURE0 + x)
      void texture::draw() const
      {
  


        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glBindTexture(GL_TEXTURE_2D, txtr);

        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vert_array::value_type), vertices.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, elements.size() * sizeof(element_array::value_type), elements.data(), GL_STATIC_DRAW);

        int position_attribute = glGetAttribLocation(shd->get_id(), "position");
        glEnableVertexAttribArray(position_attribute);
        glVertexAttribPointer(position_attribute, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), 0);

        int tex_attribute = glGetAttribLocation(shd->get_id(), "texcoord");
        glEnableVertexAttribArray(tex_attribute);
        glVertexAttribPointer(tex_attribute, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void *)(5 * sizeof(float)));

        int transform_attribute = glGetUniformLocation(shd->get_id(), "transform");
        if (transform_attribute == -1)
        {
          log::LOGERROR("Could not locate uniform \"transform\"");
          return;
        }

        shd->use();
        shd->set_int_1("tex", 0);

        glUniformMatrix4fv(transform_attribute, 1, GL_FALSE, glm::value_ptr(*(last_trans.const_data())));

        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(elements.size()), GL_UNSIGNED_INT, 0);
      }

      void texture::update(transform t)
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

        screen_point2d pos = t.get_position_in_world_coordinates();

        // take the x value for the center, and subtract half of the width of the object to the the x value for the left two verts
        // take the y value for the center, and add half of the height of the object to get the y value for the top two verts
        world_point2d top_left(pos.x - (transformed_width / 2.0f), pos.y + (transformed_height / 2.0f));
        world_point2d top_right(pos.x + (transformed_width / 2.0f), top_left.y);
        world_point2d bottom_right(top_right.x, pos.y - (transformed_height / 2.0f));
        world_point2d bottom_left(top_left.x, bottom_right.y);

        screen_point2d stop_left = world_point2d_to_screen_point2d(top_left);
        screen_point2d stop_right = world_point2d_to_screen_point2d(top_right);
        screen_point2d sbottom_right = world_point2d_to_screen_point2d(bottom_right);
        screen_point2d sbottom_left = world_point2d_to_screen_point2d(bottom_left);

                vert_array v = {
            // position             // color r     g      b   // tex coord uv
            stop_left.x, stop_left.y,         1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // top left
            stop_right.x, stop_right.y,       0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // top right
            sbottom_right.x, sbottom_right.y, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, // bottom right
            sbottom_left.x, sbottom_left.y,   1.0f, 1.0f, 1.0f, 0.0f, 1.0f  // bottom left
        };
        vertices = v;
      }

      void texture::load(imageptr img)
      {
        log::LOGTRACE(std::string("Texture: \"" + name + "\" loading image: \"" + utils::strip_path_to_filename_and_ext(img->name()) + "\""));
        glGenTextures(1, &txtr);

        glBindTexture(GL_TEXTURE_2D, txtr);
        glTexImage2D(GL_TEXTURE_2D, unit_id, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, img->data());
        glGenerateMipmap(GL_TEXTURE_2D);
        shd->set_int_1("tex", unit_id);
      }
#undef TUNIT

      namespace test
      {
        texture_test_object::texture_test_object(std::string const &n, std::string const &texture_name, std::string const &shader_name) : object_management::gameobject(n)
        {
          tex = get_texture(texture_name).value();
        }

        texture_test_object::~texture_test_object()
        {
        }

        void texture_test_object::update(float)
        {
          if (!disabled_)
          {
            tex->update();
          }
        }

        void texture_test_object::draw() const
        {
          if (!disabled_)
          {
            tex->draw();
          }
        }
      } // namespace test

    } // namespace textures
  }   // namespace graphics
} // namespace waifuengine