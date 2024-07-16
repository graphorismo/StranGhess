cmake_minimum_required(VERSION 3.1...3.29)

project(
  StranGhess
  VERSION 0.0.1
  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)

find_package(Curses REQUIRED)
find_package(nlohmann_json REQUIRED)

add_executable(StranGhess main.cpp
  Desk.hpp Desk.cpp
  Game.hpp Game.cpp
  Menu.hpp Menu.cpp
  MenuNode.hpp MenuNode.cpp
  MoveCode.hpp MoveCode.cpp
  NcursesSystemInput.hpp NcursesSystemInput.cpp
  NcursesSystemOutput.hpp NcursesSystemOutput.cpp
  Piece.hpp Piece.cpp
  SystemInputInterface.hpp
  SystemOutputInterface.hpp
  Vector2d.hpp
)

target_link_libraries(StranGhess ncurses nlohmann_json)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/figures DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
