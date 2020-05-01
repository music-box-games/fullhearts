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
        vertex_shader(std::string src);
        vertex_shader(const char * src);
        ~vertex_shader();

      private:
        friend class shader;
        void compile();
        const char * source;
        unsigned int shader_id;
      };

      class fragment_shader
      {
      public:
        fragment_shader(fs::path file);
        fragment_shader(std::string src);
        fragment_shader(const char * src);
        ~fragment_shader();

      private:
        friend class shader;
        void compile();
        const char * source;
        unsigned int shader_id;
      };

      // represents a fully linked shader program
      class shader
      {
      public:
        shader(vertex_shader& v, fragment_shader& f);
        ~shader();

        void use();

      private:
        void link(vertex_shader& v, fragment_shader& f);
        unsigned int program_id;
      };
    }
  }
}

#endif // !_WE_SHADER_HPP_