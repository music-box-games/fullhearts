// a lot of this code was found in this tutorial: https://learnopengl.com/Getting-started/Hello-Triangle

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <unordered_map>
#include <fstream>

#include <shader.hpp>
#include <utils.hpp>
#include <serialization.hpp>

#include "fs_util.hpp"
#include "log.hpp"

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

class shader_file
{
public:
  std::string v_shader;
  std::string f_shader;

  shader_file(fs::path path)
  {
    std::vector<std::string> lines = we::utils::parse_file_to_vector(path.string());
    for(auto const& s : lines)
    {
      std::vector<std::string> tokens = we::utils::tokenize_string(s, ":");
      if(tokens.at(0) == "vertex")
      {
        v_shader = tokens.at(1);
      }
      else if(tokens.at(0) == "fragment")
      {
        f_shader = tokens.at(1);
      }
    }
  }

  ~shader_file() = default;
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

void release_shaders()
{
  impl::loaded_shaders.clear();
}

void load_shaders()
{
  // find the archive that contains the map of filenames for shaders and their names or something like that
  impl::shader_map m;
  std::string exe_path = we::utils::get_exe_path();
  std::string shaders_path = exe_path + std::string("\\shaders");
  std::vector<fs::path> shader_files = we::utils::list_files_in_folder(fs::path(shaders_path));
  for(auto const& p : shader_files)
  {
    impl::shader_file s(p);
    std::string v_shader_path = utils::get_exe_path() + "\\shaders" + s.v_shader;
    std::string f_shader_path = utils::get_exe_path() + "\\shaders" + s.f_shader;
    m.m[we::utils::strip_filename(p)] = {v_shader_path, f_shader_path};
  }

  // using that data, recompile and link all shaders
  for(auto pair : m)
  {
    impl::loaded_shaders[pair.first] = std::shared_ptr<shader>(new shader(vertex_shader(pair.second.first), fragment_shader(pair.second.second)));
  }
  impl::loaded_shaders["default"] = std::shared_ptr<shader>(new shader(vertex_shader("default"), fragment_shader("default")));
}

void load_shader(fs::path p)
{
  impl::shader_file s(p);
  std::string v_shader_path = utils::get_exe_path() + "\\shaders" + s.v_shader;
  std::string f_shader_path = utils::get_exe_path() + "\\shaders" + s.f_shader;
}

std::optional<std::shared_ptr<shader>> get_shader(std::string name)
{
  if(impl::loaded_shaders.count(name))
  {
    return impl::loaded_shaders[name];
  }
  else return {};
}

std::vector<std::string> list_loaded_shaders()
{
  std::vector<std::string> list;
  for(auto const& p: impl::loaded_shaders)
  {
    list.push_back(p.first);
  }
  return list;
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
  std::string s = "";
  if(filepath == fs::path{} || filepath == "default")
  {
    source = impl::default_vertex_shader_source;
    filepath = "default";
  }
  else
  {
    s = we::utils::parse_file_to_string(filepath.generic_string()).c_str();
    if(s.empty())
    {
      source = impl::default_vertex_shader_source;
      filepath = "default";
    }
    else
    {
      source = s.c_str(); 
    }
  }
  compile();
}

void vertex_shader::compile()
{
  {
    std::stringstream ss;
    ss << "Compiling vertex shader:" << filepath << ":\n" << source;
    we::log::LOGDEBUG(ss.str());
  }
  shader_id = glCreateShader(GL_VERTEX_SHADER);
  
  glShaderSource(shader_id, 1, &source, NULL);
  glGetError();
  glCompileShader(shader_id);
  int result = glGetError();
  if(result != GL_NO_ERROR)
  {
    std::stringstream ss;
    ss << "Error " << result << " compiling shader: " << utils::strip_path_to_filename_and_ext(filepath);
    we::log::LOGERROR(ss.str());
    throw std::runtime_error(ss.str());
  }
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
    we::log::LOGERROR(infolog);
    throw std::runtime_error((const char*)infolog);
  }
}

vertex_shader::~vertex_shader()
{
  glDeleteShader(shader_id);
}

fragment_shader::fragment_shader(fs::path file) : source(nullptr), shader_id(0), filepath(file)
{
  std::string s = "";
  if(filepath == fs::path{} || filepath == "default")
  {
    source = impl::default_fragment_shader_source;
    filepath = "default";
  }
  else
  {
    s = we::utils::parse_file_to_string(filepath.generic_string());
    if(s.empty())
    {
      source = impl::default_fragment_shader_source;
      filepath = "default";
    }
    else
    {
      source = s.c_str();
    }
  }
  compile();
}

