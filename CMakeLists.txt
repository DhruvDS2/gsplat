cmake_minimum_required(VERSION 3.20)
project(gsplat_cpu LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

option(GS_BUILD_PREVIEW "Build the SDL2 preview window (needs SDL2 installed)" ON)
option(GS_BUILD_TESTS   "Build unit tests" ON)

# ---------- Dependencies (downloaded automatically) ----------
include(FetchContent)

FetchContent_Declare(glm
  GIT_REPOSITORY https://github.com/g-truc/glm.git
  GIT_TAG 1.0.1)

FetchContent_Declare(happly
  GIT_REPOSITORY https://github.com/nmwsharp/happly.git
  GIT_TAG master)

FetchContent_Declare(stb
  GIT_REPOSITORY https://github.com/nothings/stb.git
  GIT_TAG master)

FetchContent_MakeAvailable(glm)
FetchContent_Populate(happly)
FetchContent_Populate(stb)

find_package(OpenMP)

# ---------- Core library (shared by every app) ----------
add_library(gs_core
  src/math.cpp
  src/camera.cpp
  src/ply_loader.cpp
  src/sh.cpp
  src/tiles.cpp
  src/renderer.cpp
  src/trim.cpp
  src/image_io.cpp
)
target_include_directories(gs_core PUBLIC
  include
  ${happly_SOURCE_DIR}
  ${stb_SOURCE_DIR})
target_link_libraries(gs_core PUBLIC glm::glm)
if(OpenMP_CXX_FOUND)
  target_link_libraries(gs_core PUBLIC OpenMP::OpenMP_CXX)
  target_compile_definitions(gs_core PUBLIC GS_HAS_OPENMP=1)
endif()

# ---------- Apps ----------
add_executable(gs_render apps/render_main.cpp)
target_link_libraries(gs_render PRIVATE gs_core)

if(GS_BUILD_PREVIEW)
  find_package(SDL2 QUIET)
  if(SDL2_FOUND)
    add_executable(gs_preview apps/preview_main.cpp)
    target_link_libraries(gs_preview PRIVATE gs_core SDL2::SDL2)
  else()
    message(WARNING "SDL2 not found: skipping gs_preview. Install SDL2 or pass -DGS_BUILD_PREVIEW=OFF.")
  endif()
endif()

# ---------- Tests ----------
if(GS_BUILD_TESTS)
  enable_testing()
  add_executable(gs_tests tests/test_main.cpp)
  target_link_libraries(gs_tests PRIVATE gs_core)
  add_test(NAME gs_tests COMMAND gs_tests)
endif()
