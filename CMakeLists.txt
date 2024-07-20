cmake_minimum_required(VERSION 3.1...3.29)

project(
  StranGhess
  VERSION 0.0.1
  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)

find_package(Curses REQUIRED)
find_package(nlohmann_json REQUIRED)

add_executable(StranGhess src/main.cpp
  src/Cursor.hpp
  src/Desk.hpp src/Desk.cpp
  src/Game.hpp src/Game.cpp
  src/Menu.hpp src/Menu.cpp
  src/MenuNode.hpp src/MenuNode.cpp
  src/MoveCode.hpp src/MoveCode.cpp
  src/NcursesSystemInput.hpp src/NcursesSystemInput.cpp
  src/NcursesSystemOutput.hpp src/NcursesSystemOutput.cpp
  src/Piece.hpp src/Piece.cpp
  src/SystemInputInterface.hpp
  src/SystemInterfaces.hpp
  src/SystemOutputInterface.hpp
  src/Vector2d.hpp
)

if(MSVC)
  target_compile_options(StranGhess PRIVATE /W4 /WX)
else()
  target_compile_options(StranGhess PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()

target_link_libraries(StranGhess ncurses nlohmann_json)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/figures DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
