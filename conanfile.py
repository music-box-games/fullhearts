from conans import ConanFile, CMake

class FullheartsConan(ConanFile):
  generators = "cmake"
  settings = "os", "compiler", "build_type", "arch"

  def requirements(self):
    self.requires("boost/1.70.0@conan/stable")
    self.requires("glm/0.9.9.5@g-truc/stable")
    self.requires("gtest/1.8.1@bincrafters/stable")
    self.requires("glad/0.1.29@bincrafters/stable")
    self.requires("glfw/3.3.2@bincrafters/stable")
    if self.settings.os == "Windows":
      pass
    else:
      self.requires("zlib/1.2.11")

  def configure(self):
    if self.settings.os == "Windows":
      self.settings.compiler = "Visual Studio"
      self.settings.compiler.version = "16"
    else:
      pass

  def build(self):
    cmake = CMake(self)
    cmake.configure()
    cmake.build()