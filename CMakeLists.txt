cmake_minimum_required(VERSION 3.15)
set(PROJECT_NAME "ifaces")

project(${PROJECT_NAME} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(TESTS "Enable tests" OFF)

if(TESTS)
  find_package(GTest)
  enable_testing()
  include(GoogleTest)

  add_executable(CppNetIfacesTests ./src/system/sockets/linux_sockets.cpp
                                   ./tests/tests_system_linux_sockets.cpp)

  target_include_directories(CppNetIfacesTests PUBLIC ./include/)

  target_link_libraries(CppNetIfacesTests PRIVATE GTest::gtest
                                                  GTest::gtest_main)

  add_test(NAME CppNetIfacesTests COMMAND CppNetIfacesTests)
else()
  add_executable(${PROJECT_NAME} src/main.cpp)

  add_library(Sockets ./src/system/sockets/linux_sockets.cpp)

  target_include_directories(${PROJECT_NAME} PUBLIC include/)
  target_include_directories(Sockets PUBLIC include/)

  target_link_libraries(${PROJECT_NAME} PRIVATE Sockets)
endif()
