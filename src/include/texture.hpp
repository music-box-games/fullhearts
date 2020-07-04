#ifndef _WE_TEXTURE_HPP_
#define _WE_TEXTURE_HPP_

#include <vector>
#include <string>
#include <memory>
#include <optional>
#include <array>
#include <set>
#include <glm/glm.hpp>

#include "filesystem.hpp"
#include "image.hpp"
#include "shader.hpp"
#include "gameobject.hpp"
#include "texture.hpp"
#include "transform.hpp"
#include "debug.hpp"

namespace waifuengine
{
  namespace graphics
  {
    namespace textures
    {
      class texture
      {
      private:
        friend class waifuengine::core::debug::imgui_listener;

        static constexpr int VERT_COUNT = 28;
        static constexpr int ELEMENT_COUNT = 6;

        using vert_array = std::array<float, VERT_COUNT>;
        using element_array = std::array<unsigned int, ELEMENT_COUNT>;

        unsigned int unit_id;
        unsigned int txtr;
        vert_array vertices;
        element_array elements;
        std::shared_ptr<shaders::shader> shd;
        unsigned int vao;
        unsigned int vbo;
        unsigned int ebo;
        int width;
        int height;
        std::shared_ptr<image> im;

        std::string name;
        void load(imageptr i);

      public:
        texture(imageptr image, std::string const& name, unsigned int id, std::string shader_name);
        ~texture();

        void draw(transform t = transform()) const;
        void update(float dt);
        void set_transform();   

        glm::vec2 texture_dimensions() const;  
      };

      using textureptr = std::shared_ptr<texture>;

      std::vector<std::string> list_loaded_textures();
      std::vector<std::string> list_loaded_images();
      std::set<std::string> list_image_files();
      std::unordered_map<std::string, fs::path> list_image_paths();
      std::optional<std::shared_ptr<texture>> get_texture(std::string const& name);
      std::optional<std::shared_ptr<image>> get_image(std::string const& name);
      void load_textures();
      textureptr load_texture(std::string const& image_name, std::string const& shader_name);
      void load_images();
      imageptr load_image(std::string const& name);

      void release_textures();
      void release_images();

      std::unordered_map<std::string, textureptr> get_texturemap();

      namespace test
      {
        class texture_test_object : public we::object_management::gameobject
        {
        protected:
          textureptr tex;

        public:
          texture_test_object(std::string const& name, std::string const& texture_name, std::string const& shader_name);
          virtual ~texture_test_object();

          virtual void update(float);
          virtual void draw() const;
        };
      }
    }
  }
}

#endif