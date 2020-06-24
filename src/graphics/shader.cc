// a lot of this code was found in this tutorial: https://learnopengl.com/Getting-started/Hello-Triangle

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <unordered_map>
#include <fstream>

#include <shader.hpp>
#include <utils.hpp>
#include <serialization.hpp>

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
static std::unordered_map<std::string, std::shared_ptr<shader>> loaded_shaders;

// class for serializing paths and names
class shader_map
{
public:
  // map of shader program name to the filenames of its vertex and fragment shaders, order sensitive
  std::unordered_map<std::string, std::pair<std::string, std::string>> m; 

  auto begin() -> decltype(m.begin()) { return m.begin(); }
  auto end() -> decltype(m.end()) { return m.end(); }
  
  template<class Archive>
  void serialize(Archive& ar, unsigned int const v)
  {
    ar & m;
  }
};

static const char *default_vertex_shader_source =
    "#version 330 core\n"
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
  impl::shader_map m;
  // using that data, recompile and link all shaders
  for(auto pair : m)
  {
    impl::loaded_shaders[pair.first] = std::shared_ptr<shader>(new shader(vertex_shader(pair.second.first), fragment_shader(pair.second.second)));
  }
  // std::string temp;
  // std::ifstream stream(temp);
  // boost::archive::text_iarchive arch(stream);
  // arch >> m;
}

void generate_default_shaders()
{
  // compile and link default shaders
  vertex_shader v({});
  fragment_shader f({});
  impl::loaded_shaders["default"] = std::shared_ptr<shader>(new shader(v, f));
}

void save_shader_map()
{
  // saves out a config file that has the location of shader files in use
  impl::shader_map m;

  std::string temp; // TODO: change this for the actual file path
  std::ofstream stream(temp);
  boost::archive::text_oarchive arch(stream);
  arch << m;
}

vertex_shader::vertex_shader(fs::path file) : source(nullptr), shader_id(0), filepath(file)
{
  if(filepath == fs::path{} || filepath == "default")
  {
    source = impl::default_vertex_shader_source;
    filepath = "default";
  }
  else
  {
    source = we::utils::parse_file_to_string(file.generic_string()).c_str();
  }
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
    throw std::exception(infolog);
  }
}

vertex_shader::~vertex_shader()
{
  glDeleteShader(shader_id);
}

fragment_shader::fragment_shader(fs::path file) : source(nullptr), shader_id(0), filepath(file)
{
  if(filepath == fs::path{} || filepath == "default")
  {
    source = impl::default_fragment_shader_source;
    filepath = "default";
  }
  else
  {
    source = we::utils::parse_file_to_string(file.generic_string()).c_str();
  }
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
    throw std::exception(infolog);
  }
}

fragment_shader::~fragment_shader()
{
  glDeleteShader(shader_id);
}

shader::shader(vertex_shader& v, fragment_shader& f) : program_id(0), files({v.filepath, f.filepath})
{
  link(v, f);
}

shader::shader(vertex_shader&& v, fragment_shader&& f) : program_id(0), files({v.filepath, f.filepath})
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
    throw std::exception(infolog);
  }
}

void shader::link(vertex_shader&& v, fragment_shader&& f)
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
    throw std::exception(infolog);
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