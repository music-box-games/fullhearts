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
      }

      std::vector<std::string> list_loaded_textures()
      {
        return utils::list_keys(impl::loaded_textures);
      }

      std::vector<std::string> list_loaded_images()
      {
        return utils::list_keys(impl::loaded_images);
      }

      std::optional<textureptr> get_texture(std::string const& name)
      {
        if (impl::loaded_textures.count(name))
        {
          return impl::loaded_textures.at(name);
        }
        else
        {
          get_image(name);
          return load_texture(name, "default_texture_shader");
        }

        return {};
      }

      std::optional<imageptr> get_image(std::string const& name)
      {
        if (impl::loaded_images.count(name))
        {
          return impl::loaded_images.at(name);
        }
        else
        {
          return load_image(name);
        }
      }

      void load_images()
      {
        std::string images_path = we::utils::get_exe_path() + "\\assets\\images";
        std::vector<fs::path> paths = we::utils::recursive_list_files_in_folder(images_path);
        for (fs::path const& p : paths)
        {
          impl::loaded_images[we::utils::strip_filename(p)] = std::shared_ptr<image>(new image(p));
        }
      }

      std::set<std::string> list_image_files()
      {
        std::string images_path = we::utils::get_exe_path() + "\\assets\\images";
        std::vector<fs::path> paths = we::utils::recursive_list_files_in_folder(images_path);
        std::set<std::string> names;
        std::for_each(paths.begin(), paths.end(), [&names](fs::path const& p) -> void {
          names.insert(we::utils::strip_filename(p));
        });
        return names;
      }

      std::unordered_map<std::string, fs::path> list_image_paths()
      {
        std::string images_path = we::utils::get_exe_path() + "\\assets\\images";
        auto paths = we::utils::recursive_list_files_in_folder(images_path);
        std::unordered_map<std::string, fs::path> p;
        for(fs::path const& f : paths)
        {
          p[we::utils::strip_filename(f)] = f;
        }
        return p;
      }

      imageptr load_image(std::string const& name)
      {
        auto img_names = list_image_paths();
        if(img_names.count(name))
        {
          impl::loaded_images[name] = std::shared_ptr<image>(new image(img_names[name]));
          return impl::loaded_images.at(name);
        }
        return {};
      }

      textureptr load_texture(std::string const& image_name, std::string const& shader_name)
      {
        if (impl::loaded_textures.count(image_name)) return impl::loaded_textures.at(image_name);
        std::shared_ptr<image> i = get_image(image_name).value();
        impl::loaded_textures[image_name] = std::make_shared<texture>(i, image_name, impl::loaded_textures.size(), shader_name);
        return impl::loaded_textures[image_name];
      }

      void load_textures()
      {

      }

      texture::texture(imageptr i, std::string const& n, unsigned int uid, std::string shader_name) : unit_id(uid)
      {
        im = i;
        name = n;
        width = im->dimensions()[0];
        height = im->dimensions()[1];
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        glGenBuffers(1, &vbo);

        auto wind = get_current_window();

        float top_left_x =      0 - (((width / 2) - (wind->get_width() / 2)) / wind->get_width()) -1.0f;
        float top_left_y =      0 + (((height / 2) + (wind->get_height() / 2)) / wind->get_height());
        float top_right_x =     0 + (((width / 2) + (wind->get_width() / 2)) / wind->get_width());
        float top_right_y =     0 + (((height / 2) + (wind->get_height() / 2)) / wind->get_height());
        float bottom_right_x =  0 + (((width / 2) + (wind->get_width() / 2)) / wind->get_width());
        float bottom_right_y =  0 - (((height / 2) - (wind->get_height() / 2)) / wind->get_height()) - 1.0f;
        float bottom_left_x =   0 - (((width / 2) - (wind->get_width() / 2)) / wind->get_width()) - 1.0f;
        float bottom_left_y =   0 - (((height / 2) - (wind->get_height() / 2)) / wind->get_height()) - 1.0f;

        glm::vec2 top_left = {top_left_x, top_left_y};
        glm::vec2 top_right = {top_right_x, top_right_y};
        glm::vec2 bottom_right = {bottom_right_x, bottom_right_y};
        glm::vec2 bottom_left = {bottom_left_x, bottom_left_y};

        vert_array v = {
          // position                           // color              // tex coord
           top_left[0],  top_left[1],           1.0f, 0.0f, 0.0f,  0.0f, 0.0f, // top left
           top_right[0], top_right[1],          0.0f, 1.0f, 0.0f,  1.0f, 0.0f,  // top right
           bottom_right[0], bottom_right[1],    0.0f, 0.0f, 1.0f,  1.0f, 1.0f, // bottom right
           bottom_left[0], bottom_left[1],      1.0f, 1.0f, 1.0f,  0.0f, 1.0f // bottom left
        };

        vertices = v;

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vert_array::value_type), vertices.data(), GL_STATIC_DRAW);

        glGenBuffers(1, &ebo);

        std::array<unsigned int, ELEMENT_COUNT> e = {
          0, 1, 2,
          2, 3, 0
        };
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
        glVertexAttribPointer(position_attribute, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), 0);

        int tex_attribute = shd->get_attribute("texcoord");
        glEnableVertexAttribArray(tex_attribute);
        glVertexAttribPointer(tex_attribute, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(5 * sizeof(float)));


        load(im->data());

        shd->set_int_1("tex", unit_id);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      }

      
      texture::~texture()
      {
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
      void texture::draw(transform t) const
      {
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
        glVertexAttribPointer(tex_attribute, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(5 * sizeof(float)));

        int transform_attribute = glGetUniformLocation(shd->get_id(), "transform");
        glm::vec4 result = (*(t.data())) * glm::vec4(1.0, 0.0, 0.0, 1.0f);

        shd->use();
        glUniformMatrix4fv(transform_attribute, 1, GL_FALSE, glm::value_ptr(*(t.data())));

        glDrawElements(GL_TRIANGLES, elements.size(), GL_UNSIGNED_INT, 0);
      }

      void texture::update(float)
      {

      }

      void texture::load(unsigned char* image)
      {
        glGenTextures(1, &txtr);

        glActiveTexture(TUNIT(unit_id));
        glBindTexture(GL_TEXTURE_2D, txtr);
        glTexImage2D(GL_TEXTURE_2D, unit_id, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
        shd->set_int_1("tex", unit_id);

      }
#undef TUNIT

      namespace test
      {
        texture_test_object::texture_test_object(std::string const& n, std::string const& texture_name, std::string const& shader_name) : object_management::gameobject(n)
        {
          tex = get_texture(texture_name).value();
        }

        texture_test_object::~texture_test_object()
        {

        }

        void texture_test_object::update(float dt)
        {
          if (!disabled_)
          {
            tex->update(dt);
          }
        }

        void texture_test_object::draw() const
        {
          if (!disabled_)
          {
            tex->draw();
          }
        }
      }

    } // namespace textures
  }   // namespace graphics
} // namespace waifuengine