void fragment_shader::compile()
{
  {
    std::stringstream ss;
    
    ss << "Compiling fragment shader:" << filepath << ":\n" << source;
    we::log::LOGDEBUG(ss.str());
  }
  glGetError();
  shader_id = glCreateShader(GL_FRAGMENT_SHADER);
  glGetError();
  glShaderSource(shader_id, 1, &source, NULL);
  glGetError();
  glCompileShader(shader_id);
  glGetError();
  int result = glGetError();
  if(result != GL_NO_ERROR)
  {
    std::stringstream ss;
    ss << "Error " << result << " compiling shader: " << utils::strip_path_to_filename_and_ext(filepath);
    we::log::LOGERROR(ss.str());
    throw std::runtime_error(ss.str());
  }
  // more error checks
  int success;
  glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
  if(!success)
  {
    char infolog[512];
    glGetShaderInfoLog(shader_id, 512, NULL, infolog);
    // ERROR HERE
    we::log::LOGERROR(infolog);
    throw std::runtime_error((const char*)infolog);
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
    throw std::runtime_error((const char*)infolog);
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
    we::log::LOGERROR(infolog);
    throw std::runtime_error((const char*)infolog);
  }
}

void shader::use() const
{
  glUseProgram(program_id);
}

unsigned int shader::get_id() const
{
  return program_id;
}

shader::~shader()
{
  glDeleteProgram(program_id); // TODO: being called twice
}

void shader::set_bool_1(std::string const& name, bool value) const
{
  glUniform1i(glGetUniformLocation(program_id, name.c_str()), (int)value);
}

void shader::set_int_1(std::string const& name, int value) const
{
  use();
  glUniform1i(glGetUniformLocation(program_id, name.c_str()), value);
}

void shader::set_float_1(std::string const& name, float value) const
{
  glUniform1f(glGetUniformLocation(program_id, name.c_str()), value);
}

void shader::set_bool_2(std::string const& name, bool value0, bool value1) const
{
  glUniform2i(glGetUniformLocation(program_id, name.c_str()), (int)value0, (int)value1);
}

void shader::set_int_2(std::string const& name, int value0, int value1) const
{
  glUniform2i(glGetUniformLocation(program_id, name.c_str()), value0, value1);
}

void shader::set_float_2(std::string const& name, float value0, float value1) const
{
  glUniform2f(glGetUniformLocation(program_id, name.c_str()), value0, value1);
}

void shader::set_bool_3(std::string const& name, bool value0, bool value1, bool value2) const
{
  glUniform3i(glGetUniformLocation(program_id, name.c_str()), (int)value0, (int)value1, (int)value2);
}

void shader::set_int_3(std::string const& name, int value0, int value1, int value2) const
{
  glUniform3i(glGetUniformLocation(program_id, name.c_str()), value0, value1, value2);
}

void shader::set_float_3(std::string const& name, float value0, float value1, float value2) const
{
  glUniform3f(glGetUniformLocation(program_id, name.c_str()), value0, value1, value2);
}

void shader::set_bool_4(std::string const& name, bool value0, bool value1, bool value2, bool value3) const
{
  glUniform4i(glGetUniformLocation(program_id, name.c_str()), (int)value0, (int)value1, (int)value2, (int)value3);
}

void shader::set_int_4(std::string const& name, int value0, int value1, int value2, int value3) const
{
  glUniform4i(glGetUniformLocation(program_id, name.c_str()), value0, value1, value2, value3);
}

void shader::set_float_4(std::string const& name, float value0, float value1, float value2, float value3) const
{
  glUniform4f(glGetUniformLocation(program_id, name.c_str()), value0, value1, value2, value3);
}

int shader::get_attribute(std::string const& name)
{
  return glGetAttribLocation(program_id, name.c_str());
}

int shader::get_uniform(std::string const& name)
{
  int result = glGetUniformLocation(program_id, name.c_str());
  if (result == -1)
  {
    log::LOGERROR(std::string(std::string("Could not locate uniform \"") + name + std::string("\"")));
  }
  return result;
}

} // namespace shaders
} // namespace graphics
} // namespace waifuengine