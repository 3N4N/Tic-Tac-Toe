cmake_minimum_required(VERSION 3.0)
project(tictactoe)
set(EXE "Tic-tac-toe")

include_directories(inc)
file(GLOB SOURCES "src/*.c")

# find_package(SDL2 REQUIRED)

INCLUDE(FindPkgConfig)
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2_IMAGE REQUIRED SDL2_image>=2.0.0)
PKG_SEARCH_MODULE(SDL2_TTF REQUIRED SDL2_ttf)

add_executable(${EXE} ${SOURCES})
target_link_libraries(
  ${EXE}
  ${SDL2_LIBRARIES}
  ${SDL2_IMAGE_LIBRARIES}
  ${SDL2_TTF_LIBRARIES}
)

# set_property(TARGET ${EXE} PROPERTY C_STANDARD 17)

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})
