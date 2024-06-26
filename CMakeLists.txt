cmake_minimum_required(VERSION 3.1...3.29)

project(
  StranGhess
  VERSION 0.0.1
  LANGUAGES CXX)

find_package(Curses REQUIRED)
find_package(nlohmann_json REQUIRED)

add_executable(StranGhess main.cpp)

target_link_libraries(StranGhess ncurses nlohmann_json)
