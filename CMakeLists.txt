cmake_minimum_required(VERSION 4.0.0)

set(PROJECT_NAME sfml)

project(${PROJECT_NAME} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (NOT SKBUILD)
  message(WARNING "\
  This CMake file is meant to be executed using 'scikit-build'. Running
  it directly will almost certainly not produce the desired result. If
  you are a user trying to install this package, please use the command
  below, which will install all necessary build dependencies, compile
  the package in an isolated environment, and then install it.
  =====================================================================
   $ pip install .
  =====================================================================
  If you are a software developer, and this is your own package, then
  it is usually much more efficient to install the build dependencies
  in your environment once and use the following command that avoids
  a costly creation of a new virtual environment at every compilation:
  =====================================================================
   $ pip install nanobind scikit-build-core[pyproject]
   $ pip install --no-build-isolation -ve .
  =====================================================================
  You may optionally add -Ceditable.rebuild=true to auto-rebuild when
  the package is imported. Otherwise, you need to re-run the above
  after editing C++ files.")
endif()

find_package(
  Python 3.8
  REQUIRED COMPONENTS Interpreter Development.Module
  OPTIONAL_COMPONENTS Development.SABIModule
)

find_package(nanobind CONFIG REQUIRED)

include(FetchContent)

FetchContent_Declare(SFML
  GIT_REPOSITORY https://github.com/SFML/SFML.git
  GIT_TAG 3.0.1
  GIT_SHALLOW ON
  EXCLUDE_FROM_ALL
  SYSTEM)

FetchContent_MakeAvailable(SFML)

nanobind_add_module(
  ${PROJECT_NAME}
  STABLE_ABI
  NB_STATIC
  src/RootBinding.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE
  SFML::Graphics
  SFML::System
  SFML::Window
  SFML::Network
  SFML::Audio
  SFML::Main
)

target_compile_definitions(${PROJECT_NAME} PRIVATE
  PROJECT_NAME=${PROJECT_NAME}
)

target_include_directories(${PROJECT_NAME}
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/Bindings
)

install(TARGETS ${PROJECT_NAME} LIBRARY DESTINATION .)