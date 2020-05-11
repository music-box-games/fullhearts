#ifndef _WE_SHADER_HPP_
#define _WE_SHADER_HPP_

#include <fs_util.hpp>

namespace waifuengine
{
  namespace graphics
  {
    namespace shaders
    {
      void load_shaders();

      void generate_default_shaders();

      void save_shader_map();

      class shader;

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