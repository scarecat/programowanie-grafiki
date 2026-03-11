cmake_minimum_required(VERSION 3.20)
project(Game)
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
add_executable(game)


#set(ASSIMP_BUILD_DOCS OFF)
#set(ASSIMP_BUILD_TESTS OFF)
#set(ASSIMP_INSTALL OFF)
#set(ASSIMP_NO_EXPORT ON)
#set(ASSIMP_BUILD_ALL_IMPORTERS_BY_DEFAULT OFF)
#set(ASSIMP_BUILD_OBJ_IMPORTER ON)

set(glew-cmake_BUILD_SHARED OFF)

set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_DOCS ON)

#set(PATCH_ASSIMP ON)
#if(PATCH_ASSIMP) 
#  set(patch_assimp git apply ${CMAKE_CURRENT_SOURCE_DIR}/misc/assimp-6.0.4-zlib-1.3.2.patch || true)
#endif()

include(FetchContent)

# FetchContent_Declare(
#   glfw
#   GIT_REPOSITORY https://github.com/glfw/glfw.git
#   GIT_TAG 7b6aead9fb88b3623e3b3725ebb42670cbe4c579 # 3.4
# )

FetchContent_Declare(
  freeglut
  GIT_REPOSITORY https://github.com/freeglut/freeglut
  GIT_TAG 3db1649ce1f5e42f1338b51e3fa14849be547d5d # 3.8.0
)

FetchContent_Declare(
  glew
  GIT_REPOSITORY https://github.com/Perlmint/glew-cmake.git
  GIT_TAG 2f38fcbb3b6c051130a4f624675584a11bfaaf9f # 2.3.1
)

FetchContent_Declare(
  assimp
  GIT_REPOSITORY https://github.com/assimp/assimp.git
  GIT_TAG e0b52347c6e52de2827ec957a9ebf00ce3c54f79 # 6.0.4
  PATCH_COMMAND ${patch_assimp}
)

FetchContent_MakeAvailable(freeglut glew)


target_sources(game PRIVATE
  #src/stb/stb_image.h
  src/main.c
)
target_include_directories(game PRIVATE ${freeglut_SOURCE_DIR}/include)
target_include_directories(game PRIVATE include/)
target_include_directories(game PRIVATE src/)

target_link_libraries(game freeglut_static)


if(IS_DIRECTORY ${CMAKE_SOURCE_DIR}/assets)
add_custom_target(
  copy_assets
  COMMAND ${CMAKE_COMMAND} -E copy_directory              
  ${CMAKE_SOURCE_DIR}/assets ${CMAKE_BINARY_DIR}/assets
  COMMENT "Copying assets" VERBATIM
)
add_dependencies(game copy_assets)
endif()