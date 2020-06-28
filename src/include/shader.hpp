#ifndef _WE_SHADER_HPP_
#define _WE_SHADER_HPP_

#include <optional>

#include <fs_util.hpp>
#include "utils.hpp"
namespace waifuengine
{
  namespace graphics
  {
    namespace shaders
    {
      void load_shaders();

      void generate_default_shaders();

      void save_shader_map();

      std::vector<std::string> list_loaded_shaders();

      class shader;

      std::optional<std::shared_ptr<shader>> get_shader(std::string name);

      class vertex_shader
      {
      public:
        vertex_shader(fs::path file);
        ~vertex_shader();

      private:
        friend class shader;
        void compile();
        const char * source;
        unsigned int shader_id;
        fs::path filepath;
      };

      class fragment_shader
      {
      public:
        fragment_shader(fs::path file);
        ~fragment_shader();

      private:
        friend class shader;
        void compile();
        const char * source;
        unsigned int shader_id;
        fs::path filepath;
      };

      // represents a fully linked shader program
      class shader
      {
      public:
        shader(vertex_shader& v, fragment_shader& f);
        shader(vertex_shader&& v, fragment_shader&& f);
        ~shader();

        void use();
        unsigned int get_id() const;

        // uniform setters
        void set_bool_1(std::string const& name, bool value) const;
        void set_int_1(std::string const& name, int value) const;
        void set_float_1(std::string const& name, float value) const;

        void set_bool_2(std::string const& name, bool value0, bool value1) const;
        void set_int_2(std::string const& name, int value0, int value1) const;
        void set_float_2(std::string const& name, float value0, float value1) const;

        void set_bool_3(std::string const& name, bool value0, bool value1, bool value2) const;
        void set_int_3(std::string const& name, int value0, int value1, int value2) const;
        void set_float_3(std::string const& name, float value0, float value1, float value2) const;

        void set_bool_4(std::string const& name, bool value0, bool value1, bool value2, bool value3) const;
        void set_int_4(std::string const& name, int value0, int value1, int value2, int value3) const;
        void set_float_4(std::string const& name, float value0, float value1, float value2, float value3) const;

        int get_attribute(std::string const& name);

      private:
        void link(vertex_shader& v, fragment_shader& f);
        void link(vertex_shader&& v, fragment_shader&& f);
        unsigned int program_id;
        std::pair<fs::path, fs::path> files; // shader sources used to make this program
      };
    }
  }
}

#endif // !_WE_SHADER_HPP_