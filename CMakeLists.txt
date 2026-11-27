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

  add_executable(
    CppNetIfacesTests
    ./src/system/sockets/linux_sockets.cpp
    ./tests/system/sockets/tests_linux_sockets.cpp
    ./src/address_types/hwaddr.cpp ./tests/address_types/tests_hwaddr_type.cpp)

  target_include_directories(CppNetIfacesTests PUBLIC ./include/)

  target_link_libraries(CppNetIfacesTests PRIVATE GTest::gtest
                                                  GTest::gtest_main)

  add_test(NAME CppNetIfacesTests COMMAND CppNetIfacesTests)
else()
  add_executable(${PROJECT_NAME} src/main.cpp)

  add_library(Sockets ./src/system/sockets/linux_sockets.cpp)
  add_library(
    AddressTypes ./src/address_types/hwaddr.cpp ./src/address_types/praddr4.cpp
                 ./src/address_types/praddr6.cpp)

  target_include_directories(Sockets PUBLIC include/)
  target_include_directories(AddressTypes PUBLIC include/)
  target_include_directories(${PROJECT_NAME} PUBLIC include/)

  target_link_libraries(${PROJECT_NAME} PRIVATE Sockets)
  target_link_libraries(${PROJECT_NAME} PRIVATE AddressTypes)
endif()
