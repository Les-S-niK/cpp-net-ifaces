from conan import ConanFile
from conan.tools.cmake import CMake, CMakeDeps, CMakeToolchain, cmake_layout


class mypkgRecipe(ConanFile):
    name = "ifaces"
    version = "2026.11.0"
    package_type = "application"

    # Optional metadata
    license = "MIT"
    author = "Nikita Gerasimenko (Les-S-niK), lessnik343@gmail.com"
    url = "https://github.com/Les-S-niK/cpp-net-ifaces.git"
    description = "A simple CLI-utility for Linux-based systems. Provides a network interface details as name, protocol and hardware addresses, MTU and other information."
    topics = ("C++", "network")

    # Binary configuration
    settings = "os", "compiler", "build_type", "arch"

    # Sources are located in the same place as this recipe, copy them to the recipe
    exports_sources = "CMakeLists.txt", "src/*"

    def requirements(self) -> None:
        self.requires("gtest/1.18.0")

    def layout(self) -> None:
        cmake_layout(self)

    def generate(self) -> None:
        deps = CMakeDeps(self)
        deps.generate()
        tc = CMakeToolchain(self)
        tc.generate()

    def build(self) -> None:
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self) -> None:
        cmake = CMake(self)
        cmake.install()
