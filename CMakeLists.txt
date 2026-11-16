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

  add_executable(ExampleTests ./tests/tests_example.cpp)

  target_include_directories(ExampleTests PUBLIC ./include/)

  target_link_libraries(ExampleTests PRIVATE GTest::gtest GTest::gtest_main)

  add_test(NAME ExampleTests COMMAND ExampleTests)
else()
  add_executable(${PROJECT_NAME} src/main.cpp)

  target_include_directories(${PROJECT_NAME} PUBLIC include/)
endif()
