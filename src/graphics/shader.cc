// a lot of this code was found in this tutorial: https://learnopengl.com/Getting-started/Hello-Triangle

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <unordered_map>
#include <optional>
#include <initializer_list>
#include <vector>
#include <set>
#include <unordered_set>
#include <array>

#include <shader.hpp>
#include <utils.hpp>

namespace we = ::waifuengine;

namespace waifuengine
{
namespace graphics
{
namespace shaders
{
namespace impl
{
static std::unordered_map<std::string, std::string> shader_paths;
static std::unordered_map<std::string, shader> loaded_shaders;

// class for serializing paths and names
class shader_map
{
};

static const char *defaul_vert_shader_source =
    "#version 330core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "  gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

static const char * default_fragment_shader_source =
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "  FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\0";
} // namespace impl

void load_shaders()
{
  // find the archive that contains the map of filenames for shaders and their names or something like that
}

void generate_default_shaders()
{
  // compile and link default shaders
}

void save_shader_map()
{
  // saves out a config file that has the location of shader files in use
}

vertex_shader::vertex_shader(fs::path file) : source(nullptr), shader_id(0)
{
  source = we::utils::parse_file_to_string(file.generic_string()).c_str();
  compile();
}

vertex_shader::vertex_shader(std::string src) : source(nullptr), shader_id(0)
{
  source = src.c_str();
  compile();
}

vertex_shader::vertex_shader(const char * src) : source(src), shader_id(0)
{
  compile();
}

void vertex_shader::compile()
{
  shader_id = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(shader_id, 1, &source, NULL);
  glCompileShader(shader_id);
  // check for errors
  // TODO: some kind of feedback for when compilation fails, either a function to check if it is valid
  // or throw afteer failing
  int success;
  glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
  if(!success)
  {
    char infolog[512];
    glGetShaderInfoLog(shader_id, 512, NULL, infolog);
    // ERROR HERE
  }
}

vertex_shader::~vertex_shader()
{
  glDeleteShader(shader_id);
}

fragment_shader::fragment_shader(fs::path file) : source(nullptr), shader_id(0)
{
  source = we::utils::parse_file_to_string(file.generic_string()).c_str();
  compile();
}

fragment_shader::fragment_shader(std::string src) : source(nullptr), shader_id(0)
{
  source = src.c_str();
  compile();
}

fragment_shader::fragment_shader(const char * src) : source(src), shader_id(0)
{
  compile();
}

void fragment_shader::compile()
{
  shader_id = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(shader_id, 1, &source, NULL);
  glCompileShader(shader_id);
  // more error checks
  int success;
  glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
  if(!success)
  {
    char infolog[512];
    glGetShaderInfoLog(shader_id, 512, NULL, infolog);
    // ERROR HERE
  }
}

fragment_shader::~fragment_shader()
{
  glDeleteShader(shader_id);
}

shader::shader(vertex_shader& v, fragment_shader& f) : program_id(0)
{
  link(v, f);
}

void shader::link(vertex_shader& v, fragment_shader& f)
{
  program_id = glCreateProgram();
  glAttachShader(program_id, v.shader_id);
  glAttachShader(program_id, f.shader_id);
  glLinkProgram(program_id);
  int success;
  glGetProgramiv(program_id, GL_LINK_STATUS, &success);
  if(!success)
  {
    char infolog[512];
    glGetProgramInfoLog(program_id, 512, NULL, infolog);
    // ERROR
  }
}

void shader::use()
{
  glUseProgram(program_id);
}

shader::~shader()
{
  glDeleteProgram(program_id);
}

} // namespace shaders
} // namespace graphics
} // namespace waifuengine