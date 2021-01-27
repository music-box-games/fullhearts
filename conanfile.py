from conans import ConanFile, CMake

class FullheartsConan(ConanFile):
  generators = "cmake"
  settings = "os", "compiler", "build_type", "arch"

  def requirements(self):
    # NOTE: @user/channel is being phased out, can cause conflict errors, do this to fix
    self.requires("zlib/1.2.11")
    self.requires("bzip2/1.0.8")

    if self.settings.os == "Windows":
      self.requires("boost/1.71.0@conan/stable")
    else:
      self.requires("boost/1.69.0@conan/stable")

    self.requires("glm/0.9.9.5@g-truc/stable")
    self.requires("gtest/1.8.1@bincrafters/stable")
    self.requires("glad/0.1.29@bincrafters/stable")
    self.requires("glfw/3.3.2@bincrafters/stable")
    self.requires("soil2/1.20@bincrafters/stable")
    self.requires("nlohmann_json/3.9.1")
    self.requires("sfml/2.5.1@bincrafters/stable")

  def configure(self):
    if self.settings.os == "Windows":
      self.settings.compiler = "Visual Studio"
      self.settings.compiler.version = "16"
    else:
      self.settings.compiler = "clang"
      self.settings.compiler.version = "9"
      self.settings.compiler.libcxx = "libstdc++11"

  def build(self):
    cmake = CMake(self)
    cmake.configure()
    cmake.build()